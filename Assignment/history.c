#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> // For timestamps
#include <unistd.h>

#define HISTORY_FILE ".history"
#define MAX_LINE_LENGTH 1024
#define MAX_HISTORY 100

void add_to_history(char *command) {
    FILE *fp = fopen(HISTORY_FILE, "a");
    if (fp == NULL) {
        perror("Error opening history file");
        return;
    }
    fprintf(fp, "%s\n", command);
    fclose(fp);
}

void print_history() {
    FILE *fp = fopen(HISTORY_FILE, "r");
    if (fp == NULL) {
        perror("Error opening history file");
        return;
    }
    char line[MAX_LINE_LENGTH];
    int count = 0;
    while (fgets(line, MAX_LINE_LENGTH, fp) != NULL) {
        printf("%d %s", count, line);
        count++;
        if (count >= MAX_HISTORY) {
            break;
        }
    }
    fclose(fp);
}

void print_timestamp() {
    time_t now;
    struct tm *local_time;
    char timestamp[20]; // Adjust size as needed

    now = time(NULL);
    local_time = localtime(&now);
    strftime(timestamp, sizeof(timestamp), "[%Y-%m-%d %H:%M:%S]", local_time);

    printf("Timestamp: %s\n", timestamp);
}

int main(int argc, char *argv[]) {
    if (argc > 1) {
        add_to_history(argv[1]);
    } else {
        print_history();
        print_timestamp(); // Optional: Print timestamp
    }
    return 0;
}