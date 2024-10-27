#include "header.h"

void	device_manager(const char *username)
{
	int	choice;

	while (choice != 4)
	{
		printf("\n=== Device Manager ===\n");
		printf("1. View Device List\n");
		printf("2. Add Device\n");
		printf("3. Delete  Device\n");
		printf("4. go back\n");
		printf("\n======================\n");
		printf("Enter your choice: ");
		scanf("%d", &choice);
		getchar();
		switch (choice)
		{
			case 1:
				viewDevice(username);
				break;
			case 2:
				addDevice(username);
				break;
			case 3:
				deleteDevice(username);
				break;
			case 4:
				printf("go back to command page ...\n");
				break;
			default:
				printf("Invalid choice, try again.\n");
		}
		
	}
}

void	parse_cmd(char *input, const char *username)
{
	if (ft_strcmp(input, "help") == 0)
	{
		system(CLEAR_CMD);		
		printf("-----------------------------\n");
		printf("type \"exit\" to quit program.\n");
		printf("type \"logout\" to go to lobby.\n");
		printf("type \"clear\" to clear terminal-text.\n");
		printf("type \"device\" to clear terminal-text.\n");
		printf("-----------------------------\n");
	}
	else if (ft_strcmp(input, "exit") == 0)
	{
		printf("Bye Bye Bye ...\n");
		exit(0);
	}
	else if (ft_strcmp(input, "logout") == 0)
	{
		lobby();
	}
	else if (ft_strcmp(input, "clear") == 0)
	{
		system(CLEAR_CMD);
	}
	else if (ft_strcmp(input, "device") == 0)
	{
		device_manager(username);
	}
	else 
		printf("type \"help\" to see all command program\n");
}

void	outline(char *current_user)
{
	char	str[MAX_INPUT_LENGTH];

	system(CLEAR_CMD);
	printf("Login Successfully ! welcome %s \n", current_user);
	while (1)
	{
		printf("user:%s\n", current_user);
		printf("pls enter command : ");
		parse_cmd(strinput(str), current_user);
	}
}
