#include "header.h"
	
void	lobby()
{
	int	choice;
	char temp[100];

	while (1)
	{
		system(CLEAR_CMD);
printf("=========================================\n");
printf("  L      OOO    BBBBB  	BBBBB   Y     Y\n");
printf("  L     O   O   B    B  B    B   Y   Y\n");
printf("  L     O   O   BBBBB   BBBBB     Y Y\n");
printf("  L     O   O   B    B  B    B     Y\n");
printf("  LLLLL  OOO    BBBBB   BBBBB      Y\n");
printf("=========================================\n");
		printf("1. Register\n");
		printf("2. Login\n");
		printf("3. Exit\n");
		printf("Enter your choice: ");
		fgets(temp, sizeof(temp), stdin);

        // Validate if the input is a number
        if (sscanf(temp, "%d", &choice) != 1 || (choice < 1 || choice > 3))
			{
    		printf("Invalid choice. Press Enter to retry.\n");
    		while (getchar() != '\n'); // Clear the input buffer
    		continue; // Skip this loop iteration and ask again
			}
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
