#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void parse_command(char *command) {
    if (strcmp(command, "help") == 0) {
        printf("Available commands:\n");
        printf("  help - Display this help message\n");
        printf("  exit - Exit the program\n");
    } else if (strcmp(command, "exit") == 0) {
        printf("Exiting...\n");
        exit(0);
    } else {
        printf("Invalid command. Type 'help' for more information.\n");
    }
}

int main() {
    char command[100];

    printf("Enter a command: ");
    while (fgets(command, sizeof(command), stdin) != NULL) {
        command[strcspn(command, "\n")] = 0; // Remove newline character
        parse_command(command);
        printf("Enter a command: ");
    }

    return 0;
}
