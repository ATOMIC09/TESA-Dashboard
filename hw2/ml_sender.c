#include "main.h"

int init_classification_database( sqlite3** db ) {

    const char db_name[] = "classification.db";
    const char table_name[] = "logs";
    const char schema[] = "CREATE TABLE IF NOT EXISTS logs ( \
id INTEGER PRIMARY KEY AUTOINCREMENT, \
timestamp INTEGER NOT NULL, \
created_at TEXT NOT NULL, \
classification TEXT NOT NULL, \
confidence REAL);";

    // Initialize the sqlite database
    if (sqlite3_open(db_name, db) != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(*db));
        sqlite3_close(*db);
        return 1;
    }

    if (sqlite3_exec(*db, schema, NULL, NULL, NULL) != SQLITE_OK) {
        fprintf(stderr, "Cannot create table: %s\n", sqlite3_errmsg(*db));
        sqlite3_close(*db);
        return 1;
    }

    return 0;
}

int init_mqtt(
    MQTTClient* client, 
    const char* mqtt_broker, 
    const char* client_id, 
    const char* username, 
    const char* password) {
    // Initialize MQTT
    int rc;

    MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;
    MQTTClient_create(client, mqtt_broker, client_id, MQTTCLIENT_PERSISTENCE_NONE, NULL);
    conn_opts.keepAliveInterval = 20;
    conn_opts.cleansession = 1;
    conn_opts.username = username;
    conn_opts.password = password;

    if ((rc = MQTTClient_connect(*client, &conn_opts)) != MQTTCLIENT_SUCCESS) {
        fprintf(stderr, "Failed to connect, return code %d\n", rc);
        return 1;
    }

    // Test connection
    const char topic[] = "testtopic1";
    cJSON *root = cJSON_CreateObject();
    cJSON_AddStringToObject(root, "message", "Hello, World! Test in Raspberry Pi");
    char *payload = cJSON_PrintUnformatted(root);
    MQTTClient_message pubmsg = MQTTClient_message_initializer;
    pubmsg.payload = (void *)payload;
    pubmsg.payloadlen = strlen(payload);
    pubmsg.qos = 0;
    pubmsg.retained = 0;
    MQTTClient_deliveryToken token;
    if ((rc = MQTTClient_publishMessage(*client, topic, &pubmsg, &token)) != MQTTCLIENT_SUCCESS) {
        fprintf(stderr, "Failed to publish message, return code %d\n", rc);
        return 1;
    }

    printf("Test message published\n");

    return 0;
}

int send_mqtt_message(
    MQTTClient* client,
    const char* topic,
    MQTTClient_message* pubmsg,
    MQTTClient_deliveryToken* token,
    int id, 
    int timestamp, 
    char* created_at,
    char* classification, 
    double confidence) {
    // Send MQTT message
    cJSON *root = cJSON_CreateObject();
    cJSON_AddNumberToObject(root, "id", id);
    cJSON_AddNumberToObject(root, "timestamp", timestamp);
    cJSON_AddStringToObject(root, "created_at", created_at);
    cJSON_AddStringToObject(root, "classification", classification);
    cJSON_AddNumberToObject(root, "confidence", confidence);
    char *payload = cJSON_PrintUnformatted(root);
    pubmsg->payload = (void *)payload;
    pubmsg->payloadlen = strlen(payload);
    pubmsg->qos = 0;
    pubmsg->retained = 0;
    if (MQTTClient_publishMessage(*client, topic, pubmsg, token) != MQTTCLIENT_SUCCESS) {
        fprintf(stderr, "Failed to publish message\n");
        return 1;
    }
    return 0;
}

void* ml_sender() {
    const char* mqtt_broker = getenv("mqtt_broker");
    const char* client_id = getenv("client_id");
    const char* username = getenv("username");
    const char* password = getenv("password");
    const char* topic = "rpi/mlu/data"; // 10000000edec2a6b

    sqlite3* db = NULL;
    MQTTClient client;
    if (init_classification_database(&db) != 0) {
        printf("Failed to initialize SQLite database\n");
        exit(1);
    }
    if (init_mqtt(
        &client, 
        mqtt_broker, 
        client_id,
        username,
        password) != 0) {
        printf("Failed to initialize MQTT\n");
        exit(1);
    }

    MQTTClient_message pubmsg = MQTTClient_message_initializer;
    MQTTClient_deliveryToken token;
    sqlite3_stmt* stmt;

    while (1) {
        // Get the shared variable
        char classification[1024];

        pthread_mutex_lock(&ml_sender_data.lock);
        pthread_cond_wait(&ml_sender_data.cond, &ml_sender_data.lock);

        strcpy(classification, ml_sender_data.shared_var);

        pthread_mutex_unlock(&ml_sender_data.lock);

        cJSON *root = cJSON_Parse(classification);
        int timestamp = cJSON_GetObjectItem(root, "timestamp")->valueint;
        char* created_at = cJSON_GetObjectItem(root, "created_at")->valuestring;
        char* classification_str = cJSON_GetObjectItem(root, "classification")->valuestring;
        double confidence = cJSON_GetObjectItem(root, "confidence")->valuedouble;

        // Insert into SQLite database
        char sql[1024];
        sprintf(sql, "INSERT INTO logs (timestamp, created_at, classification, confidence) VALUES (%d, '%s', '%s', %f);", timestamp, created_at, classification_str, confidence);

        if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
            fprintf(stderr, "Cannot prepare statement: %s\n", sqlite3_errmsg(db));
            sqlite3_close(db);
            exit(1);
        }

        if (sqlite3_step(stmt) != SQLITE_DONE) {
            fprintf(stderr, "Cannot execute statement: %s\n", sqlite3_errmsg(db));
            sqlite3_finalize(stmt);
            sqlite3_close(db);
            exit(1);
        }

        sqlite3_finalize(stmt);

        // Send MQTT message

        if (send_mqtt_message(
            &client,
            topic,
            &pubmsg,
            &token,
            sqlite3_last_insert_rowid(db),
            timestamp,
            created_at,
            classification_str,
            confidence) != 0) {
            printf("Failed to send MQTT message\n");
            exit(1);
        }

        cJSON_Delete(root);
    }
}