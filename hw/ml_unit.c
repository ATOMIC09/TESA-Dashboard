#include "main.h"

void* ml_unit() {
    char command[100] = "\0";
    char* command_copy = malloc(sizeof(char) * 100);
    while (1) {
        get_shared_var(&command_data, sizeof(char) * 100, command_copy);
        if (strcmp(command_copy, command) != 0) {
            printf("Command received: %s\n", command_copy);
            strcpy(command, command_copy);

            // Do something with the command
        }
    }
}