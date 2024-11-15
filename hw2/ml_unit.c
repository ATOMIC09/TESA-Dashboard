#include "main.h"

void* ml_unit() {
    char command[256] = "TEST Command";
    char command_copy[256];
    time_t t;
    double feature[14042];
    while (1) {
        pthread_mutex_lock(&command_data.lock);
        strcpy(command_copy, command_data.shared_var);
        pthread_mutex_unlock(&command_data.lock);

        if (strcmp(command_copy, command) != 0) {
            strcpy(command, command_copy);

            // Do something with the command
            if (strcmp(command, "update-model") == 0) {
                char result_payload_comamand[] = "wget %s -O static/model.zip";
                char result_payload[256];
                sprintf(result_payload, result_payload_comamand, getenv("MODEL_URL"));
                system(result_payload);
                system("unzip static/model.zip");
                system("rm static/model.zip");
                // Remove except .o files
                system("find . -type f ! -name '*.o' -delete");
                system("mv NeuralNgin codegen/lib/");
                const char all_c_files_bash[] = "find . -name '*.c'";
                FILE* fp = popen(all_c_files_bash, "r");
                if (fp == NULL) {
                    printf("Failed to run command\n" );
                    pclose(fp);
                } else {
                    char path[1024];
                    if (fgets(path, sizeof(path), fp) != NULL) {
                        system("make");
                        system("./main");
                        pclose(fp);
                        exit(0);
                    }
                    pclose(fp);
                }

            }
        }

        char payload1[600000];

        pthread_mutex_lock(&processing_ml_unit_data.lock);
        pthread_cond_wait(&processing_ml_unit_data.cond, &processing_ml_unit_data.lock);
        strcpy(payload1, processing_ml_unit_data.shared_var);
        pthread_mutex_unlock(&processing_ml_unit_data.lock);
        
        cJSON *root = cJSON_Parse(payload1);
        cJSON *features = cJSON_GetObjectItem(root, "features");
        int timestamp = cJSON_GetObjectItem(root, "timestamp")->valueint;

        for (int i = 0; i < 14042; i++) {
            feature[i] = cJSON_GetArrayItem(features, i)->valuedouble;
        }

        categorical result_class;
        float result_confidence;
        NeuralPredictAudio2(
            feature,
            &result_class,
            &result_confidence
        );

        time(&t);
        struct tm tm = *localtime(&t);
        char created_at[100];
        strftime(created_at, 26, "%Y-%m-%dT%H:%M:%S%z", &tm);
        char class[1];
        char num_class = result_class.categoryNames[result_class.codes - 1].f1.data[0];
        sprintf(class, "%c", num_class);

        cJSON *root2 = cJSON_CreateObject();
        cJSON_AddNumberToObject(root2, "timestamp", timestamp);
        cJSON_AddStringToObject(root2, "created_at", created_at);
        cJSON_AddStringToObject(root2, "classification", class);
        cJSON_AddNumberToObject(root2, "confidence", result_confidence);
        char *payload2 = cJSON_PrintUnformatted(root2);
        printf("Payload: %s\n", payload2);
        printf("Payload Size: %lu\n", strlen(payload2));
        pthread_mutex_lock(&ml_sender_data.lock);
        strcpy(ml_sender_data.shared_var, payload2);
        pthread_cond_signal(&ml_sender_data.cond);
        pthread_mutex_unlock(&ml_sender_data.lock);
        // set_shared_var_cond_signal(&ml_sender_data, payload, sizeof(char) * 1024);

        
        cJSON_Delete(root);
        cJSON_Delete(root2);
        free(payload2);
        
        // sleep(1);
    }
}