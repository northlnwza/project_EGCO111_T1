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

void	create_user_bill(const char *path)
{
	FILE	*f;
	char	PAID[MAX_USERNAME_LENGTH + 20 + 20];	
	char	UNPAID[MAX_USERNAME_LENGTH + 20 + 20];	
	char	AmountBill[MAX_USERNAME_LENGTH + 20 + 20];	

	sprintf(PAID, "%s/PAID", path);
	sprintf(UNPAID, "%s/UNPAID", path);
	sprintf(AmountBill, "%s/Amount_of_bills.txt", path);
	mkdir(PAID, 0777);
	mkdir(UNPAID, 0777);
	f = fopen(AmountBill, "w");
	if (f == 0)
	{
		printf("error\n");
		return;
	}
	fclose(f);
}

void	create_user_dir(const char *username)
{
	char	user_dir_path[MAX_USERNAME_LENGTH + 20];

	mkdir(USERS_DIR, 0777);
	sprintf(user_dir_path, "%s/%s", USERS_DIR, username);

	if(mkdir(user_dir_path, 0777) == -1)
	{
		printf("Error creating user folder.\n");
	}
	else
	{
		create_user_bill(user_dir_path);
		printf("User folder create at %s.\n", user_dir_path);
	}
	
}

int	checkdup(char	*username)
{
	FILE	*f;
	char	name[MAX_USERNAME_LENGTH];
	char	password[MAX_PASSWORD_LENGTH];

	f = fopen(KEEP_USERS, "r");
	if (f == 0)
	{
		printf("Error opening file\n");
		return (2);
	}
	while (fscanf(f, "%s %s", name, password) != EOF)
	{
		if (strcmp(username, name) == 0)
			return (1);
	}	
	fclose(f);
	return (0);
}

void    toregister(void)
{
        FILE    *file;
        char    username[MAX_USERNAME_LENGTH];
        char    password[MAX_PASSWORD_LENGTH];
	int	ischeckdup;

        file = fopen(KEEP_USERS, "a");
        if (file == NULL)
        {
                printf("Error opening file\n");
                return;
        }
        system(CLEAR_CMD);
        printf("===== REGISTER =====\n");
	/*
        printf("Enter your username: ");
       	scanf("%s", username);
	*/
	while (1)
	{
        	printf("Enter your username: ");
        	scanf("%s", username);
		ischeckdup = checkdup(username);
		if (ischeckdup == 1)
			printf("this name already taken!\n");
		else if (ischeckdup == 0)
			break;
	}
        printf("Enter your password: ");
        scanf("%s", password);
	getchar();
        fprintf(file, "%s %s\n", username, password);
        fclose(file);
	create_user_dir(username);
	while(1)
	{
		printf("\nType any key to go back to lobby");
		if(getchar()) 
			break;
	}
}
