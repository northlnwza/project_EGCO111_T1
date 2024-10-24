#include "header.h"

void	parse_cmd(char *input)
{
	if (ft_strcmp(input, "help") == 0)
	{
		system(CLEAR_CMD);		
		printf("-----------------------------\n");
		printf("type \"exit\" to quit program.\n");
		printf("type \"logout\" to go to lobby.\n");
		printf("type \"clear\" to clear terminal-text.\n");
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
		parse_cmd(strinput(str));
	}
}
