#include "main.h"

void* ml_unit() {
    char ccc[] = {'F', 'N', 'X'};
    int length = sizeof(ccc) / sizeof(ccc[0]);
    char command[1024] = "TEST Command\0";
    char command_copy[1024];
    time_t t;
    while (1) {
        // get_shared_var(&command_data, sizeof(char) * 100, command_copy);
        // pthread_mutex_lock(&command_data.lock);
        // strcpy(command_copy, command_data.shared_var);
        // pthread_mutex_unlock(&command_data.lock);

        // if (strcmp(command_copy, command) != 0) {
        //     printf("Command received: %s\n", command_copy);
        //     strcpy(command, command_copy);

        //     // Do something with the command
        //     if (strcmp(command, "update-model") == 0) {
        //         // Update the model
        //     }
        // }

        // Do Classification
        // double x[48000];
        // for (int i = 0; i < 48000; i++) {
        //     x[i] = (double)rand() / RAND_MAX;
        // }

        time(&t);
        struct tm tm = *localtime(&t);
        char created_at[100];
        strftime(created_at, 26, "%Y-%m-%dT%H:%M:%S%z", &tm);

        int timestamp = (int)t;
        int rI = rand() % length;
        char classification = ccc[rI];
        char classification_copy[1];

        memcpy(classification_copy, &classification, sizeof(char));
        double confidence = (double)rand() / RAND_MAX;

        cJSON *root = cJSON_CreateObject();
        cJSON_AddNumberToObject(root, "timestamp", timestamp);
        cJSON_AddStringToObject(root, "created_at", created_at);
        cJSON_AddStringToObject(root, "classification", classification_copy);
        cJSON_AddNumberToObject(root, "confidence", confidence);
        char *payload = cJSON_PrintUnformatted(root);

        pthread_mutex_lock(&ml_sender_data.lock);
        strcpy(ml_sender_data.shared_var, payload);
        pthread_cond_signal(&ml_sender_data.cond);
        pthread_mutex_unlock(&ml_sender_data.lock);
        // set_shared_var_cond_signal(&ml_sender_data, payload, sizeof(char) * 1024);

        cJSON_Delete(root);
        free(payload);
        
        // sleep(1);


    }
}