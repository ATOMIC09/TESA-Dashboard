#include "main.h"

void* ml_unit() {
    char command[1024] = "TEST Command";
    char command_copy[1024];
    time_t t;
    char payload[600000];
    double feature[14042];
    while (1) {
        pthread_mutex_lock(&command_data.lock);
        strcpy(command_copy, command_data.shared_var);
        pthread_mutex_unlock(&command_data.lock);

        if (strcmp(command_copy, command) != 0) {
            strcpy(command, command_copy);

            // Do something with the command
            if (strcmp(command, "update-model") == 0) {
                // Update the model
            }
        }

        pthread_mutex_lock(&processing_ml_unit_data.lock);
        pthread_cond_wait(&processing_ml_unit_data.cond, &processing_ml_unit_data.lock);
        strcpy(payload, processing_ml_unit_data.shared_var);
        pthread_mutex_unlock(&processing_ml_unit_data.lock);
        
        cJSON *root = cJSON_Parse(payload);
        cJSON *features = cJSON_GetObjectItem(root, "features");
        int timestamp = cJSON_GetObjectItem(root, "timestamp")->valueint;

        for (int i = 0; i < 14042; i++) {
            feature[i] = cJSON_GetArrayItem(features, i)->valuedouble;
        }
        
        categorical* result_class;
        float* result_confidence;
        NeuralPredictAudio2(
            feature,
            result_class,
            result_confidence
        );

        time(&t);
        struct tm tm = *localtime(&t);
        char created_at[100];
        strftime(created_at, 26, "%Y-%m-%dT%H:%M:%S%z", &tm);

        cJSON *root2 = cJSON_CreateObject();
        cJSON_AddNumberToObject(root2, "timestamp", timestamp);
        cJSON_AddStringToObject(root2, "created_at", created_at);
        cJSON_AddStringToObject(root2, "classification", result_class->categoryNames[result_class->codes].f1.data);
        cJSON_AddNumberToObject(root2, "confidence", *result_confidence);
        char *payload = cJSON_PrintUnformatted(root);
        pthread_mutex_lock(&ml_sender_data.lock);
        strcpy(ml_sender_data.shared_var, payload);
        pthread_cond_signal(&ml_sender_data.cond);
        pthread_mutex_unlock(&ml_sender_data.lock);
        // set_shared_var_cond_signal(&ml_sender_data, payload, sizeof(char) * 1024);

        cJSON_Delete(root2);
        free(payload);

        cJSON_Delete(root);
        
        // sleep(1);
    }
}