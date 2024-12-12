#include "header.h"

void	screen()
{
    printf("                 ______________________________________________________\n");
    printf("               /                                                       \\\n");
    printf("             /   ____________________________________________________    \\\n");
    printf("            |   |                                                    |    |\n");
    printf("            |   |type \"exit\" to quit program.                        |    |\n");
    printf("            |   |type \"logout\" to go to lobby.                       |    |\n");
    printf("            |   |type \"clear\" to clear terminal-text.                |    |\n");
    printf("            |   |type \"device\" to manage your device.                |    |\n");
    printf("            |   |type \"use\" to turn on your device.                  |    |\n");
    printf("            |   |type \"cal\" to calculate your electric cost.         |    |\n");
    printf("            |   |                                                    |    |\n");
    printf("            |   |                                                    |    |\n");
    printf("            |   |                                                    |    |\n");
    printf("            |   |                                                    |    |\n");
    printf("            |   |                                                    |    |\n");
    printf("            |   |____________________________________________________|    |\n");
    printf("             \\                                                           /\n");
    printf("               \\________________________________________________________/\n");
    printf("                         \\___________________________________/\n");
    printf("                      ___________________________________________\n");
    printf("                   _-'    .-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.  --- `-_\n");
    printf("                _-'.-.-. .---.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.  .-.-.`-_\n");
    printf("             _-'.-.-.-. .---.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-`__`. .-.-.-.`-_\n");
    printf("          _-'.-.-.-.-. .-----.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-----. .-.-.-.-.`-_\n");
    printf("       _-'.-.-.-.-.-. .---.-. .-------------------------. .-.---. .---.-.-.-.`-_\n");
    printf("      :-------------------------------------------------------------------------:\n");
    printf("      :-------------------------------------------------------------------------:\n");
}

void	device_manager(const char *username)
{
	int	choice;

	while (choice != 5)
	{
		printf("\n=== Device Manager ===\n");
		printf("1. View Device List\n");
		printf("2. Add Device\n");
		printf("3. Delete  Device\n");
		printf("4. Edit Device\n");
		printf("5. go back\n");
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
				editDevice(username);
				break;
			case 5:
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
		screen();
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
	else if (ft_strcmp(input, "cal") == 0)
	{
		electric(username);
	}
	else if (ft_strcmp(input, "use") == 0)
	{
		usedevice(username);
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
		printf("%s pls enter command : ", current_user);
		parse_cmd(strinput(str), current_user);
	}
}
