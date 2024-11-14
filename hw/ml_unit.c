#include "main.h"

void* ml_unit() {

    char command[100] = "TEST Command\0";
    char* command_copy = malloc(sizeof(char) * 100);
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

        time_t t = time(NULL);
        struct tm tm = *localtime(&t);
        char created_at[100];
        strftime(created_at, 26, "%Y-%m-%dT%H:%M:%S%z", &tm);

        int timestamp = (int)t;
        char* classification = "X";
        double confidence = 0.99;

        cJSON *root = cJSON_CreateObject();
        cJSON_AddNumberToObject(root, "timestamp", timestamp);
        cJSON_AddStringToObject(root, "created_at", created_at);
        cJSON_AddStringToObject(root, "classification", classification);
        cJSON_AddNumberToObject(root, "confidence", confidence);
        char *payload = cJSON_PrintUnformatted(root);

        printf("Payload: %s\n", payload);

        set_shared_var_cond_signal(&ml_sender_data, payload, sizeof(char) * 1024);
        
        sleep(1);


    }
}