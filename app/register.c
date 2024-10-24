#include "header.h"

void	toregister(void)
{
	FILE	*file;
	char	username[MAX_USERNAME_LENGTH];
	char	password[MAX_PASSWORD_LENGTH];

	file = fopen(KEEP_USERS, "a");
	if (file == NULL)
	{
		printf("Error opening file\n");
		return;
	}
	system(CLEAR_CMD);
	printf("===== REGISTER =====\n");
	printf("Enter your username: ");
	scanf("%s", username);
	printf("Enter your password: ");
	scanf("%s", password);

	fprintf(file, "%s %s\n", username, password);
	fclose(file);
}
