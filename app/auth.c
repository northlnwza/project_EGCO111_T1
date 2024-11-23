#include "header.h"

int	identifier(char *filename, char *Input_Username, char *Input_Password)
{
	FILE	*file;
	char	username[MAX_USERNAME_LENGTH];
	char	password[MAX_USERNAME_LENGTH];


	file = fopen(filename, "r");
	if (file == NULL)
	{
		printf("Error openning file.\n");
		return (0);
	}
	while (fscanf(file, "%s %s", username, password) != EOF)
	{
		if (strcasecmp(username, Input_Username) == 0 && strcasecmp(password, Input_Password) == 0)
		{	
			fclose(file);
			return (1);
		}
	}
	fclose(file);
	return (0);
}

int	login(void)
{
	int	attempts;
	char	Input_Username[MAX_USERNAME_LENGTH];
	char	Input_Password[MAX_PASSWORD_LENGTH];
	char	*filename;

	filename = KEEP_USERS;
	attempts = 0;
	system(CLEAR_CMD);
	while (attempts < MAX_TRIES)
	{
printf("===================================\n");
printf("  L      OOO   GGGGG   III  N   N\n");
printf("  L     O   O  G        I   NN  N\n");
printf("  L     O   O  G  GG    I   N N N\n");
printf("  L     O   O  G   G    I   N  NN\n");
printf("  LLLLL  OOO   GGGGG   III  N   N\n");
printf("===================================\n");
		printf("EnterUsername: ");
		scanf("%s", Input_Username);
		printf("EnterPassword: ");
		scanf("%s", Input_Password);
		getchar(); //to clear leftover whitespace input. 
		if (identifier(filename, Input_Username, Input_Password) == 1)
		{
			outline(Input_Username);
			return (1);
		}
		else if (attempts != MAX_TRIES - 1)
			printf("Invalid username or password. Please try again.\n");
		attempts++;	
	}
	printf("Too many failed attempts. Access denied.\n");
	return (0);
}

void	create_user_dir(const char *username)
{
	char	user_dir_path[MAX_USERNAME_LENGTH + 20];

	mkdir(USERS_DIR);
	sprintf(user_dir_path, "%s/%s", USERS_DIR, username);

	if(mkdir(user_dir_path) == -1)
	{
		printf("Error creating user folder.\n");
	}
	else
		printf("User folder create at %s.\n", user_dir_path);
	
}

void    toregister(void)
{
        FILE    *file;
        char    username[MAX_USERNAME_LENGTH];
        char    password[MAX_PASSWORD_LENGTH];
		char stored_username[MAX_USERNAME_LENGTH];
    	char stored_password[MAX_PASSWORD_LENGTH];
    	int user_exists = 0;

        file = fopen(KEEP_USERS, "r");
        if (file == NULL)
        {
                printf("Error opening file\n");
                return;
        }
        system(CLEAR_CMD);
printf("=========================================================\n");
printf("  RRRR    EEEEE  GGGGG  III  SSSSS  TTTTT  EEEEE  RRRR   \n");
printf("  R   R   E      G       I   S        T    E      R   R   \n");
printf("  RRRR    EEEE   G  GG   I   SSSSS    T    EEEE   RRRR    \n");
printf("  R  R    E      G   G   I       S    T    E      R  R    \n");
printf("  R   R   EEEEE  GGGGG  III  SSSSS    T    EEEEE  R   R   \n");
printf("=========================================================\n");

    while (1) {
        printf("Enter your username: ");
        scanf("%s", username);
        getchar(); // Clear the input buffer to prevent issues with subsequent inputs

        // Check if the username already exists in the file
        user_exists = 0;
        while (fscanf(file, "%s %s", stored_username, stored_password) != EOF) {
            if (strcasecmp(username, stored_username) == 0) {
                user_exists = 1;
                break;  // Username already exists, exit the loop
            }
        }
		        rewind(file);

        if (user_exists) {
            printf("Error: Username '%s' already exists. Please choose a different username.\n", username);
        } else {
            break;  // Valid username found, exit the loop
        }
    }
        printf("Enter your password: ");
        scanf("%s", password);
	getchar();

		file = fopen(KEEP_USERS, "a");
        fprintf(file, "%s %s\n", username, password);
        fclose(file);
	create_user_dir(username);
	while(1)
	{
		printf("\nType Enter key to go back to lobby");
		if(getchar()) 
			break;
	}
}
