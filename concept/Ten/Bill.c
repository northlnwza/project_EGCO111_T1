#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

#define Ft 0.3972
#define Service1 8.19
#define Service2 24.62

void SaveBills(void);
void ElectricCalculate(void);
int ViewbillsMenu(void);
void printMain(void);
void get_readingMeter(int*);
float inputData(int*, int*);
void print_bill(float, int, float);
float calculate_energy_cost(float, int);
void Lobbyforbill(void);
void savebill_infile(float, int, float, FILE*, char*);
void Viewpaid(int*);
void Listbill(int*);
void deletebill(void);
void	clearScreen()
{
	#ifdef _WIN32
		system("cls");
	#else
		system("clear");
	#endif
}

char	*strlwr(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] >= 'A' && s[i] <= 'Z')
			s[i] = s[i] - 'A' + 'a';
		i++;
	}
	return (s);
}

char	*strupr(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] >= 'a' && s[i] <= 'z')
			s[i] = s[i] - 'a' + 'A';
		i++;
	}
	return (s);
}

int main()
{
    int choice;
    int v;
    char check;
    char error;

    do{ 
        Lobbyforbill();     

        do {
            printf("Enter your choice: ");
            scanf("%d%c", &choice, &check);
            if(check != '\n')
                while (getchar() != '\n'); // Clear input buffer
            if (choice < 1 || choice > 4 || check != '\n') {
                printf("Invalid choice. Enter again!\n");
                sleep(1);
                printf("\033[2A\033[0J");
            }
        } while (choice < 1 || choice > 4 || check != '\n');

	clearScreen();	
        //system("cls");
        switch (choice)
        {
            case 1: 
                ElectricCalculate();
                break;
            case 2: 
                SaveBills();
                break;
            case 3:
                do {
                    v = ViewbillsMenu();
                    switch(v)
                    {
                        case 1: 
                            Viewpaid(&v);
                            break;
                        case 2: 
                            Viewpaid(&v);
                            break;
                        case 3:
                            deletebill();
                            break;
                        case 4: 
                            break;
                    }
			clearScreen();
                    //system("cls");
                } while(v != 4);
                break;
            case 4:
                break;
        }
	clearScreen();
        //system("cls");
    } while (choice != 4);
}

void Lobbyforbill(void)
{
    printf("Electricity Calculator in OUR House\n");
    printf("1. Calculate Electricity Usage Cost\n");
    printf("2. Save an Electricity bill\n");
    printf("3. View or Delete Electricity bills\n");
    printf("4. Go back\n");
}

void SaveBills(void)
{
    int meterType;
    int recent = 0, previous = 0;
    float cost, consumption;
    char file_path[200], status[200];
    char test, yn;
    
    do {
        printMain();
        get_readingMeter(&meterType);
        consumption = inputData(&recent, &previous);
        cost = calculate_energy_cost(consumption, meterType);

        printf("Status (paid / unpaid): ");
        fgets(status, sizeof(status), stdin);
        status[strcspn(status, "\n")]  = '\0';
        strupr(status);
        
        // while loop works even input is correctly format
        if(strcmp(status, "UNPAID") != 0 && strcmp(status, "PAID") != 0)
        {
            do {
                printf("Please enter status again!\n");
                printf("Status (paid / unpaid): ");
                fgets(status, 100, stdin);
                status[strcspn(status, "\n")]  = '\0';
                strupr(status);
            } while((strcmp(status, "UNPAID") != 0) && (strcmp(status, "PAID") != 0));
        }

        // get amount of bill in file 
        FILE* amount;
        int amountpaid, amountunpaid;
        amount = fopen("testuser/Amount_of_bills.txt", "r");
        fscanf(amount, "%d %d", &amountpaid, &amountunpaid);
        fclose(amount);
        
        // save bills
        if(strcmp(status, "PAID") == 0)
        {
            sprintf(file_path, "testuser/%s/bill%d.txt", status, amountpaid);
            amountpaid++;
        }
        else 
        {
            sprintf(file_path, "testuser/%s/bill%d.txt", status, amountunpaid);
            amountunpaid++;
        }

        FILE* save; 
        save = fopen(file_path, "w");
        savebill_infile(cost, meterType, consumption, save, status);
        fclose(save);

        // save amount of bills currently
        amount = fopen("testuser/Amount_of_bills.txt", "w");
        fprintf(amount, "%d %d\n", amountpaid, amountunpaid);
        fclose(amount);

        printf("\nSave an Electricity Bill Successfully!\n");
        printf("Add more? (y / n): ");
        scanf(" %c%c", &yn, &test);
        
        while(test != '\n' || (yn != 'y' && yn != 'n'))
        {
            while(getchar() != '\n');
            printf("Invalid choice!\n");
            printf("Add more? (y / n): ");
            scanf(" %c%c", &yn, &test);
        }
	clearScreen();
        //system("cls");
    } while(yn == 'y');
    
    printf("Press Any key to continue.\n");
    getc(stdin);
    while(getchar() != '\n');
}

int ViewbillsMenu()
{
    int choice;
    char error;

    printf("Select Option\n");
    printf("1. View Paid Bills\n");
    printf("2. View Unpaid Bills\n");
    printf("3. Delete Bills\n");
    printf("4. Go back\n");
    printf("Enter your choice: ");
    scanf("%d%c", &choice, &error);
    if(error != '\n')
    {
        choice = 10;
        while(getchar() != '\n');
    }
        
    return choice;
}

void Listbill(int* v)
{
    char file_path[100];
    int amountpaid, amountunpaid;

    FILE* amountbill;
    amountbill = fopen("testuser/Amount_of_bills.txt", "r");
    fscanf(amountbill, "%d %d", &amountpaid, &amountunpaid);
    fclose(amountbill);

    FILE* bill;
    if(*v == 1)
    {
        for(int i = 1; i < amountpaid; i++)
        {
            sprintf(file_path, "testuser/PAID/bill%d.txt", i);
            bill = fopen(file_path, "r");
            if(bill == NULL)
                continue;
            else
            {
                fclose(bill);
                printf("Bill #%d\n", i);
            }
        }
    }
    else
    {
        for(int i = 1; i < amountunpaid; i++)
        {
            sprintf(file_path, "testuser/UNPAID/bill%d.txt", i);
            bill = fopen(file_path, "r");
            if(bill == NULL)
                continue;
            else
            {
                fclose(bill);
                printf("Bill #%d\n", i);
            }
        }
    }
    fclose(bill);
}

void Viewpaid(int* v)
{
    int numbill;
    int error;
    char file_path[100];
    char check;
    // char printbill[150];
    int printbill;
    char ch;
    FILE* bill;

    do {
        system("cls");
        printf("==== List Bills ====\n");
        Listbill(v);
        printf("====================\n");

        error = 0;
        printf("Which Bill? Enter number: ");
        scanf("%d%c", &numbill, &check);
        if(check != '\n')
            while(getchar() != '\n');

        if(*v == 1)
            sprintf(file_path, "testuser/PAID/bill%d.txt", numbill);
        else
            sprintf(file_path, "testuser/UNPAID/bill%d.txt", numbill);

        bill = fopen(file_path, "r");

        if(bill == NULL || check != '\n')
        {
            error = 1;
            printf("This bill is not available. Please try again!\n");
            sleep(1);
        }
        else
        {
		clearScreen();
            //system("cls");
            while((printbill = fgetc(bill)) != EOF)
                printf("%c", printbill);
            printf("\n\n");
            fclose(bill);

            printf("View another bill? (y / n): ");
            do {
                scanf("%c%c", &ch, &check);
                if(check != '\n')
                    while (getchar() != '\n'); // Clear input buffer
                if (ch != 'y' && ch != 'n') {
                    printf("Invalid choice. Please enter (y / n): ");
                }
            } while (ch != 'y' && ch != 'n');
        }
    } while(error == 1 || ch == 'y');
}


void deletebill()
{
    char filelocate[100], choose[30];
    char check, choice;
    int numbill, error;
    int a = 1, b = 2;
    int *type;

    do {
	clearScreen();
        //system("cls");
        printf("==== List Bills ====\n");
        printf("PAID BILLS\n");
        type = &a;
        Listbill(type);
        printf("\nUNPAID BILLS\n");
        type = &b;
        Listbill(type);
        printf("====================\n");

        error = 0;
        do {
            printf("Enter status you want to delete (paid / unpaid): ");
            scanf("%s%c", choose, &check);
            strlwr(choose);
            if(check != '\n')
                while(getchar() != '\n');
            if((strcmp(choose, "paid") != 0 && strcmp(choose, "unpaid") != 0) || check != '\n')
                printf("Invalid Choice. Enter again!\n");
            sleep(1);
            printf("\033[2A\033[0J");
        } while ((strcmp(choose, "paid") != 0 && strcmp(choose, "unpaid") != 0) || check != '\n');
        
        printf("Which bills you want to delete? Enter number: ");
        scanf("%d", &numbill);

        if(strcmp(choose, "paid") == 0)
            sprintf(filelocate, "testuser/PAID/bill%d.txt", numbill);
        else
            sprintf(filelocate, "testuser/UNPAID/bill%d.txt", numbill);

        if(remove(filelocate) == 0)
        {
            do {
                printf("Do you want to delete more? (y / n): ");
                scanf("%c%c", &choice, &check);
                if(check != '\n')
                    while (getchar() != '\n'); // Clear input buffer
                if ((choice != 'y' && choice != 'n') || check != '\n') {
                    printf("Invalid choice. Enter again!\n");
                }
            } while (check != 'y' && check != 'n');
		clearScreen();
            //system("cls");
        }
        else
        {
            printf("This bill doesn't exist!");
            sleep(2);
		clearScreen();
            //system("cls");
            error = 1;
        }
    } while (check == 'y' || error == 1);
}

void ElectricCalculate(void)
{
    int meterType;
    int recent = 0, previous = 0;
    float cost, consumption;

    printMain();
    get_readingMeter(&meterType);
    consumption = inputData(&recent, &previous);
    cost = calculate_energy_cost(consumption, meterType);
    print_bill(cost, meterType, consumption);

    printf("Press Any key to continue.\n");
    getc(stdin);
    while(getchar() != '\n');
}

void printMain(void)
{
    printf("FOR House (Normal Rate)\n");
    printf("Select a type of Electricity meter: \n");
    printf("1. Using Energy less than 150 kWh per month\n");
    printf("2. Using Energy more than 150 kWh per month\n");
}

void get_readingMeter(int* meterType)
{
    char test;

    printf("\nPress [1 or 2]: ");
    scanf("%d%c", meterType, &test);

    while (test != '\n' || (*meterType != 1 && *meterType != 2))
    {
        printf("Invalid input. Please enter 1 or 2.\n");
        printf("Press [1 or 2]: ");
        scanf("%d%c", meterType, &test);
    } 
}

float inputData(int* recent, int* previous)
{
    char test;

    do {
        if(*recent < *previous)
            printf("Error: Recent reading cannot be less than Previous reading.\n");

        printf("Recent Reading (kWh): ");
        scanf("%d%c", recent, &test); 

        while (test != '\n')
        {
            printf("Invalid input. Please try again.\n");
            printf("Recent Reading (kWh): ");
            while(getchar() != '\n');
            scanf("%d%c", recent, &test);
        }


        printf("Previous Reading (kWh): ");
        scanf("%d%c", previous, &test);

        while (test != '\n')
        {
            printf("Invalid input. Please try again.\n");
            printf("Previous Reading (kWh): ");
            while(getchar() != '\n');
            scanf("%d%c", previous, &test);
        }  

    } while (*recent < *previous);

    return *recent - *previous;
}

void print_bill(float cost, int meterType, float consumption)
{ 
    float service;
    if(meterType == 1) service = Service1;
    else service = Service2;
    float totalNoVat = cost + service + (Ft * consumption);

    printf("\n--------------- Electricity Bill ----------------\n\n");
    printf("Part 1\n");
    printf("    Energy Payment (EP) %20.2f bath\n", cost);
    printf("    Service charge      %20.2f bath\n", service);
    printf("Part 2\n");
    printf("    Fuel Adjustment charge %17.2f bath\n", Ft * consumption);
    printf("Part 3\n");
    printf("    Value Added Tax (7%%) %19.2f bath\n\n", (totalNoVat) * 0.07);
    printf("Total Energy Consumed: %8.2f kWh\n", consumption);
    printf("Total Bill Amount (including VAT): %9.2f bath\n\n", totalNoVat + (totalNoVat * 0.07));
    printf("--------------------------------------------------\n");
}

void savebill_infile(float cost, int meterType, float consumption, FILE* save, char* status)
{
    float service;
    if(meterType == 1) service = Service1;
    else service = Service2;
    float totalNoVat = cost + service + (Ft * consumption);

    fprintf(save, "--------------- Electricity Bill ----------------\n\n");
    fprintf(save, "Part 1\n");
    fprintf(save, "    Energy Payment (EP) %20.2f bath\n", cost);
    fprintf(save, "    Service charge      %20.2f bath\n", service);
    fprintf(save, "Part 2\n");
    fprintf(save, "    Fuel Adjustment charge %17.2f bath\n", Ft * consumption);
    fprintf(save, "Part 3\n");
    fprintf(save, "    Value Added Tax (7%%) %19.2f bath\n\n", (totalNoVat) * 0.07);
    fprintf(save, "Total Energy Consumed: %8.2f kWh\n", consumption);
    fprintf(save, "Total Bill Amount (including VAT): %9.2f bath\n\n", totalNoVat + (totalNoVat * 0.07));
    fprintf(save, "Status: %s\n", status);
    fprintf(save, "--------------------------------------------------");
}

float calculate_energy_cost(float consumption, int meterType) {
    float cost = 0;

    if (meterType == 1) {
        if (consumption <= 15) cost += consumption * 2.3488;
        else if (consumption <= 25) cost += 15 * 2.3488 + (consumption - 15) * 2.9882;
        else if (consumption <= 35) cost += 15 * 2.3488 + 10 * 2.9882 + (consumption - 25) * 3.2405;
        else if (consumption <= 100) cost += 15 * 2.3488 + 10 * 2.9882 + 10 * 3.2405 + (consumption - 35) * 3.6237;
        else if (consumption <= 150) cost += 15 * 2.3488 + 10 * 2.9882 + 10 * 3.2405 + 65 * 3.6237 + (consumption - 100) * 3.7171;
        else if (consumption <= 400) cost += 15 * 2.3488 + 10 * 2.9882 + 10 * 3.2405 + 65 * 3.6237 + 50 * 3.7171 + (consumption - 150) * 4.2218;
        else cost += 15 * 2.3488 + 10 * 2.9882 + 10 * 3.2405 + 65 * 3.6237 + 50 * 3.7171 + 250 * 4.2218 + (consumption - 400) * 4.4217;
    } 
    else {
        if (consumption <= 150) cost += consumption * 3.2484;
        else if (consumption <= 400) cost += 150 * 3.2484 + (consumption - 150) * 4.2218;
        else cost += 150 * 3.2484 + 250 * 4.2218 + (consumption - 400) * 4.4217;
    }

    return cost;
}
