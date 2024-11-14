#include "main.h"

void init_sound_processing_database( sqlite3** db ) {
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
        exit(1);
    }

    if (sqlite3_exec(*db, schema, NULL, NULL, NULL) != SQLITE_OK) {
        fprintf(stderr, "Cannot create table: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        exit(1);
    }
}

void* sound_processing_unit() {
    // Initialize the database
    sqlite3* db = NULL;
    init_sound_processing_database(&db);

    sqlite3_stmt* stmt;
    while (1) {
        // Do Something

        // Print logs
        if (sqlite3_prepare_v2(db, "SELECT * FROM logs", -1, &stmt, NULL) != SQLITE_OK) {
            fprintf(stderr, "Cannot prepare statement: %s\n", sqlite3_errmsg(db));
            sqlite3_close(db);
            exit(1);
        }

        while (sqlite3_step(stmt) == SQLITE_ROW) {
            printf("ID: %d, Timestamp: %s, Type: %s, Outcome: %s\n",
                sqlite3_column_int(stmt, 0),
                sqlite3_column_text(stmt, 1),
                sqlite3_column_text(stmt, 2),
                sqlite3_column_text(stmt, 3));
        }

        sqlite3_finalize(stmt);
        printf("SPU Looping...\n");

        sleep(1);
    }

    // Close the database
    sqlite3_close(db);
}