#include "main.h"

int init_sound_processing_database( sqlite3** db ) {
    const char db_name[] = "sound_processing.db";
    const char table_name[] = "logs";
    const char schema[] = "CREATE TABLE IF NOT EXISTS logs ( \
id INTEGER PRIMARY KEY AUTOINCREMENT, \
timestamp TEXT NOT NULL, \
type TEXT NOT NULL, \
outcome TEXT NOT NULL);";

    // Initialize the sqlite database
    if (sqlite3_open(db_name, db) != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    if (sqlite3_exec(*db, schema, NULL, NULL, NULL) != SQLITE_OK) {
        fprintf(stderr, "Cannot create table: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    return 0;
}

void* sound_processing_unit() {
    // Initialize the database
    sqlite3* db = NULL;
    if (init_sound_processing_database(&db) != 0) {
        exit(1);
    }

    sqlite3_stmt* stmt;
    time_t t;
    double x[48000];
    double y[43200];
    while (1) {
        double m;
        bool isCandidate = true;
        for (int i = 4800; i < 48000; i++) {
            y[i - 4800] = x[i];
        }
        CheckEvent(
            y,
            &m,
            &isCandidate
        );

        
        time(&t);
        if (isCandidate) {
            double feature[14042];
            ExtractFeatures(
                x,
                48000, 
                feature
            );

            cJSON *array = cJSON_CreateArray();
            for (int i = 0; i < 14042; i++) {
                cJSON_AddNumberToObject(array, "feature", feature[i]);
            }

            cJSON *root = cJSON_CreateObject();
            cJSON_AddNumberToObject(root, "timestamp", (int)t);
            cJSON_AddItemToObject(root, "features", array);

            char *payload = cJSON_PrintUnformatted(root);
            printf("Payload Size: %lu\n", strlen(payload));

            pthread_mutex_lock(&processing_ml_unit_data.lock);
            strcpy(processing_ml_unit_data.shared_var, payload);
            pthread_cond_signal(&processing_ml_unit_data.cond);
            pthread_mutex_unlock(&processing_ml_unit_data.lock);

            cJSON_Delete(root);
            free(payload);

            cJSON *root2 = cJSON_CreateObject();
            cJSON_AddNumberToObject(root2, "timestamp", (int)t);
            cJSON_AddStringToObject(root2, "outcome", "14x1003 Feature Extraction");

            char *payload2 = cJSON_PrintUnformatted(root2);

            pthread_mutex_lock(&sound_process_data.lock);
            strcpy(sound_process_data.shared_var, payload2);
            pthread_cond_signal(&sound_process_data.cond);
            pthread_mutex_unlock(&sound_process_data.lock);

            cJSON_Delete(root2);
            free(payload2);

            sleep(1);
        }
    }

    // Close the database
    sqlite3_close(db);
}