#include "header.h"

// Function to get current timestamp
void getCurrentTimestamp(char *buffer, size_t size) {
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    strftime(buffer, size, "%Y/%m/%d %H:%M:%S", t);
}

// Function to read devices from 'devices.txt'
int readDevices(char devices[][50], int maxDevices, const char *username) {
    FILE *file;
    char    path[100];

	sprintf(path, "%s/%s/device.txt", USERS_DIR, username);
    file = fopen(path, "r");
    if (!file) {
        printf("Error: Could not open devices file.\n");
        return 0;
    }

    int count = 0;
    while (count < maxDevices && fscanf(file, "%49s %49s", devices[count], devices[count + 1]) == 2) {
        count += 2;  // Store device name and number pair
    }
    fclose(file);
    return count / 2;
}

// Function to read cumulative ON times from 'timelog.txt'
void loadTotalOnTimes(long totalOnTimes[], int numDevices, char devices[][50], const char *username) {
    FILE *file;
    char    path[100];

	sprintf(path, "%s/%s/timelog.txt", USERS_DIR, username);
    file = fopen(path, "r");
    if (!file) return;  // No previous data to read

    char device[50];
    long time;
    while (fscanf(file, "%49s %ld", device, &time) == 2) {
        for (int i = 0; i < numDevices; i++) {
            if (strcmp(device, devices[i * 2]) == 0) {
                totalOnTimes[i] += time;
                break;
            }
        }
    }
    fclose(file);
}

// Function to save cumulative ON times to 'timelog.txt'
void saveTotalOnTimes(long totalOnTimes[], int numDevices, char devices[][50], const char *username) {
    FILE *file;
    char    path[100];

	sprintf(path, "%s/%s/timelog.txt", USERS_DIR, username);
    file = fopen(path, "w");
    if (file) {
        for (int i = 0; i < numDevices; i++) {
            fprintf(file, "%s %ld\n", devices[i * 2], totalOnTimes[i]);
        }
        fclose(file);
    }
}

// Function to log the status change with a timestamp
void logStatusChange(const char *device, const char *status, const char *username) {
    FILE *logFile;
    char    path[100];

	sprintf(path, "%s/%s/log.txt", USERS_DIR, username);
    logFile = fopen(path, "a");
    if (logFile) {
        char timestamp[20];
        getCurrentTimestamp(timestamp, sizeof(timestamp));
        fprintf(logFile, "%s - %s toggled to %s\n", timestamp, device, status);
        fclose(logFile);
    }
}

// Function to clear the screen
void clearScreen() {
    printf("\033[H\033[J");  // ANSI escape code to clear screen
}

// Function to validate numeric input
int isValidNumericInput(const char *input) {
    // Remove leading and trailing spaces
    while (*input == ' ' || *input == '\t') input++;
    if (*input == '\0') return 0; // Empty input after removing spaces

    for (const char *p = input; *p != '\0'; p++) {
        if (!isdigit(*p)) return 0;
    }
    return 1;
}

int usedevice(const char *username) {
    char devices[100][50];  // Array to store devices, each pair is [device name, number]
    char statuses[50][10];  // Status array (ON/OFF)
    long totalOnTimes[50] = {0};  // Cumulative ON times in seconds
    time_t startTimes[50] = {0};  // Start time when a device is turned ON

    // Ensure 'devices.txt' exists

    int numDevices = readDevices(devices, 100, username);
    if (numDevices == 0) {
        printf("No devices found.\n");
        return 1;
    }

    // Load existing total ON times from 'timelog.txt'
    loadTotalOnTimes(totalOnTimes, numDevices, devices, username);

    // Initialize all devices as OFF
    for (int i = 0; i < numDevices; i++) {
        strcpy(statuses[i], "OFF");
    }

    while (1) {
        clearScreen();
        printf("\nDevice List:\n");
        for (int i = 0; i < numDevices; i++) {
            printf("%d. %s (%s) - %s [ON time: %ld seconds]\n",
                   i + 1, devices[i * 2], devices[i * 2 + 1], statuses[i], totalOnTimes[i]);
        }

        printf("\nSelect a device to toggle (1-%d), or 0 to quit: ", numDevices);
        char input[10];
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0'; // Remove newline character

        if (!isValidNumericInput(input)) {
            printf("Invalid input. Please enter a valid number.\n");
            printf("Press Enter to continue...");
            fgets(input, sizeof(input), stdin);
            continue;
        }

        int choice = atoi(input);

        if (choice == 0) {
            break;
        }

        if (choice < 1 || choice > numDevices) {
            printf("Invalid choice. Please try again.\n");
            continue;
        }

        int index = choice - 1;
        // Toggle device status
        if (strcmp(statuses[index], "OFF") == 0) {
            strcpy(statuses[index], "ON");
            startTimes[index] = time(NULL);  // Record the start time
        } else {
            strcpy(statuses[index], "OFF");
            if (startTimes[index] != 0) {
                time_t endTime = time(NULL);
                long duration = endTime - startTimes[index];
                totalOnTimes[index] += duration;
                startTimes[index] = 0;
                saveTotalOnTimes(totalOnTimes, numDevices, devices, username);  // Update timelog.txt
            }
        }

        // Log the status change
        logStatusChange(devices[index * 2], statuses[index], username);
    }

    printf("Exiting program.\n");
    return 0;
}
