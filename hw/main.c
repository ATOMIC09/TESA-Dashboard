#include "main.h"

SharedData command_data;
SharedData payload_data;

int main() {
    // Initialize the shared data struct
    init_shared_data(&command_data, sizeof(char) * 256);
    init_shared_data(&payload_data, sizeof(char) * 1024);

    // Create threads for the sound processing unit and machine learning unit
    pthread_t sound_thread, ml_thread;

    if (pthread_create(&sound_thread, NULL, (void *)sound_processing_unit, NULL) != 0) {
        perror("Failed to create sound processing unit thread");
        destroy_shared_data(&command_data);
        exit(EXIT_FAILURE);
    }

    if (pthread_create(&ml_thread, NULL, (void *)ml_unit, NULL) != 0) {
        perror("Failed to create machine learning unit thread");
        destroy_shared_data(&command_data);
        exit(EXIT_FAILURE);
    }

    // Wait for threads to finish
    pthread_join(sound_thread, NULL);
    pthread_join(ml_thread, NULL);

    // Destroy the shared data struct
    destroy_shared_data(&command_data);

    return 0;
}