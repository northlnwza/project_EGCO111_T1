#include "header.h"

struct User
{
	char	username[MAX_USERNAME_LENGTH];
	char	password[MAX_PASSWORD_LENGTH];
};

int	identifier(struct User *user, char *Input_Username, char *Input_Password)
{
	if (ft_strcmp(user->username, Input_Username) == 0 && ft_strcmp(user->password, Input_Password) == 0)
		return (1);
	return (0);
}

int	login(void)
{
	int	attempts;
	char	Input_Username[MAX_USERNAME_LENGTH];
	char	Input_Password[MAX_PASSWORD_LENGTH];
	//to specify what is correct username & password
	struct User user;			
	ft_strcpy(user.username, "admin");
	ft_strcpy(user.password, "1234");

	attempts = 0;
	while (attempts < MAX_TRIES)
	{
		printf("EnterUsername: ");
		strinput(Input_Username);
		fflush(stdin);
		printf("EnterPassword: ");
		strinput(Input_Password);
		fflush(stdin);
		if (identifier(&user, Input_Username, Input_Password) == 1)
		{
			printf("Login Successfully ! welcome %s \n", user.username);
			return (1);
		}
		else if (attempts != MAX_TRIES - 1)
			printf("Invalid username or password. Please try again.\n");
		attempts++;	
	}
	printf("Too many failed attempts. Access denied.\n");
	return (0);
}

