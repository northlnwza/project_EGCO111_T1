#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

#define PowerRate 4

typedef struct {
    char numList[50];
    char lists[30];
    float energy;
    float cost;
    float hours;
    int days;
    int watt;
} Appliance;

Appliance appliance[50];
int appliance_count = 0;

void displayMenu(void);
void inputAppliance(void);
void displaySummary(void);
int  PickupWatt(int);
void calculateEnergyandCost(void);
int  showListAppliance(void);

int main()
{
    int choice;

    do {
        displayMenu();

        printf("Enter your choice: ");
        scanf("%d", &choice);

        fflush(stdin);
        
        switch (choice)
        {
            case 1 :
                showListAppliance();
                inputAppliance();
                break;
            case 2 :
                displaySummary();
                break;
            // case 3 :
            //     printf("3. Compare Appliances\n");
            case 4 :
                printf("Loading...\r");
                fflush(stdout); 
                sleep(1);
                printf("Exiting...");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }

    } while (choice != 4);
    return 0;
}

void displayMenu(void)
{
    printf("\n--- Electricity Usage Calculator ---\n");
    printf("1. Input Appliance Data\n");
    printf("2. View Usage Summary\n");
    printf("3. Compare Appliances\n");
    printf("4. Exit\n");
}


void inputAppliance(void)
{
    int i = 0, check, error, numList;

    do{
        printf("\nEnter Appliance Number [Press 1-10]: ");
        scanf(" %s", appliance[appliance_count].numList);
        while(getchar() != '\n');
        numList = atoi(appliance[appliance_count].numList);
        check = PickupWatt(numList);  
    } while(check == 1);

    printf("Enter hours used per day: ");
    scanf("%f", &appliance[appliance_count].hours);

    printf("Enter number of days used per month: ");
    scanf("%d", &appliance[appliance_count].days);

    

    appliance_count++;
}

void displaySummary(void)
{
    float totalEnergy = 0, totalCost = 0;
    calculateEnergyandCost();
    
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

int PickupWatt(int numList)
{
    int count = 0;
    char check[4];
    FILE *pickup;
    pickup = fopen("Device.txt", "r");

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

void calculateEnergyandCost(void)
{
    for(int i = 0; i < appliance_count; i++)
    {
        appliance[i].energy = appliance[i].watt * appliance[i].hours * appliance[i].days;
        appliance[i].cost = (appliance[i].energy / 1000) * PowerRate;
    }
}

int showListAppliance(void)
{
	char	str[100];
    int i;
    FILE* f;
    f = fopen("Device.txt", "r");
    char info;

    printf("----------------------------\n");
    printf("List of Devices\n");
	printf("device   watt\n");
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
/*
    while((info = fgetc(f)) != EOF)
    {
        if(count == 1)
        {
            printf("1. ");
            count++;
        }    
        if(info == '\n')
        {
            printf(" Watt");
            printf("\n");
            printf("%d. ", count);
            count++;
        }
        else 
            printf("%c", info);
    }
    printf(" Watt");
    printf("\n----------------------------");
*/
    fclose(f);
}
