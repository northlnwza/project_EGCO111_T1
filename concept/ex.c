#include <stdio.h>
#include <time.h>
#include <string.h>
#include <dirent.h>
#include <stdlib.h>
#include <unistd.h>
#include <windows.h>
#include <dos.h>
#include <direct.h>
#include <conio.h>
#include <sys/stat.h>
#include <sys/types.h>

#define MAX_LINE_LENGTH 1000
#define MAX_PATH_LENGTH 256
#define MAX_LINE_LENGTH 256

void input_day(char *filed);
void input_time();
void input_header(char *filen);
void input_info();
void merge(char *filen, char *filed, char nameofuser[]);
void set_day(int Day, int Month, int Year);
int validate_date(int Day, int Month, int Year);
int list_file(char listuserpath[]);
void list_manage(char nameofuser[], char userdirname[]);
void view_task(char listuserpath[], char userdirname[],int n);
void delete_task(char listuserpath[]);
void edit_task(char listuserpath[], char userdirname[]);
void edit_taskMod(const char *filename, char userdir[]);
void centerText(const char *text);
void centerTextNoEnter(const char *text);
int view_notif(char nameofuser[]);
time_t convertToEpoch(const char *date_str, const char *time_str);
void convertSecondsToDHMS(double seconds, int *days, int *hours, int *minutes, int *secs);
int processFile(const char *filePath, int rownum);
int processNotif(const char *filePath, int rownum);
int processFileMod(const char *filePath);
int processFileReturnOnly(const char *filePath);
int processDirectory(const char *dirPath);
int processDirectoryNotif(const char *dirPath);
int processFileNotif(const char *filePath, int rownum);
int processDirectoryMod(const char *dirPath);
int UserLogin(char *mainname);
void UserSignUp();
int IsUsernameExists(const char* username);
int IsValidUsername(const char* username);
int IsBlank(const char* str);
void GetPassword(char* password);
int IsEnglishCharacter(char ch);
void createUserDirectory(const char* username);
int checkdigit(int maxdigit, char _input[10],int *number);
void DisplayMainPageHeader();
void ReturnToMainPage();
char* returndate(const char *filePath);
char* extractfilename(const char *filePath);
void checkDoneInFile(const char *filePath);
int countFilesInDirectory(const char *dirPath);
void check_task(char userpath[]);

struct user
{
    char username[50];
    char password[50];
    char loginusername[50];
    char loginpassword[50];
    char confpassword[50];
    char line[1024];
};



int main()
{
    int choice;
    DisplayMainPageHeader();

    while (1)
    {
        printf("         \n");
        printf("                                             {1. SignUp | 2. Login | 3. Exit}\n");
        printf("                                             ================================\n");
        printf("               Choose [1 - 3] : ");
        fflush(stdin);
        if (scanf("%d", &choice) != 1 || getchar() != '\n')
        {
            printf("Invalid input. Please enter a valid number.\n");
            while (getchar() != '\n');  // Clear the input buffer
            sleep(1);
            ReturnToMainPage();
            continue;
        }
        fflush(stdin);
        char mainname[50];

        switch (choice)
        {
        case 1:
            UserSignUp(); // Sign up Function
            sleep(2);
            ReturnToMainPage(); // After signup, return to the main page
            break;
        case 2:

            if(UserLogin(&mainname)==0)
            {
                sleep(2);
                ReturnToMainPage();
                break;
            };

            FILE *datefile,*headerfile,*infofile,*mergefile,*timefile;

            int opt;

            char* nameofuser = mainname;
            char *filen[50],*filed[50];
            char userpath[50] = "./";
            strcat(userpath,nameofuser);

            while(1)
            {

                int countnotif = processDirectoryMod(userpath); //using userpath
                //printf("\n");
                system("cls");
                printf("\n                                              Welcome to Task Creator : %s\n", nameofuser);
                centerText("***********************************************************************************\n");
                centerText("#-----------------------------/\\_/\\");
                centerText(" /\\ /\\                         =( 0 0 )=  ");
                centerText("  ||_||         TaskCreator       > ^ <    ");
                centerText(" ( 0 0 )                             |      ");
                centerText("|>^<|------------------------------#  \n");
                printf("\n");
                printf("\t\t    {1.Create New Task | 2. Tasks List | 3. Notification [%d]! | 4. Exit Program} : ",countnotif);
                fflush(stdin);
                if(scanf("%d",&opt)!=1)
                {
                    system("cls");
                    printf("\n");
                    centerText("-----------Invalid input!-----------\n\n");
                    continue;
                }
                fflush(stdin);
                switch(opt)
                {
                case 1:
                    printf("                 -------------------------------------------------------------------------------------\n");
                    input_day(&filed);
                    printf("                 ------------------------------");
                    input_time();
                    printf("                 -------------------------------\n");
                    input_header(&filen);
                    printf("                 -------------------------------\n");
                    input_info();
                    printf("                 -------------------------------\n");
                    merge(filen,filed,nameofuser); ////
                    break;
                case 2:
                    list_manage(nameofuser, userpath);
                    break;
                case 3:
                    view_notif(nameofuser); ////
                    break;
                case 4:
                    printf("\n");
                    centerText("--------Exit Program :/--------\n");
                    centerText("***********************************************************************************\n");
                    sleep(1);
                    break;
                default:
                    system("cls");
                    printf("\n");
                    centerText("-----------Invalid input!-----------\n\n");
                    break;
                }
                fflush(stdin);
                if(opt==4) break;
            }
            // Main Program

            ReturnToMainPage(); // After login, return to the main page

            break;
        case 3:
            printf("\n               Exit from the Program. See you next time :/\n"); // Exit from the program
            printf("\n             ************************************************************************************************\n\n");
            return 0;
        default:
            printf("Invalid choice. Please enter a number between 1 and 3.\n");
            sleep(1);
            ReturnToMainPage(); // After signup, return to the main page
            break;
        }
    }
}

void input_day(char *filed)
{
    char input[10];
    int i,j,k,a;

    while(1)
    {
        printf("\n                    Year: ");
        scanf("%[^ \t\n]", input);
        fflush(stdin);
        a = checkdigit(4,input,&k);
        if(a==0)
        {
            break;
        }
        else if(a==1)
            continue;
        printf("\n                    Invalid input!\n");
    }
    while(1)
    {
        printf("\n                    Month [1 - 12] : ");
        scanf("%[^ \t\n]", input);
        fflush(stdin);
        a = checkdigit(2,input,&i);
        if(a==0 && i>0 && i<=12)
        {
            break;
        }
        else if(a==1)
            continue;
        printf("\n                    Input must be within range [1 - 12]\n");
    }
    while(1){
        if(i == 2){
            if(k%4==0)
                printf("\n                    Day [1-29]: ");
            else
                printf("\n                    Day [1-28]: ");
        }else if(i==4 || i==6 || i==9 || i==11){
            printf("\n                    Day [1-30]: ");
        }else
            printf("\n                    Day [1-31]: ");
        scanf("%[^ \t\n]", input);
        fflush(stdin);
        a = checkdigit(2,input,&j);

        if(a==0){
            if(i == 2){
                if(k%4==0){
                    if(j>29 || j<1){
                    printf("\n                    Input must be within range [1 - 29]\n");
                       continue;
                    }
                }else{
                    if(j>28 || j<1){
                    printf("\n                    Input must be within range [1 - 28]\n");
                       continue;
                    }
                }

                break;
            }else if(i==4 || i==6 || i==9 || i==11){
                if(j>30 || j<1){
                    printf("\n                    Input must be within range [1 - 30]\n");
                    continue;
                }
                break;
            }else{
            if(j>31 || j<1){
                    printf("\n                    Input must be within range [1 - 31]\n");
                    continue;
                }
                break;
            }
        }
        else if(a==1)
            continue;
        break;
    }

    fflush(stdin);
    if (validate_date(j, i, k) == 0)
    {
        printf("\n                    Invalid date.\n");
        return 0;
    }
    sprintf(filed, "%d-%d-%d", k, j, i);
    fflush(stdin);
    set_day(j, i, k);
}

void input_time()
{
    FILE *timefile;
    timefile = fopen("Time.txt","w");
    char input[10];
    int hours,minutes,seconds,a;
    while(1)
    {
        printf("\n                    Enter hours [0 - 23]: ");
        if(scanf("%d", &hours)==1)
        {
            if(hours<0||hours>23)
            {
                printf("\n                    Input must be within range!\n");
                continue;
            }
            break;
        }
        printf("\n                    Invalid input!\n");
        fflush(stdin);
    }
    while(1)
    {
        printf("\n                    Enter minutes [0 - 59]: ");
        if(scanf("%d", &minutes)==1)
        {
            if(minutes<0||minutes>59)
            {
                printf("\n                    Input must be within range!\n");
                continue;
            }
            break;
        }
        printf("\n                    Invalid input!\n");
        fflush(stdin);
    }
    while(1)
    {
        printf("\n                    Enter seconds [0 - 59]: ");
        if(scanf("%d", &seconds)==1)
        {
            if(seconds<0||seconds>59)
            {
                printf("\n                    Input must be within range!\n");
                continue;
            }
            break;
        }
        printf("\n                    Invalid input!\n");
        fflush(stdin);
    }
    fprintf(timefile, "%02d:%02d:%02d", hours,minutes,seconds);
    fclose(timefile);
}

void set_day(int Day, int Month, int Year)
{
    FILE *datefile;
    datefile = fopen("Date.txt", "w");
    fprintf(datefile, "%d/%d/%d", Day, Month, Year);
    fclose(datefile);
}

int validate_date(int Day, int Month, int Year)
{
    if (Day < 0 || Day > 31)
    {
        return 0;
    }
    if (Month < 0 || Month > 12)
    {
        return 0;
    }
    if (Year < 0)
    {
        return 0;
    }
    if (Month == 2 && (Day > 29 || (Day == 28 && Year % 4 != 0)))
    {
        return 0;
    }
    if ((Month == 4 || Month == 6 || Month == 9 || Month == 11) && Day > 30)
    {
        return 0;
    }
    return;
}

void input_header(char *filen)
{
    fflush(stdin);
    char header[100];
    FILE *headerfile;
    headerfile = fopen("Header.txt","w");
    while(1)
    {
            printf("                    Input your task header : ");
            fgets(header, sizeof(header), stdin);
            header[strlen(header) - 1] = '\0';
            if(!IsValidUsername(header))
            {
                printf("                    Invalid header name.\n");
            }
            else break;
    }
    strcpy(filen,header);
    fputs(header,headerfile);
    fclose(headerfile);
}

void input_info()
{
    char info[1000];
    FILE *infofile;
    infofile = fopen("Info.txt","w");
    printf("                    Input your information : ");
    fgets(info, sizeof(info), stdin);
    info[strlen(info) - 1] = '\0';

    fputs(info, infofile);
    fclose(infofile);
}
void merge(char *filen,char *filed, char nameofuser[])
{
    FILE *datefile,*headerfile,*infofile,*mergefile,*timefile;

    datefile = fopen("Date.txt","r");
    headerfile = fopen("Header.txt","r");
    infofile = fopen("Info.txt","r");
    timefile = fopen("Time.txt","r");

    char path[100];
    char ch;
    char* dir_name = nameofuser; //using name of user
    char textfile[] = ".txt";

    strcat(filed, "-");
    strcat(filed, filen);
    strcat(filed, textfile); //task file name

    strcpy(path, dir_name); //path name
    strcat(path, "/");
    strcat(path, filed);

    if (access(dir_name, F_OK) == -1)
    {
        if (mkdir(dir_name) == -1)
        {
            perror("mkdir");
            return;
        }
    }
    if(datefile != NULL && timefile != NULL && headerfile != NULL && infofile != NULL)
    {
        mergefile = fopen(path,"w");
        printf("\n");
        centerText("Your Task has been Created!");
        centerText("===========================");
        printf("\n");
        centerText("***********************************************************************************\n");
        sleep(2);
        //system("cls");
    }
    else
    {
        centerText("Cannot Create Task!");
        centerText("========================");
        printf("\n");
        centerText("***********************************************************************************\n");

    }
    if (mergefile == NULL)
    {
        perror("fopen");
        return;
    }
    while((ch = fgetc(datefile))!=EOF)
    {
        fputc(ch, mergefile);
    }
    fprintf(mergefile,"\n");
    while((ch = fgetc(timefile))!=EOF)
    {
        fputc(ch, mergefile);
    }
    fprintf(mergefile,"\n");
    while((ch = fgetc(headerfile))!=EOF)
    {
        fputc(ch, mergefile);
    }
    fprintf(mergefile,"\n");
    while((ch = fgetc(infofile))!=EOF)
    {
        fputc(ch, mergefile);
    }
    fclose(datefile);
    fclose(timefile);
    fclose(headerfile);
    fclose(infofile);
    fclose(mergefile);
    fflush(stdin);
    sleep(1);
    system("cls");
}

void list_manage(char nameofuser[], char userdirname[])
{
    int opt_list;
    system("cls");
    while(1)
    {
        char* listusername = nameofuser;
        char listuserpath[100] = "./";
        strcat(listuserpath,listusername); //user path

        centerText("***********************************************************************************\n");
        printf("\n");
        centerText("-------------------------------");
        centerText("|            List Task          |");
        centerText("-------------------------------\n");
        centerText("List the task file in this window");
        centerText("=================================");
        printf("\n");

        int num = list_file(listuserpath); ////

        printf("\n");
        centerText("-------------------------------------------------------------------------------");
        centerTextNoEnter("List manage {1. View Task | 2. Edit Task | 3. Delete Task | 4. View all | 5. Check Task | 6. Main Menu} : ");
        fflush(stdin);
        if(scanf("%d",&opt_list)!=1)
        {
            system("cls");
            printf("\n");
            centerText("Invalid Input!\n");
            continue;
            fflush(stdin);
        }
        fflush(stdin);
        switch(opt_list)
        {
        case 1:
            view_task(listuserpath,userdirname,num);
            sleep(1);
            break;
        case 2:
            printf("\n                    Edit task?\n");
            edit_task(listuserpath,userdirname);
            sleep(1);
            break;
        case 3:
            printf("\n                    Delete task?\n");
            delete_task(listuserpath);
            sleep(1);
            break;
        case 4:
            list_fileMod(listuserpath);
            sleep(1);
            break;
        case 5:
            check_task(listuserpath);
            sleep(1);
            break;
        case 6:
            sleep(1);
            break;
        default:
            system("cls");
            printf("                      Invalid input!\n");
            break;
        }
        fflush(stdin);
        system("cls");
        if(opt_list==6) break;
    }
}

int list_file(char listuserpath[])
{
    DIR *dir = opendir(listuserpath);
    if (dir == NULL)
    {
        perror("Error opening directory");
        return;
    }
    struct dirent *entry;
    int row_number = 1;

    while ((entry = readdir(dir)) != NULL)
    {
        if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0)
        {
            printf("                      %d. %.*s\n", row_number++, (int)(strcspn(entry->d_name, ".")), entry->d_name);
            char filePath[MAX_PATH_LENGTH];
            snprintf(filePath, sizeof(filePath), "%s/%s", listuserpath, entry->d_name);
            checkDoneInFile(filePath);
        }

    }
    closedir(dir);
    return row_number-1;
}

void checkDoneInFile(const char *filePath)
{
    FILE *file = fopen(filePath, "r");
    if (file == NULL)
    {
        perror("Error opening file");
        return;
    }
    // Read the first 5 lines and check for "Done"
    char line[MAX_LINE_LENGTH];
    int lineCount = 0;
    while (fgets(line, sizeof(line), file) != NULL && lineCount < 5)
    {
        if (strstr(line, "Done") != NULL)
        {
            printf("                      --> Task Done <--\n");
            break;
        }
        lineCount++;
    }

    fclose(file);
}

void delete_task(char listuserpath[])
{
    int fileNumber;
    printf("                     Enter the number of the task to delete: ");
    scanf("%d", &fileNumber);

    DIR *dir = opendir(listuserpath);

    if (dir == NULL)
    {
        perror("No task found!");
        return;
    }

    struct dirent *entry;
    int currentFileNumber = 1;
    char fileName[50];

    while ((entry = readdir(dir)) != NULL)
    {
        if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0)
        {
            if (currentFileNumber == fileNumber)
            {
                strcpy(fileName, entry->d_name);
                break;
            }
            currentFileNumber++;
        }
    }

    closedir(dir);

    char fullPath[150];

    sprintf(fullPath, "%s/%s", listuserpath, fileName);

    char removeopt;
    while(1){
        printf("\n                    Are you sure [y/n] : ");
        scanf(" %c",&removeopt);
        fflush(stdin);
        if(removeopt == 'y' || removeopt == 'Y')
        {
            remove(fullPath);
            printf("\n");
            centerTextNoEnter("****Successfully Removed****");
            sleep(2);
            return;
        }
        else if(removeopt == 'n')
        {
            printf("\n");
            centerTextNoEnter("****Does not Removed****");
            sleep(2);
            return;
        }
        else
        {
            printf("\n");
            centerTextNoEnter("****Invalid Input!****");
        }
    }
}
void check_task(char userpath[])
{
    int fileNumber;
    printf("\n                    Enter the number of the task to Check: ");
    scanf("%d", &fileNumber);

    int fileCount = countFilesInDirectory(userpath);

    if(fileNumber > fileCount || fileNumber <= 0){
        centerTextNoEnter("No Task Found!");
        sleep(1);
        return;
    }

    DIR *dir = opendir(userpath);
    if (dir == NULL)
    {
        perror("Error opening directory");
        return;
    }

    struct dirent *entry;
    int currentFileNumber = 1;
    char fileName[50];

    while ((entry = readdir(dir)) != NULL)
    {
        if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0)
        {
            if (currentFileNumber == fileNumber)
            {
                strcpy(fileName, entry->d_name);
                break;
            }
            currentFileNumber++;
        }
    }

    closedir(dir);

    while(1)
    {
        char fullPath[150];
        sprintf(fullPath, "%s/%s", userpath, fileName);
        FILE *file;
        file = fopen(fullPath,"r");
        char ch;
        printf("\n                    Task Info:\n");
        printf("                    -------------------------------------------------------------------------------\n");

        int lineNumber = 1;
        int flagLine1 = 0, flagLine2 = 0, flagLine3 = 0, flagLine4 = 0, flagLine5 = 0;

        if(lineNumber == 1 && flagLine1 == 0)
        {
            printf("                    | Date   : ");
            flagLine1 = 1;
        }

        while ((ch = fgetc(file)) != EOF)
        {
            putchar(ch);
            if (ch == '\n')
            {
                lineNumber++;
            }
            if (lineNumber == 2 && flagLine2 == 0)
            {
                printf("                    | Time   : ");
                flagLine2 = 1;
            }
            if (lineNumber == 3 && flagLine3 == 0)
            {
                printf("                    | Header : ");
                flagLine3 = 1;
            }
            if (lineNumber == 4 && flagLine4 == 0)
            {
                printf("                    | Info   : ");
                flagLine4 = 1;
            }
            if (lineNumber == 5 && flagLine5 == 0)
            {
                printf("                    | Status : ");
                lineNumber = 10;
                flagLine5 = 1;
            }
        }

        processFileMod(fullPath);
        fclose(file);

        printf("                    -------------------------------------------------------------------------------\n\n");
        start:
        printf("\n                    Complete Task [y/n] : ");
        char opt;
        scanf(" %c", &opt);
        fflush(stdin);
        if(opt == 'y')
        {
            file = fopen(fullPath,"a");
            fputs("\nDone",file);
            fclose(file);
            break;
        }
        else if(opt == 'n')
        {
            fclose(file);
            break;
        }
        else
        {
            goto start;
        }
    }
}

void view_task(char listuserpath[], char userdirname[], int n)
{
    struct stat fileStat;
    int fileNumber;

    printf("\n                    Enter the number of the task to view: ");
    scanf("%d", &fileNumber);
    int fileCount = countFilesInDirectory(userdirname);

    if(fileNumber > fileCount || fileNumber <= 0){
        centerTextNoEnter("No Task Found!");
        sleep(1);
        return;
    }

    DIR *dir = opendir(listuserpath);
    if (dir == NULL)
    {
        perror("No task found!");
        return;
    }

    struct dirent *entry;
    int currentFileNumber = 1;
    char fileName[50];

    // Find the file corresponding to the selected number
    while ((entry = readdir(dir)) != NULL)
    {
        if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0)
        {
            if (currentFileNumber == fileNumber)
            {
                strcpy(fileName, entry->d_name);
                break;
            }
            currentFileNumber++;
        }
        if (stat(userdirname, &fileStat) == 0 && S_ISREG(fileStat.st_mode)) {
            fileCount++;
        }
    }

    closedir(dir);

    char fullPath[150];
    sprintf(fullPath, "%s/%s", listuserpath, fileName);

    while(1)
    {
        system("cls");

        char ch;
        FILE *file;
        file = fopen(fullPath,"r");

        printf("\n                    Task Info: \n");
        printf("                    -------------------------------------------------------------------------------\n");

        int lineNumber = 1;
        int flagLine1 = 0, flagLine2 = 0, flagLine3 = 0, flagLine4 = 0, flagLine5 = 0;

        if(lineNumber == 1 && flagLine1 == 0)
        {
            printf("                    | Date   : ");
            flagLine1 = 1;
        }
        while ((ch = fgetc(file)) != EOF)
        {
            putchar(ch);
            if (ch == '\n')
            {
                lineNumber++;
            }
            if (lineNumber == 2 && flagLine2 == 0)
            {
                printf("                    | Time   : ");
                flagLine2 = 1;
            }
            if (lineNumber == 3 && flagLine3 == 0)
            {
                printf("                    | Header : ");
                flagLine3 = 1;
            }
            if (lineNumber == 4 && flagLine4 == 0)
            {
                printf("                    | Info   : ");
                flagLine4 = 1;
            }
            if (lineNumber == 5 && flagLine5 == 0)
            {
                printf("                    | Status : ");
                lineNumber = 10;
                flagLine5 = 1;
            }
        }

        processFileMod(fullPath);
        fclose(file);
        printf("                    -------------------------------------------------------------------------------\n\n");
        char removeopt;
        int opt;
        fflush(stdin);
        centerTextNoEnter("Do you want to {1. Edit Task | 2. Delete Task | 3. Exit View} : ");
        scanf(" %d",&opt);
        printf("\n");
        if(opt == 3) break;
        switch(opt)
        {
        case 1:
            system("cls");
            edit_taskMod(fullPath, userdirname);
            break;
        case 2:
            while(1)
            {
                printf("                    Are you sure [y/n] : ");
                //char removeopt;
                scanf(" %c",&removeopt);
                fflush(stdin);
                if(removeopt == 'y' || removeopt == 'Y')
                {
                    remove(fullPath);
                    printf("\n");
                    centerTextNoEnter("****Successfully Removed****");
                    sleep(2);
                    break;
                }
                else
                {
                    centerTextNoEnter("****You did not remove this file****");
                    sleep(2);
                    system("cls");
                    break;
                }
            }
            break;
        case 3:
            break;
        default:
            printf("                   Invalid Input");
            break;
        }
        if(removeopt == 'y') return;
    }
}

void edit_task(char listuserpath[], char userdirname[])
{
    int fileNumber;
    printf("                    Enter the number of the task to edit: ");
    scanf("%d", &fileNumber);

    DIR *dir = opendir(listuserpath);
    if (dir == NULL)
    {
        perror("Error opening directory");
        return;
    }

    struct dirent *entry;
    int currentFileNumber = 1;
    char fileName[50];

    while ((entry = readdir(dir)) != NULL)
    {
        if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0)
        {
            if (currentFileNumber == fileNumber)
            {
                strcpy(fileName, entry->d_name);
                break;
            }
            currentFileNumber++;
        }
    }

    closedir(dir);

    char fullPath[150];
    sprintf(fullPath, "%s/%s",listuserpath, fileName);

    edit_taskMod(fullPath,userdirname);
}

void centerText(const char *text)
{
    int terminalWidth = 120;
    int spaces = (terminalWidth - strlen(text)) / 2;
    for (int i = 0; i < spaces; ++i)
    {
        printf(" ");
    }
    printf("%s\n", text);
}
void centerTextNoEnter(const char *text)
{
    int terminalWidth = 120;
    int spaces = (terminalWidth - strlen(text)) / 2;
    for (int i = 0; i < spaces; ++i)
    {
        printf(" ");
    }
    printf("%s", text);
}

time_t convertToEpoch(const char *date_str, const char *time_str)
{
    struct tm tm_struct = {0};

    sscanf(date_str, "%d/%d/%d", &tm_struct.tm_mday, &tm_struct.tm_mon, &tm_struct.tm_year);
    tm_struct.tm_mon -= 1;
    tm_struct.tm_year -= 1900;

    sscanf(time_str, "%d:%d:%d", &tm_struct.tm_hour, &tm_struct.tm_min, &tm_struct.tm_sec);

    return mktime(&tm_struct);
}

void convertSecondsToDHMS(double seconds, int *days, int *hours, int *minutes, int *secs)
{
    *days = seconds / (24 * 3600);
    seconds -= *days * (24 * 3600);
    *hours = seconds / 3600;
    seconds -= *hours * 3600;
    *minutes = seconds / 60;
    *secs = seconds - (*minutes * 60);
}

int processFileReturnOnly(const char *filePath)
{
    struct stat file_stat;

    if (stat(filePath, &file_stat) != 0)
    {
        perror("Error getting file information");
        return -1;
    }

    if (!S_ISREG(file_stat.st_mode))
    {
        return 0;
    }

    FILE *file = fopen(filePath, "r");

    if (file == NULL)
    {
        perror("Error opening file");
        return -1;
    }

    char date_str[20];
    char time_str[20];

    if (fgets(date_str, sizeof(date_str), file) == NULL)
    {
        perror("Error reading date");
        fclose(file);
        return -1;
    }

    if (fgets(time_str, sizeof(time_str), file) == NULL)
    {
        perror("Error reading time");
        fclose(file);
        return -1;
    }

    char buffer[100];
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        if (strstr(buffer, "Done") != NULL) {
            fclose(file);
            return 0;
        }
    }

    fclose(file);

    time_t file_time = convertToEpoch(date_str, time_str);

    time_t current_time = time(NULL);

    double time_difference = difftime(file_time, current_time);

    int days, hours, minutes, secs;
    convertSecondsToDHMS(time_difference, &days, &hours, &minutes, &secs);

    return (days < 10 && secs > 0) ? 1 : 0;
}

int processFileMod(const char *filePath)
{
    struct stat file_stat;

    if (stat(filePath, &file_stat) != 0)
    {
        perror("Error getting file information");
        return 1;
    }

    if (!S_ISREG(file_stat.st_mode))
    {
        // Not a regular file, ignore
        return 0;
    }

    FILE *file = fopen(filePath, "r");

    if (file == NULL)
    {
        perror("Error opening file");
        return 1;
    }

    char date_str[20];
    char time_str[20];

    if (fgets(date_str, sizeof(date_str), file) == NULL)
    {
        perror("Error reading date");
        fclose(file);
        return 1;
    }

    if (fgets(time_str, sizeof(time_str), file) == NULL)
    {
        perror("Error reading time");
        fclose(file);
        return 1;
    }

    fclose(file);

    time_t file_time = convertToEpoch(date_str, time_str);

    time_t current_time = time(NULL);

    double time_difference = difftime(file_time, current_time);

    int days, hours, minutes, secs;
    convertSecondsToDHMS(time_difference, &days, &hours, &minutes, &secs);

    if(secs > 0)
    {
        printf("\n\n                    Time Remaining : %d days, %d hours, %d minutes, %d seconds\n\n", days, hours, minutes, secs);
    }
    else
    {
        printf("\n                    Time has already passed :/\n");
    }

    return (days < 10) ? 1 : 0;
}

int view_notif(char nameofuser[])
{
    char userpath[50] = "./";

    strcat(userpath,nameofuser); //using userpath

    system("cls");
    centerText("***********************************************************************************\n");
    centerText("$--------------------------$ ");
    centerText("|                          | ");
    centerText(">  This is a notification  < ");
    centerText("|                          | ");
    centerText("$--------------------------$ ");
    printf("\n");
    int countfile;
    int opt;
    while(1)
    {
        const char *directoryPath = userpath;
        int count1 = processDirectoryMod(userpath);
        int count = processDirectoryNotif(directoryPath);


        if(count == 1)
        {
            printf("\n                                ***There is %d Task with less than 10 days remaining!*** \n",count1);
        }
        else
        {
            printf("\n                                ***There are %d Task with less than 10 days remaining!*** \n",count1);
        }
        countfile = count;
        printf("\n");
        centerTextNoEnter("{0. Exit} : ");
        scanf("%d",&opt);
        printf("\n");
        centerText("***********************************************************************************\n");
        sleep(1);
        if(opt == 0) break;
        else{
            return;
        }
    }

    system("cls");
}

int processFile(const char *filePath, int rownum)
{
    struct stat file_stat;

    if (stat(filePath, &file_stat) != 0)
    {
        perror("Error getting file information");
        return -1;
    }

    if (!S_ISREG(file_stat.st_mode))
    {
        return 0;
    }

    FILE *file = fopen(filePath, "r");

    if (file == NULL)
    {
        perror("Error opening file");
        return -1;
    }

    char date_str[20];
    char time_str[20];

    if (fgets(date_str, sizeof(date_str), file) == NULL)
    {
        perror("Error reading date");
        fclose(file);
        return -1;
    }

    if (fgets(time_str, sizeof(time_str), file) == NULL)
    {
        perror("Error reading time");
        fclose(file);
        return -1;
    }

    fclose(file);

    time_t file_time = convertToEpoch(date_str, time_str);

    time_t current_time = time(NULL);

    double time_difference = difftime(file_time, current_time);

    int days, hours, minutes, secs;
    convertSecondsToDHMS(time_difference, &days, &hours, &minutes, &secs);

    if(days < 10 && secs >= 0)
    {
        const char *filenameWithoutExtension = strrchr(filePath, '/');
        if (filenameWithoutExtension == NULL)
        {
            filenameWithoutExtension = filePath;
        }
        else
        {
            filenameWithoutExtension++; // Move past the '/'
        }

        char modifiedFilename[256];
        snprintf(modifiedFilename, sizeof(modifiedFilename), "%.*s", (int)(strcspn(filenameWithoutExtension, ".")), filenameWithoutExtension);

        printf("                    %d. %s\n\n", rownum, modifiedFilename);

        printf("                    Time Remaining : %d days, %d hours, %d minutes, %d seconds\n\n", days, hours, minutes, secs);
    }

    return (days < 10) ? 1 : 0;
}

int processFileNotif(const char *filePath, int rownum)
{
    struct stat file_stat;

    if (stat(filePath, &file_stat) != 0)
    {
        perror("Error getting file information");
        return -1;
    }

    if (!S_ISREG(file_stat.st_mode))
    {
        return 0;
    }

    FILE *file = fopen(filePath, "r");

    if (file == NULL)
    {
        perror("Error opening file");
        return -1;
    }

    char date_str[20];
    char time_str[20];

    if (fgets(date_str, sizeof(date_str), file) == NULL)
    {
        perror("Error reading date");
        fclose(file);
        return -1;
    }

    if (fgets(time_str, sizeof(time_str), file) == NULL)
    {
        perror("Error reading time");
        fclose(file);
        return -1;
    }

    char line[MAX_LINE_LENGTH];
    int lineCount = 0;

    char buffer[100];
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        if (strstr(buffer, "Done") != NULL) {
            fclose(file);
            return 0;
        }
    }

    fclose(file);

    time_t file_time = convertToEpoch(date_str, time_str);

    time_t current_time = time(NULL);

    double time_difference = difftime(file_time, current_time);

    int days, hours, minutes, secs;
    convertSecondsToDHMS(time_difference, &days, &hours, &minutes, &secs);
    if(days < 10 && secs > 0)
    {
        const char *filenameWithoutExtension = strrchr(filePath, '/');
        if (filenameWithoutExtension == NULL)
        {
            filenameWithoutExtension = filePath;
        }
        else
        {
            filenameWithoutExtension++; // Move past the '/'
        }

        char modifiedFilename[256];
        snprintf(modifiedFilename, sizeof(modifiedFilename), "%.*s", (int)(strcspn(filenameWithoutExtension, ".")), filenameWithoutExtension);

        printf("                    %d. %s\n\n", rownum, modifiedFilename);

        printf("                    Time Remaining : %d days, %d hours, %d minutes, %d seconds\n\n", days, hours, minutes, secs);
    }

    return (days < 10) ? 1 : 0;
}

int processDirectoryNotif(const char *dirPath)
{
    DIR *dir = opendir(dirPath);
    struct dirent *ent;

    if (dir == NULL)
    {
        perror("Error opening directory");
        return 1;
    }

    int filesWithLessThan10Days = 0;
    int rownum = -1;
    while ((ent = readdir(dir)) != NULL)
    {
        char filePath[256];
        snprintf(filePath, sizeof(filePath), "%s/%s", dirPath, ent->d_name);
        filesWithLessThan10Days += processFileNotif(filePath, rownum);
        rownum += 1;
    }

    closedir(dir);

    return filesWithLessThan10Days;
}

int processDirectory(const char *dirPath)
{
    DIR *dir = opendir(dirPath);
    struct dirent *ent;

    if (dir == NULL)
    {
        perror("Error opening directory");
        return 1;
    }

    int filesWithLessThan10Days = 0;
    int rownum = -1;
    while ((ent = readdir(dir)) != NULL)
    {
        char filePath[256];
        snprintf(filePath, sizeof(filePath), "%s/%s", dirPath, ent->d_name);
        filesWithLessThan10Days += processFile(filePath, rownum);
        rownum += 1;
    }

    closedir(dir);

    return filesWithLessThan10Days;
}

int processDirectoryMod(const char *dirPath)
{
    DIR *dir = opendir(dirPath);
    struct dirent *ent;

    if (dir == NULL)
    {
        perror("Error opening directory");
        return 1;
    }

    int filesWithLessThan10Days = 0;
    while ((ent = readdir(dir)) != NULL)
    {
        char filePath[256];
        snprintf(filePath, sizeof(filePath), "%s/%s", dirPath, ent->d_name);
        filesWithLessThan10Days += processFileReturnOnly(filePath);

    }

    closedir(dir);

    return filesWithLessThan10Days;
}

void edit_taskMod(const char *filename, char userdir[])
{
    FILE *file, *tempFile;
    int lineNumber;
    char newText[MAX_LINE_LENGTH];

    file = fopen(filename, "r");
    if (file == NULL)
    {
        centerText("Error opening the file.\n");
        return 1;
    }
    char ch;

    printf("\n                    Edit Task: \n");
    printf("                    -------------------------------------------------------------------------------\n");
    int lineNumber1 = 1;
    int flagLine1 = 0, flagLine2 = 0, flagLine3 = 0, flagLine4 = 0, flagLine5 = 0;

    if(lineNumber1 == 1 && flagLine1 == 0)
    {
        printf("                    | Date   : ");
        flagLine1 = 1;
    }

    while ((ch = fgetc(file)) != EOF)
    {
        putchar(ch);
        if (ch == '\n')
        {
            lineNumber1++;
        }
        if (lineNumber1 == 2 && flagLine2 == 0)
        {
            printf("                    | Time   : ");
            flagLine2 = 1;
        }
        if (lineNumber1 == 3 && flagLine3 == 0)
        {
            printf("                    | Header : ");
            flagLine3 = 1;
        }
        if (lineNumber1 == 4 && flagLine4 == 0)
        {
            printf("                    | Info   : ");
            flagLine4 = 1;
        }
        if (lineNumber1 == 5 && flagLine5 == 0)
        {
            printf("                    | Status : ");
            lineNumber = 10;
            flagLine5 = 1;
        }
    }
    processFileMod(filename);
    printf("                    -------------------------------------------------------------------------------\n");

    char *dbug = returndate(filename);
    char *fbug = extractfilename(filename);
    char formatdate[100], formatheader[100];
    strcpy(formatdate,dbug);
    strcpy(formatheader,fbug);
    free(dbug);
    free(fbug);

    fclose(file);

    file = fopen(filename, "r");
    if (file == NULL)
    {
        centerText("Error opening the file.\n");
        return 1;
    }

    tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL)
    {
        printf("                    Error creating a temporary file.\n");

        fclose(file);
        return 1;
    }

    printf("\n");
    centerTextNoEnter("{1. Edit Date | 2. Edit Time | 3. Edit Header | 4. Edit Info}: ");
    scanf("%d", &lineNumber); fflush(stdin);

    int currentLine = 1;
    while (currentLine < lineNumber && fgets(newText, MAX_LINE_LENGTH, file) != NULL)
    {
        fputs(newText, tempFile);
        currentLine++;
    }

    switch(lineNumber)
    {
        char input[10];
        int i,j,k,a;
        int hours,minutes,seconds;
    case 1:
        while(1)
        {
            printf("\n                    Year: ");
            scanf("%[^ \t\n]", input);
            fflush(stdin);
            a = checkdigit(4,input,&k);
            if(a==0)
            {
                break;
            }
            else if(a==1)
                continue;
            printf("\n                    Invalid input!\n");
        }
        while(1){
            printf("\n                    Month [1 - 12] : ");
            scanf("%[^ \t\n]", input);
            fflush(stdin);
            a = checkdigit(2,input,&i);
            if(a==0 && i>0 && i<=12)
            {
                break;
            }
            else if(a==1)
                continue;
            printf("\n                    Input must be within range [1 - 12]\n");
        }

        while(1){
            if(i == 2){
                if(k%4==0)
                    printf("\n                    Day [1-29]: ");
                else
                    printf("\n                    Day [1-28]: ");
            }else if(i==4 || i==6 || i==9 || i==11){
                printf("\n                    Day [1-30]: ");
            }else
                printf("\n                    Day [1-31]: ");
            scanf("%[^ \t\n]", input);
            fflush(stdin);
            a = checkdigit(2,input,&j);

            if(a==0){
                if(i == 2){
                    if(k%4==0){
                        if(j>29 || j<1){
                        printf("\n                    Input must be within range [1 - 29]\n");
                        continue;
                        }
                    }else{
                        if(j>29 || j<1){
                        printf("\n                    Input must be within range [1 - 29]\n");
                        continue;
                        }
                    }
                    break;
                }else if(i==4 || i==6 || i==9 || i==11){
                    if(j>30 || j<1){
                        printf("\n                    Input must be within range [1 - 30]\n");
                        continue;
                    }
                    break;
                }else{
                    if(j>31 || j<1){
                        printf("\n                    Input must be within range [1 - 31]\n");
                        continue;
                    }
                    break;
                }
            }
            else if(a==1)
                continue;
            break;
        }

        fflush(stdin);

        fprintf(tempFile, "%d/%d/%d\n",j,i,k);

        char newdate[50];
        sprintf(newdate,"%d-%d-%d-",k,j,i);

        fgets(newText, MAX_LINE_LENGTH, file);

        while (fgets(newText, MAX_LINE_LENGTH, file) != NULL)
        {
            fputs(newText, tempFile);
        }
        fclose(file);
        fclose(tempFile);

        char datenameedit[100];
        strcpy(datenameedit,userdir);
        strcat(datenameedit,"/");
        strcat(datenameedit,newdate);
        strcat(datenameedit,formatheader);
        strcat(datenameedit,".txt");
        sleep(3);
        remove(filename);
        rename("temp.txt", datenameedit);
        strcpy(filename,datenameedit);
        break;
    case 2:
        while(1)
        {
            printf("\n                    Enter hours [0 - 23]: ");
            if(scanf("%d", &hours)==1)
            {
                if(hours<0||hours>23)
                {
                    printf("\n                    Input must be within range!\n");
                    continue;
                }
                break;
            }
            printf("\n                    Invalid input!\n");
            fflush(stdin);
        }
        while(1)
        {
            printf("\n                    Enter minutes [0 - 59]: ");
            if(scanf("%d", &minutes)==1)
            {
                if(minutes<0||minutes>59)
                {
                    printf("\n                    Input must be within range!\n");
                    continue;
                }
                break;
            }
            printf("\n                    Invalid input!\n");
            fflush(stdin);
        }
        while(1)
        {
            printf("\n                    Enter seconds [0 - 59]: ");
            if(scanf("%d", &seconds)==1)
            {
                if(seconds<0||seconds>59)
                {
                    printf("\n                    Input must be within range!\n");
                    continue;
                }
                break;
            }
            printf("\n                    Invalid input!\n");
            fflush(stdin);
        }


        fprintf(tempFile, "%02d:%02d:%02d\n", hours,minutes,seconds);

        fgets(newText, MAX_LINE_LENGTH, file);

        while (fgets(newText, MAX_LINE_LENGTH, file) != NULL)
        {
            fputs(newText, tempFile);
        }

        fclose(file);
        fclose(tempFile);

        remove(filename);
        rename("temp.txt", filename);

        break;
    case 3:
        while(1)
        {
            printf("                      Enter the new Header: ");
            scanf(" %[^\n]", newText);
            if(!IsValidUsername(newText))
                {
                printf("                      Invalid Header name.\n");
                }
            else break;
        }

        char copytext[50];

        strcpy(copytext,newText);

        fprintf(tempFile, "%s\n", newText);

        fgets(newText, MAX_LINE_LENGTH, file);

        while (fgets(newText, MAX_LINE_LENGTH, file) != NULL)
        {
            fputs(newText, tempFile);
        }

        fclose(file);
        fclose(tempFile);

        char fname[100];
        strcpy(fname,userdir);
        char newHeader[50] = "-";

        strcat(newHeader,copytext);
        strcat(formatdate,newHeader);
        strcat(formatdate,".txt");
        strcat(fname,formatdate);
        remove(filename);
        rename("temp.txt", fname);
        strcpy(filename,fname);
        break;
    case 4:
        printf("                      Enter the new text: ");
        scanf(" %[^\n]", newText);
        fprintf(tempFile, "%s\n", newText);

        fgets(newText, MAX_LINE_LENGTH, file);

        while (fgets(newText, MAX_LINE_LENGTH, file) != NULL)
        {
            fputs(newText, tempFile);
        }

        fclose(file);
        fclose(tempFile);

        remove(filename);
        rename("temp.txt", filename);

        break;
    default:
        centerTextNoEnter("Invalid Input!\n");
        break;
    }

    if(lineNumber==1 ||lineNumber==2||lineNumber==3||lineNumber==4)
    {
        printf("\n");
        centerText("Task Edited successfully.");
        centerText("===========================");
        printf("\n");
    }

    centerText("***********************************************************************************\n");
    sleep(2);
}

void UserSignUp()
{
    struct user user;

    FILE *fp;
    fp = fopen("store.txt","a"); //open text file in appending mode
    int passwordmatched = 0;

    do
    {
        printf("\n               Input your username :\t");

        char ch;
        int i = 0;

        // Read the username character by character
        while (1)
        {
            ch = _getch();

            if (ch == 13)
            {
                user.username[i] = '\0';
                break;
            }
            else if (ch == 8)
            {
                if (i > 0)
                {
                    i--;
                    printf("\b \b");
                }
            }
            else if (ch != ' ')
            {
                user.username[i++] = ch;
                printf("%c", ch);
            }
        }

        if (IsBlank(user.username))
        {
            printf("\n               Username cannot be blank. Please try again.\n");
        }
        // Check if the entered username already exists
        else if (IsUsernameExists(user.username))
        {
            printf("\n               Username already exists. Please choose a different username.\n");
        }
        else if(!IsValidUsername(user.username))
        {
            printf("\n               Cannot use these special characters(\\ / : * ? \" < > |). Please try again. \n");
        }
        else
        {
            break;
        }

    }
    while (1);

    do
    {
        printf("\n               Input your password :\t");
        GetPassword(user.password);

        if (IsBlank(user.password))
        {
            printf("               Password cannot be blank. Please try again.\n");
        }
        else
        {
            printf("               Confirm your password :\t");
            GetPassword(user.confpassword);

            if (strcmp(user.password, user.confpassword) == 0)
            {
                printf("               Your password matched \n");
                passwordmatched = 1;
                printf("\n             ************************************************************************************************\n\n");
            }
            else
            {
                printf("               Your password and confirmation password don't match. Please try again.\n");
            }
        }
    }
    while (!passwordmatched);

    fputs("\n", fp);
    fputs(user.username, fp);
    fputs("\n", fp);
    fputs(user.password, fp);
    fputs("\n", fp); // this line to write confirmation password

    fclose(fp);
}

int IsUsernameExists(const char* username)
{
    FILE* fp = fopen("store.txt", "r");
    if (fp == NULL)
    {
        perror("Error opening file");
        exit(1);
    }

    char line[1024];
    while (fgets(line, sizeof(line), fp) != NULL)
    {
        line[strlen(line) - 1] = '\0';
        if (strcmp(username, line) == 0)
        {
            fclose(fp);
            return 1;
        }
    }

    fclose(fp);
    return 0;
}

int IsValidUsername(const char* username)
{
    const char* restrictedChars = "\\/:*?\"<>|";
    for (int i = 0; i < strlen(restrictedChars); i++)
    {
        if (strchr(username, restrictedChars[i]) != NULL)
        {
            return 0; // Invalid character found
        }
    }

    return 1;
}

int IsEnglishCharacter(char ch)
{
    return ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z'));
}

void GetPassword(char *password)
{
    int i = 0;
    char ch;
    while (1)
    {
        ch = getch();
        if (ch == 13)   // Enter key
        {
            password[i] = '\0';
            break;
        }
        else if (ch == 8)     // Backspace key
        {
            if (i > 0)
            {
                i--;
                printf("\b \b");
            }
        }
        else if (ch != ' ')
        {
            password[i] = ch;
            i++;
            printf("*");
        }
    }
    printf("\n");
}

int IsBlank(const char* str)
{
    for (int i = 0; i < strlen(str); i++)
    {
        if (str[i] != ' ')
        {
            return 0;
        }
    }
    return 1; // Blank
}

int UserLogin(char *mainname)
{
    struct user user;
    FILE *ft;
    int found = 0;
    int loginattempts = 0;

    ft = fopen("store.txt", "r");

    if (ft == NULL)
    {
        perror("Error opening file");
        return;
    }
    while (loginattempts < 3)
    {
        printf("\n               Enter Username : ");
        char ch;
        int i = 0;

        // Read the login username character by character
        while (1)
        {
            ch = _getch();

            if (ch == 13)
            {
                user.loginusername[i] = '\0';
                break;
            }
            else if (ch == 8)
            {
                if (i > 0)
                {
                    i--;
                    printf("\b \b"); // Move the cursor back and erase the character
                }
            }
            else if (ch != ' ')
            {
                user.loginusername[i++] = ch;
                printf("%c", ch);
            }
        }

        if (strlen(user.loginusername) == 0)
        {
            printf("\n               Username cannot be blank. Please try again.\n");
            continue; // Prompt user to re-enter the username
        }

        if (IsUsernameExists(user.loginusername))
        {
            printf("\n               Enter Password : ");
            GetPassword(user.loginpassword);

            while (fscanf(ft, "%s %s", user.username, user.password) == 2)
            {
                if (strcmp(user.loginusername, user.username) == 0 &&
                        strcmp(user.loginpassword, user.password) == 0)
                {
                    strcpy(mainname, user.loginusername);
                    createUserDirectory(user.loginusername);
                    found = 1;
                    break;
                }
            }

            if (!found)
            {
                printf("               Invalid Password! Please try again.\n");
                rewind(ft);
                loginattempts++;
            }
            else
            {
                break; // Exit the loop if login is successful
            }
        }
        else
        {
            printf("\n               Invalid Username! Please try again.\n");
            rewind(ft);
            loginattempts++;
        }
    }
    fclose(ft);

    if (loginattempts >= 3)
    {
        printf("\n               Too many invalid login attempts. Returning to the main page.\n\n");
        fclose(ft);
        sleep(2);
        system("cls"); //Clear the console screen
        return 0; // return to main page
    }
    return 1;
}

void DisplayMainPageHeader()   //Login Header
{
    printf("             ************************************************************************************************\n");
    printf("                                                                          /\\__/\\                                 \n");
    printf("                                              +--------------------------(^(00)^)                               \n");
    printf("                                              |                           >    <                              \n");
    printf("                                              /\\_/\\       Login System         |\n");
    printf("                                            =( 0 0 )=                          |\n");
    printf("                                              > ^ <----------------------------+\n\n");
}

void ReturnToMainPage() //Return to main page
{
    system("cls");
    DisplayMainPageHeader();

}

void createUserDirectory(const char* username)   //Create directory for user
{
    char directoryName[50];
    sprintf(directoryName, "%s", username);

    struct stat st = {0};
    if (stat(directoryName, &st) == -1)
    {
        if (mkdir(directoryName) != 0)
        {
            perror("Error creating directory");
            exit(EXIT_FAILURE);
        }
    }
}

int checkdigit(int maxdigit, char _input[10],int *number)
{
    fflush(stdin);
    int num;
    int i = 0;

    while (_input[i] != '\0')
    {
        if (!isdigit(_input[i]) || i>=maxdigit)
        {
            printf("\n                    Invalid input. Please enter %d digits number.\n",maxdigit);
            return 1;
        }
        i++;
    }

    sscanf(_input, "%d", &num);
    *number = num;

    return 0;
}

void displayFileContent(const char *filePath)
{
    FILE *file = fopen(filePath, "r");

    if (file == NULL)
    {
        perror("Error opening file");
        return;
    }

    char ch;
    printf("\n                    Task Info:\n");
    printf("                    -------------------------------------------------------------------------------\n");

    int lineNumber = 1;
    int flagLine1 = 0, flagLine2 = 0, flagLine3 = 0, flagLine4 = 0, flagLine5 = 0;

    if(lineNumber == 1 && flagLine1 == 0)
    {
        printf("                    | Date   : ");
        flagLine1 = 1;
    }

    while ((ch = fgetc(file)) != EOF)
    {
        putchar(ch);
        if (ch == '\n')
        {
            lineNumber++;
        }
        if (lineNumber == 2 && flagLine2 == 0)
        {
            printf("                    | Time   : ");
            flagLine2 = 1;
        }
        if (lineNumber == 3 && flagLine3 == 0)
        {
            printf("                    | Header : ");
            flagLine3 = 1;
        }
        if (lineNumber == 4 && flagLine4 == 0)
        {
            printf("                    | Info   : ");
            flagLine4 = 1;
        }
        if (lineNumber == 5 && flagLine5 == 0)
        {
            printf("                    | Status : ");
            lineNumber = 10;
            flagLine5 = 1;
        }
    }

    processFileMod(filePath);
    fclose(file);
    printf("                    -------------------------------------------------------------------------------\n\n");

    printf("\n\n");
}

void list_fileMod(char listuserpath[])
{
    system("cls");
    printf("\n                    View All Task\n\n");
    DIR *dir = opendir(listuserpath);

    if (dir == NULL)
    {
        perror("Error opening directory");
        return;
    }

    struct dirent *entry;
    int row_number = 1;

    while ((entry = readdir(dir)) != NULL)
    {
        if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0)
        {
            printf("                      %d. %.*s\n", row_number++, (int)(strcspn(entry->d_name, ".")), entry->d_name);
            char filePath[256];
            snprintf(filePath, sizeof(filePath), "%s/%s", listuserpath, entry->d_name);
            displayFileContent(filePath);
        }
    }
    closedir(dir);
    while(1)
    {
        int opt;
        centerTextNoEnter("{0. Exit} : ");
        scanf(" %d",&opt);
        if(opt == 0)
        {
            break;
        }
        else
        {
            printf("\n");
            centerText("Invalid Input!\n");
        }
    }
}

char* extractfilename(const char *filePath)
{
    const char *lastSlash = strrchr(filePath, '/');

    const char *startOfFileName = (lastSlash != NULL) ? lastSlash + 1 : filePath;

    const char *lastHyphen = strrchr(startOfFileName, '-');

    const char *startOfString = (lastHyphen != NULL) ? lastHyphen + 1 : startOfFileName;

    const char *lastDot = strrchr(startOfString, '.');

    size_t stringLength = (lastDot != NULL) ? (size_t)(lastDot - startOfString) : strlen(startOfString);

    char *result = malloc(stringLength + 1);

    strncpy(result, startOfString, stringLength);
    result[stringLength] = '\0';

    return result;
}

char* returndate(const char *filePath)
{
    FILE *file = fopen(filePath, "r");
    if (file == NULL)
    {
        perror("Error opening file");
        return NULL;
    }

    char date_str[11];

    if (fgets(date_str, sizeof(date_str), file) == NULL)
    {
        fclose(file);
        perror("Error reading date");
        return NULL;
    }

    fclose(file);

    int day, month, year;
    sscanf(date_str, "%d/%d/%d", &day, &month, &year);

    char *formatted_date = malloc(12);
    if (formatted_date == NULL)
    {
        perror("Memory allocation error");
        return NULL;
    }

    snprintf(formatted_date, 12, "/%04d-%02d-%02d", year, day, month);

    return formatted_date;
}

int countFilesInDirectory(const char *dirPath) {
    DIR *dir;
    struct dirent *entry;
    struct stat fileStat;
    int fileCount = 0;

    dir = opendir(dirPath);

    if (dir == NULL) {
        perror("Error opening directory");
        return -1;
    }

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        char filePath[1024];
        snprintf(filePath, sizeof(filePath), "%s/%s", dirPath, entry->d_name);

        if (stat(filePath, &fileStat) == 0 && S_ISREG(fileStat.st_mode)) {
            fileCount++;
        }
    }

    closedir(dir);

    return fileCount;
}
