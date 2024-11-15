#include "main.h"

int init_model_update_database( sqlite3** db ) {

    const char db_name[] = "model_update.db";
    const char table_name[] = "logs";
    const char schema[] = "CREATE TABLE IF NOT EXISTS logs ( \
id INTEGER PRIMARY KEY AUTOINCREMENT, \
created_at TEXT NOT NULL, \
event TEXT NOT NULL);";

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

void* model_update_sender() {
    sqlite3* db = NULL;
    sqlite3_stmt* stmt;
    if (init_model_update_database(&db) != 0) {
        printf("Failed to initialize SQLite database\n");
        exit(1);
    }

    time_t t;

    while (1) {
        // Get the shared variable
        char event[1024];

        pthread_mutex_lock(&model_update_data.lock);
        pthread_cond_wait(&model_update_data.cond, &model_update_data.lock);

        strcpy(event, model_update_data.shared_var);

        pthread_mutex_unlock(&model_update_data.lock);

        time(&t);
        struct tm tm = *localtime(&t);
        char created_at[100];
        strftime(created_at, 26, "%Y-%m-%dT%H:%M:%S%z", &tm);


        // Insert into SQLite database
        char sql[1024];
        sprintf(sql, "INSERT INTO logs (created_at, event) VALUES ('%s', '%s');", created_at, event);

        if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
            fprintf(stderr, "Cannot prepare statement: %s\n", sqlite3_errmsg(db));
            sqlite3_close(db);
            exit(1);
        }

        if (sqlite3_step(stmt) != SQLITE_DONE) {
            fprintf(stderr, "Cannot execute statement: %s\n", sqlite3_errmsg(db));
            sqlite3_close(db);
            exit(1);
        }

        sqlite3_finalize(stmt);
    }
}