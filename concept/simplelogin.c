#include <stdio.h>
#include <string.h>

#define MAX_TRIES 3

struct User {
    char username[100];
    char password[100];
};

// Function to check login credentials
int checkCredentials(struct User *user, const char *inputUsername, const char *inputPassword) {
    if (strcmp(user->username, inputUsername) == 0 && strcmp(user->password, inputPassword) == 0) {
        return 1;  // login successful
    }
    return 0;  // login failed
}

int main() {
    struct User user;
    strcpy(user.username, "admin");  // Hardcoded username
    strcpy(user.password, "1234");   // Hardcoded password

    char inputUsername[100];
    char inputPassword[100];
    int attempts = 0;

    printf("Welcome to the command-line login system!\n");

    while (attempts < MAX_TRIES) {
        printf("Enter username: ");
        scanf("%s", inputUsername);

        printf("Enter password: ");
        scanf("%s", inputPassword);

        if (checkCredentials(&user, inputUsername, inputPassword)) {
            printf("Login successful! Welcome %s.\n", user.username);
            return 0;  // Exit on success
        } else {
            printf("Invalid credentials. Please try again.\n");
            attempts++;
        }
    }

    printf("Too many failed attempts. Access denied.\n");
    return 1;
}
