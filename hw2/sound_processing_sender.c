#include "main.h"

int init_processing_database( sqlite3** db ) {

    const char db_name[] = "processing.db";
    const char table_name[] = "logs";
    const char schema[] = "CREATE TABLE IF NOT EXISTS logs ( \
id INTEGER PRIMARY KEY AUTOINCREMENT, \
created_at TEXT NOT NULL, \
outcome TEXT NOT NULL);";

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

void* sound_process_sender() {
    sqlite3* db = NULL;
    if (init_processing_database(&db) != 0) {
        exit(1);
    }
    sqlite3_stmt* stmt;
    time_t t;
    while (1) {
        // Get the shared variable
        char outcome[1024];

        pthread_mutex_lock(&sound_process_data.lock);
        pthread_cond_wait(&sound_process_data.cond, &sound_process_data.lock);
        strcpy(outcome, sound_process_data.shared_var);
        pthread_mutex_unlock(&sound_process_data.lock);

        
        time(&t);
        struct tm tm = *localtime(&t);
        char created_at[100];
        strftime(created_at, 26, "%Y-%m-%dT%H:%M:%S%z", &tm);

        // Insert into SQLite database
        char sql[1024];
        sprintf(sql, "INSERT INTO logs (created_at, outcome) VALUES ('%s', '%s');", created_at, outcome);

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
    }
    
}