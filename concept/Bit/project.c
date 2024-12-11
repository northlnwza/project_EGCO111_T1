#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void getCurrentTimestamp(char *buffer, size_t size) {
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    strftime(buffer, size, "%Y/%m/%d %H:%M:%S", t);
}

void createDevicesFile() {
    FILE *file = fopen("devices.txt", "r");
    if (!file) {
        file = fopen("devices.txt", "w");
        if (file) {
            fprintf(file, "fridge 200\n");
            fprintf(file, "air_conditioner 1500\n");
            fprintf(file, "heater 1200\n");
            fclose(file);
        }
    } else {
        fclose(file);
    }
}

int readDevices(char devices[][50], int maxDevices) {
    FILE *file = fopen("devices.txt", "r");
    if (!file) {
        printf("Error: Could not open devices file.\n");
        return 0;
    }
    int count = 0;
    while (count < maxDevices && fscanf(file, "%49s %49s", devices[count], devices[count + 1]) == 2) {
        count += 2; 
    }
    fclose(file);
    return count / 2; 
}

void logStatusChange(const char *device, const char *number, const char *status) {
    FILE *logFile = fopen("log.txt", "a");
    if (logFile) {
        char timestamp[20];
        getCurrentTimestamp(timestamp, sizeof(timestamp));
        fprintf(logFile, "%s - %s (%s) toggled to %s\n", timestamp, device, number, status);
        fclose(logFile);
    }
}

void updateTimeLog(const char *device, const char *number, long duration) {
    FILE *timeLogFile = fopen("timelog.txt", "a");
    if (timeLogFile) {
        fprintf(timeLogFile, "%s (%s) was ON for %ld seconds\n", device, number, duration);
        fclose(timeLogFile);
    }
}

int main() {
    char devices[100][50]; 
    char statuses[50][10];
    time_t startTimes[50] = {0}; 
    int numDevices;
    
    createDevicesFile();
    numDevices = readDevices(devices, 100);

    if (numDevices == 0) {
        printf("No devices found.\n");
        return 1;
    }

    for (int i = 0; i < numDevices; i++) {
        strcpy(statuses[i], "OFF");
    }

    while (1) {
        clearScreen();

        printf("Device List:\n");
        for (int i = 0; i < numDevices; i++) {
            printf("%d. %s (%s) - %s\n", i + 1, devices[i * 2], devices[i * 2 + 1], statuses[i]);
        }

        printf("\nSelect a device to toggle (1-%d), -1 to view log, or 0 to quit: ", numDevices);
        char input[20];
        fgets(input, sizeof(input), stdin);

        char *endptr;
        int choice = strtol(input, &endptr, 10);
        if (endptr == input || *endptr != '\n') {
            printf("Invalid input. Please enter a number.\n");
            continue;
        }

        if (choice == 0) {
            break; 
        } else if (choice == -1) {
            FILE *logFile = fopen("log.txt", "r");
            if (logFile) {
                char line[256];
                printf("\n--- Log Entries ---\n");
                while (fgets(line, sizeof(line), logFile)) {
                    printf("%s", line);
                }
                fclose(logFile);
            } else {
                printf("No logs available.\n");
            }
            printf("\nPress Enter to continue...");
            getchar(); 
            continue;
        } else if (choice < 1 || choice > numDevices) {
            printf("Invalid choice. Please try again.\n");
            continue;
        }

        int index = choice - 1;

        if (strcmp(statuses[index], "OFF") == 0) {
            strcpy(statuses[index], "ON");
            startTimes[index] = time(NULL);
        } else {
            strcpy(statuses[index], "OFF");
            if (startTimes[index] != 0) {
                time_t endTime = time(NULL);
                long duration = endTime - startTimes[index];
                updateTimeLog(devices[index * 2], devices[index * 2 + 1], duration);
                startTimes[index] = 0;
            }
        }

        logStatusChange(devices[index * 2], devices[index * 2 + 1], statuses[index]);
    }

    printf("Exiting program.\n");
    return 0;
}
