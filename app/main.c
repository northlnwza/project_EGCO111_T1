#include "header.h"
	
void	lobby()
{
	int	choice;

	while (1)
	{
		system(CLEAR_CMD);
		printf("\n===== LOBBY =====\n");
		printf("1. Register\n");
		printf("2. Login\n");
		printf("3. Exit\n");
		printf("Enter your choice: ");
		scanf("%d", &choice);
		switch (choice)
		{
			case 1:
				toregister();
				break;
			case 2:
				login();
				break;
			case 3:
				printf("Exiting...\n");
				exit(0);
			default:
				printf("Invalid choice. Please try again.\n");
		}
	}
	
}

int	main(void)
{
	lobby();
	return (0);
}
