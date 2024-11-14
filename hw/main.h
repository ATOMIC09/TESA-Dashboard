#ifndef RPI_MAIN_H
#define RPI_MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sqlite3.h>

extern void* sound_processing_unit();
extern void* ml_unit();

typedef struct {
    void* shared_var;            // The variable to manage (generic pointer)
    pthread_mutex_t lock;        // Mutex for locking and unlocking
    pthread_cond_t cond;         // Condition variable for signaling
} SharedData;

extern SharedData command_data;
extern SharedData payload_data;

extern void init_shared_data(SharedData *data, size_t size);
extern void set_shared_var(SharedData *data, void *value, size_t size);
extern void get_shared_var(SharedData *data, size_t size, void *value);
extern void destroy_shared_data(SharedData *data);

#endif // RPI_MAIN_H