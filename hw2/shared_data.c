#include "main.h"

// Initialize the struct
void init_shared_data(SharedData *data, size_t size) {
    if (pthread_mutex_init(&data->lock, NULL) != 0) {
        perror("Failed to initialize mutex");
        exit(EXIT_FAILURE);
    }
    if (pthread_cond_init(&data->cond, NULL) != 0) {
        perror("Failed to initialize condition variable");
        pthread_mutex_destroy(&data->lock);
        exit(EXIT_FAILURE);
    }

    // Allocate memory for the shared variable
    data->shared_var = malloc(size);
}

// Setter function for shared_var (copies the provided value)
void set_shared_var(SharedData *data, void *value, size_t size) {
    pthread_mutex_lock(&data->lock);

    // Free any previously allocated memory
    free(data->shared_var);

    // Allocate memory for the new value and copy it
    data->shared_var = malloc(size);
    if (data->shared_var == NULL) {
        perror("Failed to allocate memory for shared_var");
        pthread_mutex_unlock(&data->lock);
        exit(EXIT_FAILURE);
    }
    memcpy(data->shared_var, value, size);

    // Signal other threads waiting on this condition
    pthread_cond_signal(&data->cond);
    pthread_mutex_unlock(&data->lock);
}

// Getter function for shared_var (returns a copy of the value)
void get_shared_var(SharedData *data, size_t size, void *value) {
    pthread_mutex_lock(&data->lock);

    // Allocate memory for the copy of the value
    
    if (value == NULL) {
        value = malloc(size);
    }
    
    // If size of value is not equal to size of shared_var, reallocate memory for value
    if (sizeof(value) != size) {
        value = realloc(value, size);
    }

    memcpy(value, data->shared_var, size);

    pthread_mutex_unlock(&data->lock);
}

void set_shared_var_cond_signal(SharedData *data, void *value, size_t size) {
    pthread_mutex_lock(&data->lock);

    // Free any previously allocated memory
    free(data->shared_var);

    // Allocate memory for the new value and copy it
    data->shared_var = malloc(size);
    if (data->shared_var == NULL) {
        perror("Failed to allocate memory for shared_var");
        pthread_mutex_unlock(&data->lock);
        exit(EXIT_FAILURE);
    }
    memcpy(data->shared_var, value, size);

    // Signal other threads waiting on this condition
    pthread_cond_signal(&data->cond);
    pthread_mutex_unlock(&data->lock);
}

void get_shared_var_cond_wait(SharedData *data, size_t size, void *value) {
    pthread_mutex_lock(&data->lock);

    // Wait for the condition variable to be signaled
    pthread_cond_wait(&data->cond, &data->lock);

    // Allocate memory for the copy of the value
    if (value == NULL) {
        value = malloc(size);
    }

    // If size of value is not equal to size of shared_var, reallocate memory for value
    if (sizeof(value) != size) {
        value = realloc(value, size);
    }

    memcpy(value, data->shared_var, size);
    pthread_mutex_unlock(&data->lock);
}

// Destroy the mutex, condition variable, and free shared_var when done
void destroy_shared_data(SharedData *data) {
    pthread_mutex_destroy(&data->lock);
    pthread_cond_destroy(&data->cond);
    free(data->shared_var);
}