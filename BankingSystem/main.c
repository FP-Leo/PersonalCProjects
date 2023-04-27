#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <conio.h>
#include <ctype.h>

void generalMenu();

int searchAccount(int);

unsigned tohash(char *, int, int);
int addEAccount(char *, int, unsigned int);
int searchEAccount(int);



int main()
{
    generalMenu();
    return 0;
}

unsigned tohash(char * value, int size, int multiplier){
    if(value == NULL)
        return 0;
    unsigned int hashvalue = 0;
    int i = 0;
    while(value[i] != '\0'){
        hashvalue = (value[i] + hashvalue*multiplier)%size;
        i++;
    }
    return hashvalue;
}

int searchAccount(int socialID){
    FILE *ptr;
    ptr = fopen("database.txt", "r");
    if(!ptr){
        printf("Error accessing the database!\n");
        return 0;
    }
    char line[256];
    int length = snprintf( NULL, 0, "%d", socialID);
    char * intToStr = malloc( length + 1 );
    snprintf(intToStr, length + 1, "%d", socialID);
    while(fgets(line, sizeof(line), ptr)){
        char * tobecompared = strtok(line, "-");
        if(!strcmp(tobecompared, intToStr)){
            fclose(ptr);
            free(intToStr);
            return 1;
        }
    }
    free(intToStr);
    fclose(ptr);
    return 0;
}

int addAccount(int socialID, char * name, double value, int notControlled){
    if(name == NULL || value < 0 ){
        printf("Wrong input!\n");
        return 0;
    }
    if(notControlled && searchAccount(socialID)){
        printf("An account with that ID already exists!\n");
        return 0;
    }
    FILE *ptr;
    ptr = fopen("database.txt", "a");
    if(!ptr){
        printf("Error accessing the database!\n");
        return 0;
    }
    fprintf(ptr, "%d-%s-%lf-\n", socialID, name, value);
    fclose(ptr);
    return 1;
}

int removeAccount(int socialID, int notControlled){
    if(notControlled && !searchAccount(socialID)){
        printf("An account with that ID doesn't exist!\n");
        return 0;
    }
    FILE *ptr;
    ptr = fopen("database.txt", "r+");
    if(!ptr){
        printf("Error accessing the database!\n");
        return 0;
    }
    FILE *fcopy;
    fcopy = fopen("temporarycopy.txt", "w");
    if(!fcopy){
        printf("Failed to create a txt file!\n");
        return 0;
    }
    char line[256];
    int length = snprintf( NULL, 0, "%d", socialID);
    char* intToStr = malloc( length + 1 );
    snprintf(intToStr, length + 1, "%d", socialID);
    char linecopy[256];
    while(fgets(line, sizeof(line), ptr)){
        strcpy(linecopy, line);
        char * tobecompared = strtok(linecopy, "-");
        if(!strcmp(tobecompared, intToStr)){
            continue;
        }
        fprintf(fcopy, line);
    }
    free(intToStr);
    fclose(ptr);
    fclose(fcopy);
    if(remove("database.txt")){
        printf("Failed to delete the original");
        return 0;
    }
    if(rename("temporarycopy.txt", "database.txt")){
        printf("Failed to rename the file\n");
        return 0;
    }
    return 1;
}

int changeAccountName(int socialID, char * updatedName){
    double getBalance(int);
    if(searchAccount(socialID)){
        double balance = getBalance(socialID);
        removeAccount(socialID, 0);
        addAccount(socialID, updatedName, balance, 0);
        return 1;
    }
    printf("An account with that ID doesn't exist!\n");
    return 0;
}

void changeBalance(int socialID, double balance){
    void getAccountName(int, char **);
    char * name;
    getAccountName(socialID, &name);
    removeAccount(socialID, 0);
    addAccount(socialID, name, balance, 0);
}

double getBalance(int socialID){
    FILE *ptr;
    ptr = fopen("database.txt", "r");
    if(!ptr){
        printf("Error accessing the database!\n");
        return 0;
    }
    char line[256];
    int length = snprintf( NULL, 0, "%d", socialID);
    char * intToStr = malloc( length + 1 );
    snprintf(intToStr, length + 1, "%d", socialID);
    while(fgets(line, sizeof(line), ptr)){
        char * tobecompared = strtok(line, "-");
        if(!strcmp(tobecompared, intToStr)){
            tobecompared = strtok(NULL, "-");
            tobecompared = strtok(NULL, "-");
            double balance = strtod(tobecompared, NULL);
            free(intToStr);
            fclose(ptr);
            return balance;
        }
    }
    return 0;
}

void getAccountName(int socialID, char **name){
    FILE *ptr;
    ptr = fopen("database.txt", "r");
    if(!ptr){
        printf("Error accessing the database!\n");
        return;
    }
    char line[256];
    int length = snprintf( NULL, 0, "%d", socialID);
    char * intToStr = malloc( length + 1 );
    snprintf(intToStr, length + 1, "%d", socialID);
    while(fgets(line, sizeof(line), ptr)){
        char * tobecompared = strtok(line, "-");
        if(!strcmp(tobecompared, intToStr)){
            tobecompared = strtok(NULL, "-");
            *name = malloc(strlen(tobecompared) + 1);
            strcpy(*name, tobecompared);
            free(intToStr);
            fclose(ptr);
            break;
        }
    }
}

int addEAccount(char * type, int socialID, unsigned int password){
    if(strcmp(type, "Admin") && strcmp(type, "User")){
        printf("Error creating E-Account, unknown type\n");
        return 0;
    }
    if(searchEAccount(socialID)){
        printf("An account already exists with that ID\n");
        return 0;
    }
    FILE * ptr;
    ptr = fopen("eaccount.txt", "a");
    fprintf(ptr, "%d-%d-%s-\n", socialID, password, type);
    fclose(ptr);
    return 1;
}

int searchEAccount(int socialID){
    FILE * ptr;
    ptr = fopen("eaccount.txt", "r");
    if(!ptr){
        printf("Failed accessing the database\n");
        return 0;
    }
    char line[256];
    int length = snprintf( NULL, 0, "%d", socialID);
    char * intToStr = malloc( length + 1 );
    snprintf(intToStr, length + 1, "%d", socialID);
    while(fgets(line, sizeof(line), ptr)){
        char * tobecompared = strtok(line, "-");
        if(!strcmp(tobecompared, intToStr)){
            free(intToStr);
            fclose(ptr);
            return 1;
        }
    }
    free(intToStr);
    fclose(ptr);
    return 0;
}

int getHashPass(int socialID){
    FILE * ptr;
    ptr = fopen("eaccount.txt", "r");
    char line[256];
    int length = snprintf( NULL, 0, "%d", socialID);
    char * intToStr = malloc( length + 1 );
    snprintf(intToStr, length + 1, "%d", socialID);
    while(fgets(line, sizeof(line), ptr)){
        char * tobecompared = strtok(line, "-");
        if(!strcmp(tobecompared, intToStr)){
            tobecompared = strtok(NULL, "-");
            int toint = strtol(tobecompared, NULL, 10);
            free(intToStr);
            fclose(ptr);
            return toint;
        }
    }
    free(intToStr);
    fclose(ptr);
    return 0;
}

void getAccountType(int socialID, int * type){
    FILE * ptr;
    ptr = fopen("eaccount.txt", "r");
    char line[256];
    int length = snprintf( NULL, 0, "%d", socialID);
    char * intToStr = malloc( length + 1 );
    snprintf(intToStr, length + 1, "%d", socialID);
    while(fgets(line, sizeof(line), ptr)){
        char * tobecompared = strtok(line, "-");
        if(!strcmp(tobecompared, intToStr)){
            tobecompared = strtok(NULL, "-");
            tobecompared = strtok(NULL, "-");
            if(!strcmp("Admin", tobecompared))
                *type = 1;
            else
                *type = 2;
            free(intToStr);
            fclose(ptr);
        }
    }
}

void generalMenu(){

    int logInMenu(int *, int *);
    void adminMenu(int);
    void customerMenu(int);

    int type;
    int id;
    int flag = 1;
    while(flag){
        if(logInMenu(&type, &id))
            flag = 0;
    }
    system("cls");

    switch(type){
        case 1:adminMenu(id);break;
        case 2:customerMenu(id);break;
        case 3:break;
    }
}

int logInMenu(int * acctype, int * ID){
    int choice;
    system("cls");
    printf("1.Log in\n2.Sing up\n3.Quit\n\nEnter your choice: ");

    fflush(stdin);
    char c = getch();
    while( !isdigit(c) || ( c != '1' && c != '2' && c != '3')){
        printf("\nUnknown choice.\n\nPress any key to continue...");
        if(getch())
            system("cls");
        fflush(stdin);
        printf("1.Log in\n2.Sing up\n3.Quit\n\nEnter your choice: ");
        c = getch();
    }
    choice = (int)(c - '0');

    if(choice == 3){
        printf("\nGoodbye!\n");
        sleep(3);
        system("cls");
        *acctype = 3;
        return 1;
    }
    system("cls");

    fflush(stdin);
    printf("%s", "Enter your ID(max 20 numbers): ");
    int i = 0;
    char socialID[21];
    c = getchar();
    while(c != '\n' && i < 20){
        if(!isdigit(c)){
            printf("An ID consists only of integer numbers, try again!\n\nPress any key to continue...");
            if(getch()){
                return 0;
            }
        }
        socialID[i] = c;
        i++;
        c = getchar();
    }
    if(i == 0){
        printf("ID can't be empty!\n\nPress any key to continue...");
        if(getch())
            return 0;
    }
    socialID[i] = '\0';

    int checkID = strtol(socialID, NULL, 10);
    if(!searchAccount(checkID)){
        printf("Invalid ID.\n\nPress any key to continue...");
        if(getch())
            system("cls");
        return 0;
    }

    if(choice == 2 && searchEAccount(checkID)){
        printf("An E-Account already exists with that ID, try logging in!\n\nPress any key to continue...");
        if(getch())
            system("cls");
        return 0;
    }

    if(choice == 1 && !searchEAccount(checkID)){
        printf("There's no E-Account with that ID!Try singing up!\n\nPress any key to continue...");
        if(getch())
            system("cls");
        return 0;
    }

    fflush(stdin);
    char password[31];
    i = 0;
    printf("%s", "Enter your password(max 30 characters): ");
    c = getchar();
    while(c != '\n' && i < 30){
        password[i] = c;
        i++;
        c = getchar();
    }
    if(i == 0){
        printf("Password can't be empty!\n\nPress any key to continue...");
        if(getch())
            return 0;
    }
    password[i] = '\0';

    unsigned hashval = tohash(password, 100, 50);
    if(choice == 2){
        if(addEAccount("User", checkID, hashval)){
            printf("Signed up successfully!\n\nPress any key to continue...");
        }else
            printf("Error signing up, try again!\n\nPress any key to continue...");
        if(getch())
            system("cls");
        return 0;
    }

    int getHashPass(int);

    int test = getHashPass(checkID);
    if(hashval == test){
        void getAccountType(int, int*);

        getAccountType(checkID, acctype);
        *ID = checkID;
        system("cls");
        printf("Logged in successfully! Press any key to continue...");
        if(getch())
            system("cls");
        return 1;
    }
    printf("Wrong password, try again!\n\nPress any key to continue...");
    getch();
    return 0;
}

void adminMenu(int socialID){

    int changeAccountName(int, char *);
    void getAccountName(int, char **);

    int addAccount(int, char *, double, int);
    int removeAccount(int, int);

    int loop = 1;
    char * name;
    getAccountName(socialID, &name);

    while(loop){
        printf("Account type: Admin\n\nWelcome %s\n\n", name);
        printf("1.Add an account\n2.Remove an account\n3.Quit\n\nEnter your choice: ");
        fflush(stdin);
        char c = getch();
        while( !isdigit(c) || ( c != '1' && c != '2' && c != '3')){
            printf("\nUnknown choice.\n\nPress any key to continue!");
            if(getch())
                system("cls");
            fflush(stdin);
            printf("Account type: Admin\n\nWelcome %s\n\n", name);
            printf("1.Add an account\n2.Remove an account\n3.Quit\n\nEnter your choice: ");
            c = getch();
        }
        int choice = (int)(c - '0');
        system("cls");
        switch(choice){
            case 1:{
                char idStr[100];
                int pos = 0;
                char c;
                int flag = 0;
                printf("%s", "Enter the account's ID: ");
                fflush(stdin);
                while(pos < 98){
                    c = getchar();
                    if(c == '\n'){
                        break;
                    }
                    if(!isdigit(c)){
                        printf("ID can only contain integers! Mission abort!\n");
                        flag = 1;
                        break;
                    }
                    idStr[pos] = c;
                    pos++;
                }
                if(flag)
                    break;
                if(pos == 0){
                    printf("ID can't be empty!\n");
                    break;
                }
                idStr[pos] = '\0';
                int id = strtol(idStr, NULL, 10);
                if(searchAccount(id)){
                    printf("An account already exists with that ID!\n");
                    break;
                }
                char name[100];
                printf("%s", "Enter the account's name(max 100 characters, only alpha characters allowed): ");
                pos = 0;
                flag = 0;
                fflush(stdin);
                while(pos < 98){
                    c = getchar();
                    if(c == '\n'){
                        break;
                    }
                    if(!isalpha(c) && !isspace(c)){
                        printf("Non alpha character spotted! Mission abort!\n");
                        flag = 1;
                        break;
                    }
                    name[pos] = c;
                    pos++;
                }
                if(flag)
                    break;
                if(pos == 0){
                    printf("Name can't be empty!\n");
                    break;
                }
                name[pos] = '\0';

                char amount[8];
                printf("%s", "Enter the balance(max 9.9 mil. $): ");
                fflush(stdin);
                pos = 0;
                flag = 0;
                while(pos < 7){
                    c = getchar();
                    if(c == '\n'){
                        break;
                    }
                    if(!isdigit(c)){
                        printf("Illegal input.\n");
                        flag = 1;
                        break;
                    }
                    amount[pos] = c;
                    pos++;
                }
                if(flag)
                    break;
                if(pos == 0){
                    printf("Balance can't be empty.\n");
                    break;
                }
                amount[pos] = '\0';
                double balance = strtod(amount, NULL);
                if(addAccount(id, name, balance, 0)){
                    printf("Added successfully!\n");
                }
            }break;
            case 2:{
                char idStr[100];
                int pos = 0;
                char c;
                int flag = 0;
                printf("%s", "Enter the account's ID: ");
                fflush(stdin);
                while(pos < 98){
                    c = getchar();
                    if(c == '\n'){
                        if(pos == 0){
                            printf("ID can't be empty!\n");
                            flag = 1;
                        }
                        break;
                    }
                    if(!isdigit(c)){
                        printf("ID can only contain integers! Mission abort!\n");
                        flag = 1;
                        break;
                    }
                    idStr[pos] = c;
                    pos++;
                }
                if(flag)
                    break;
                idStr[pos] = '\0';
                int id = strtol(idStr, NULL, 10);
                if(removeAccount(id, 1)){
                    printf("Removed successfully!\n");
                }
            }break;
            case 3:loop = 0;break;
        }
        printf("%s", "Press any key to continue...");
        if(getch()){
            system("cls");
        }
    }
}

void customerMenu(int socialID){

    int loop = 1;
    char * name;
    void getAccountName(int, char **);
    double getBalance(int);
    void changeBalance(int , double);
    getAccountName(socialID, &name);
    while(loop){
        system("cls");
        fflush(stdin);
        double balance = getBalance(socialID);
        printf("Account type: Customer\nWelcome %s\n\n", name);
        printf("Current balance: %.2lf\n\n", balance);
        printf("1.Withdraw\n2.Deposit\n3.Quit\n\nEnter your choice: ");
        char c = getch();
        while(!isdigit(c) || ( c != '1' && c != '2' && c != '3')){
            printf("\nUnknown choice, press any key to continue!");
            if(getch())
                system("cls");
            fflush(stdin);
            printf("Account type: Customer\nWelcome %s\n\n", name);
            printf("Current balance: %.2lf\n\n", balance);
            printf("1.Withdraw\n2.Deposit\n3.Quit\n\nEnter your choice: ");
            c = getch();
        }
        int choice = (int)(c - '0');
        system("cls");
        switch(choice){
            case 1:{
                char amount[8];
                if(balance > 9999999)
                    printf("Enter the amount(max 9.9 mil $): ");
                else
                    printf("Enter the amount(max %lf $): ", balance);
                fflush(stdin);
                int pos = 0;
                int flag = 0;
                while(pos < 7){
                    c = getchar();
                    if(c == '\n'){
                        break;
                    }
                    if(!isdigit(c)){
                        printf("Illegal input.\n\nPress any key to continue...");
                        flag = 1;
                        if(getch())
                            break;
                    }
                    amount[pos] = c;
                    pos++;
                }
                if(flag)
                    break;
                if(pos == 0){
                    printf("Input can't be empty!\n\nPress any key to continue...");
                    if(getch())
                        break;
                }
                amount[pos] = '\0';
                double doubAmount = strtod(amount, NULL);
                if(doubAmount > balance){
                    printf("Insufficient funds!\n");
                    break;
                }
                balance -= doubAmount;
                changeBalance(socialID, balance);
            }break;
            case 2:{
                char amount[8];
                printf("%s", "Enter the amount(max 9.9 mil. $): ");
                fflush(stdin);
                int pos = 0;
                int flag = 0;
                while(pos < 7){
                    c = getchar();
                    if(c == '\n'){
                        break;
                    }
                    if(!isdigit(c)){
                        printf("Illegal input.\n\nPress any key to continue...");
                        flag = 1;
                        if(getch())
                            break;
                    }
                    amount[pos] = c;
                    pos++;
                }
                if(flag)
                    break;
                if(pos == 0){
                    printf("Input can't be empty!\n\nPress any key to continue...");
                    if(getch())
                        break;
                }
                amount[pos] = '\0';
                double doubAmount = strtod(amount, NULL);
                balance += doubAmount;
                changeBalance(socialID, balance);
            }break;
            case 3:{
                system("cls");printf("Goodbye!\n");sleep(3);break;
            }
        }
    }
}


