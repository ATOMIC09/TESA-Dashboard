#include "main.h"

SharedData command_data;
SharedData payload_data;

SharedData recorder_processing_unit_data;
SharedData processing_ml_unit_data;
SharedData ml_sender_data;
SharedData sound_process_data;
SharedData model_update_data;

void load_env(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        perror("Failed to open .env file");
        exit(EXIT_FAILURE);
    }
    char line[256];
    while (fgets(line, sizeof(line), file))
    {
        char *key = strtok(line, "=");
        char *value = strtok(NULL, "\n");
        if (key && value)
        {
            setenv(key, value, 1);
        }
    }
    fclose(file);
}

void destroy_all_datas() {
    destroy_shared_data(&command_data);
    destroy_shared_data(&payload_data);
    destroy_shared_data(&recorder_processing_unit_data);
    destroy_shared_data(&processing_ml_unit_data);
    destroy_shared_data(&ml_sender_data);
    destroy_shared_data(&sound_process_data);
    destroy_shared_data(&model_update_data);
}

int main() {
    // Load environment variables from .env file
    load_env(".env");

    // Initialize the shared data struct
    init_shared_data(&command_data, sizeof(char) * 256);
    init_shared_data(&payload_data, sizeof(char) * 1024);
    init_shared_data(&recorder_processing_unit_data, sizeof(char) * 192600);
    init_shared_data(&processing_ml_unit_data, sizeof(char) * 600000);
    init_shared_data(&ml_sender_data, sizeof(char) * 1024);
    init_shared_data(&sound_process_data, sizeof(char) * 1024);
    init_shared_data(&model_update_data, sizeof(char) * 1024);

    // Create threads for the sound processing unit and machine learning unit
    pthread_t sound_thread, ml_thread, ml_sender_thread, sound_process_sender_thread;

    if (pthread_create(&sound_thread, NULL, (void *)sound_processing_unit, NULL) != 0) {
        perror("Failed to create sound processing unit thread");
        destroy_all_datas();
        exit(EXIT_FAILURE);
    }

    if (pthread_create(&ml_thread, NULL, (void *)ml_unit, NULL) != 0) {
        perror("Failed to create machine learning unit thread");
        destroy_all_datas();
        exit(EXIT_FAILURE);
    }

    if (pthread_create(&ml_sender_thread, NULL, (void *)ml_sender, NULL) != 0) {
        perror("Failed to create machine learning sender thread");
        destroy_all_datas();
        exit(EXIT_FAILURE);
    }

    if (pthread_create(&sound_process_sender_thread, NULL, (void *)sound_process_sender, NULL) != 0) {
        perror("Failed to create sound process sender thread");
        destroy_all_datas();
        exit(EXIT_FAILURE);
    }

    // Wait for threads to finish
    pthread_join(sound_thread, NULL);
    pthread_join(ml_thread, NULL);
    pthread_join(ml_sender_thread, NULL);
    pthread_join(sound_process_sender_thread, NULL);

    // Destroy the shared data struct
    destroy_all_datas();

    return 0;
}