#include "main.h"

void init_classification_database( sqlite3** db ) {

    const char db_name[] = "classification.db";
    const char table_name[] = "logs";
    const char schema[] = "CREATE TABLE IF NOT EXISTS logs ( \
id INTEGER PRIMARY KEY AUTOINCREMENT, \
timestamp TEXT NOT NULL, \
classification TEXT NOT NULL, \
confidence REAL);";

    // Initialize the sqlite database
    if (sqlite3_open(db_name, db) != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(*db));
        sqlite3_close(*db);
        exit(1);
    }

    if (sqlite3_exec(*db, schema, NULL, NULL, NULL) != SQLITE_OK) {
        fprintf(stderr, "Cannot create table: %s\n", sqlite3_errmsg(*db));
        sqlite3_close(*db);
        exit(1);
    }

    // 
}

void* ml_unit() {
    // Initialize the database
    sqlite3* db = NULL;
    init_classification_database(&db);

    char command[100] = "\0";
    char* command_copy = malloc(sizeof(char) * 100);
    sqlite3_stmt* stmt;
    while (1) {
        get_shared_var(&command_data, sizeof(char) * 100, command_copy);
        if (strcmp(command_copy, command) != 0) {
            printf("Command received: %s\n", command_copy);
            strcpy(command, command_copy);

            // Do something with the command
            if (strcmp(command, "update-model") == 0) {
                // Update the model
            }
        }

        // Do Classification
        
        // Print logs
        if (sqlite3_prepare_v2(db, "SELECT * FROM logs", -1, &stmt, NULL) != SQLITE_OK) {
            fprintf(stderr, "Cannot prepare statement: %s\n", sqlite3_errmsg(db));
            sqlite3_close(db);
            exit(1);
        }

        while (sqlite3_step(stmt) == SQLITE_ROW) {
            printf("ID: %d, Timestamp: %s, Classification: %s, Confidence: %f\n",
                sqlite3_column_int(stmt, 0),
                sqlite3_column_text(stmt, 1),
                sqlite3_column_text(stmt, 2),
                sqlite3_column_double(stmt, 3));
        }

        sqlite3_finalize(stmt);
        printf("MLU Looping...\n");

        sleep(1);

    }

    // Close the database
    sqlite3_close(db);
}