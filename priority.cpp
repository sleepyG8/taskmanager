#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s add <priority> <task>\n", argv[0]);
        printf("       %s read\n", argv[0]);
        exit(1);  
    }

    char *choice = argv[1];

    if (strcmp(choice, "add") == 0) {
        if (argc < 4) {
            printf("Usage: %s add <priority> <task>\n", argv[0]);
            return 1;
        }
        char *priority = argv[2];

       
        char buffer[100] = "";
        for (int i = 3; i < argc; i++) {
            strcat(buffer, argv[i]);
            strcat(buffer, " ");  
        }
        buffer[strlen(buffer) - 1] = '\0';  

        
        FILE *file = fopen("tasks", "a");
        if (file == NULL) {
            printf("Cannot create file\n");
            return 1;
        }

        
        printf("Adding to file...\n");
        char fullline[100];
        if (strlen(buffer) < sizeof(fullline)) {
            strcpy(fullline, buffer);
            strcat(fullline, "|");
            strcat(fullline, priority);
            strcat(fullline, "\n");
            fwrite(fullline, sizeof(char), strlen(fullline), file);
        } else {
            printf("Error: Task data too long\n");
            fclose(file);
            return 1;
        }

        fclose(file);
        return 0;
    }

    if (strcmp(choice, "read") == 0) {
        FILE *file = fopen("tasks", "r");
        if (file == NULL) {
            printf("Error opening file to read\n");
            return 1;  
        }

        printf("Reading from file:\n");
        char buffer[100];
        int linesRead = 0;  

        
        while (fgets(buffer, sizeof(buffer), file) != NULL) {
            printf("%s", buffer);  
            linesRead++;  
        }

        if (linesRead == 0) {
            printf("The file is empty or has no readable content.\n");
        }

        fclose(file);
        return 0;
    }
}
