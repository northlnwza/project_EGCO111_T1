#include "header.h" 

typedef struct {
    char numList[50];
    char lists[30];
    float energy;
    float cost;
    float hours;
    int days;
    int watt;
} Appliance;

void displayMenu(void);
void inputAppliance(const char *username, Appliance *appliance, int *ptr);
void displaySummary(Appliance *appliance, int appliance_count);
int  PickupWatt(int numList, const char *username, Appliance *appliance, int appliance_count);
void calculateEnergyandCost(Appliance *appliance, int appliance_count);
int  showListAppliance(const char *username);

int electric(const char *username)
{
    int choice;
	Appliance appliance[50];
	int	*ptr;
	int appliance_count = 0;
	
	ptr = &appliance_count;

    do {
        displayMenu();

        printf("Enter your choice: ");
        scanf(" %d", &choice);

        
        switch (choice)
        {
            case 1 :
                showListAppliance(username);
                inputAppliance(username, appliance, ptr);
                break;
            case 2 :
                displaySummary(appliance, appliance_count);
                break;
            case 3 :
                printf("Loading...\r");
                sleep(1);
                printf("Exiting...");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }

    } while (choice != 3);
    return 0;
}

void displayMenu(void)
{
    printf("\n--- Electricity Usage Calculator ---\n");
    printf("1. Input Appliance Data\n");
    printf("2. View Usage Summary\n");
    printf("3. Exit\n");
}


void inputAppliance(const char *username, Appliance *appliance, int *ptr)
{
    int  check, numList;
	int	appliance_count;

	appliance_count = *ptr;

    do{
        printf("\nEnter Appliance Number [Press integer]: ");
        scanf(" %s", appliance[appliance_count].numList);
        while(getchar() != '\n');
        numList = atoi(appliance[appliance_count].numList);
        check = PickupWatt(numList, username, appliance, *ptr);  
    } while(check == 1);

    printf("Enter hours used per day: ");
    scanf("%f", &appliance[appliance_count].hours);

    printf("Enter number of days used per month: ");
    scanf("%d", &appliance[appliance_count].days);

    
	*ptr = *ptr + 1;
    //appliance_count++;
}

void displaySummary(Appliance *appliance, int appliance_count)
{
    float totalEnergy = 0, totalCost = 0;
    calculateEnergyandCost(appliance, appliance_count);
    for(int i = 0; i < appliance_count; i++)
    {
        appliance[i].energy = appliance[i].watt * appliance[i].hours * appliance[i].days;
        appliance[i].cost = (appliance[i].energy / 1000) * PowerRate;
    }
	system(CLEAR_CMD); 
    printf("\n-------------------- Usage Summary --------------------\n");
    printf("Appliance              Energy (kWh)         Cost (bath)\n");
    printf("-------------------------------------------------------\n");
    for(int i = 0; i < appliance_count; i++)
    {
        printf("%d. %-22s %9.2f %19.2f\n", i+1, appliance[i].lists, (appliance[i].energy) / 1000, appliance[i].cost);
        totalEnergy += (appliance[i].energy) / 1000;
        totalCost += appliance[i].cost;
    }
    printf("\nTotal Energy: %.2f kWh\n", totalEnergy);
    printf("Total Cost: %.2f bath\n", totalCost);
}

int PickupWatt(int numList, const char *username, Appliance *appliance, int appliance_count)
{
	char	filepath[MAX_USERNAME_LENGTH + 30];
    int count = 0;
    FILE *pickup;

	sprintf(filepath, "%s/%s/device.txt", USERS_DIR, username);
    pickup = fopen(filepath, "r");

    while(fscanf(pickup, "%s %d", appliance[appliance_count].lists, &appliance[appliance_count].watt) == 2)
    { 
        count++;
        if(count == numList)
        {
            fclose(pickup);
            return 0;
        }
    } 
    fclose(pickup);
    printf("Appliance number not found!\n");
    return 1;
}

void calculateEnergyandCost(Appliance *appliance, int appliance_count)
{
    for(int i = 0; i < appliance_count; i++)
    {
        appliance[i].energy = appliance[i].watt * appliance[i].hours * appliance[i].days;
        appliance[i].cost = (appliance[i].energy / 1000) * PowerRate;
    }
}

int showListAppliance(const char *username)
{
	char	str[100];
	char	filepath[MAX_USERNAME_LENGTH + 30];
    int i;
    FILE* f;

	sprintf(filepath, "%s/%s/device.txt", USERS_DIR, username);
    f = fopen(filepath, "r");

    printf("----------------------------\n");
    printf("List of Devices\n");
    printf("----------------------------\n");
    if(f == NULL)
    {
        printf("Error opening file\n");
        return 1;
    }

	i = 0;
	while(fgets(str, sizeof(str), f))
	{
		printf("%d. %s", i + 1, str);
		i++;
	}
    printf("\n----------------------------\n");
    fclose(f);
	return (0);
}
