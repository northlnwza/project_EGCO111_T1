#include "header.h"

void	parse_cmd(char *input)
{
	if (ft_strcmp(input, "help") == 0)
	{
		printf("type \"exit\" to quit program\n");
	}
	else if (ft_strcmp(input, "exit") == 0)
	{
		printf("Bye Bye Bye ...\n");
		free(input);
		exit(0);
	}
	else 
		printf("type \"help\" to see all command program\n");
}

void	outline(void)
{
	char	*str;
	int	status;

	status = 1;
	while (status)
	{
		printf("pls enter command : ");
		str = (char *)malloc(sizeof(char) * (MAX_INPUT_LENGTH + 1));
		if (str == 0)
			status = 0;
		parse_cmd(strinput(str));
		free(str);
	}
}
