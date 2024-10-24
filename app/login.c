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
		if (ft_strcmp(username, Input_Username) == 0 && ft_strcmp(password, Input_Password) == 0)
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
		printf("===== LOGIN ====\n");
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
