#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>

float getamount();`
void setCheck(char[], float);
void printCheck(char []);
void toString(char, int, char);

int main()
{
    float amount = getamount();

    char check[10];
    setCheck(check, amount);
    printCheck(check);

    printf("\n---------\n");
    printf("%s\n", check);
    printf("---------\n");
    printf("123456789\n");


    return 0;
}

float getamount(){
    char arr[10];
    printf("%s", "Enter the amount(use float numbers): ");
    fgets(arr, 10, stdin);
    arr[strlen(arr)-1] = '\0';
    float amount;

    while(1){
        sscanf(arr, "%f", &amount);
        int count = 0;
        for(int i = 0; i < strlen(arr); i++){
            if(!isdigit(arr[i]))
                 count++;
        }
        if(count > 1)
            printf("Error, read to many non digits characters. Please only use 1 comma to separate floats ex: 154.99, 1023.32, 34210.10\n");
        else if(amount > 100000)
            printf("Error, amount exceeded!\n");
        else if (amount <= 0)
            printf("Error, amount is less than 0!\n");
        else
            break;
        fflush(stdin);
        printf("%s", "Enter the amount(use float numbers): ");
        fgets(arr, 10, stdin);
        arr[strlen(arr)-1] = '\0';
    }

    return amount;
}

void printCheck(char currentamount[]){
    puts("");
    if(isdigit(currentamount[0]))
        toString(currentamount[0], 5, currentamount[1]);
    else if(isdigit(currentamount[1]))
        toString(currentamount[1], 4, ' ');
    if(isdigit(currentamount[3]))
        toString(currentamount[3], 3, ' ');
    if(isdigit(currentamount[4]))
        toString(currentamount[4], 2, currentamount[5]);
    else if(isdigit(currentamount[5])){
        toString(currentamount[5], 1, ' ');
        printf("%c", ' ');
    }

    if(currentamount[7] != '0'){
        if(currentamount[8] == '0')
            printf("and %c/%d\n", currentamount[7], 10);
        else
            printf("and %c%c/%d\n", currentamount[7], currentamount[8], 100);
    }
    else{
        if(currentamount[8] != '0')
            printf("and %c/%d\n", currentamount[8], 100);
        else
            puts("");
    }
}

void toString(char toStr, int indicator, char second){
    if(indicator == 1 || indicator == 3 || indicator == 4){
        switch(toStr){
            case '0': break;
            case '1': printf("ONE");break;
            case '2': printf("TWO");break;
            case '3': printf("THREE");break;
            case '4': printf("FOUR");break;
            case '5': printf("FIVE");break;
            case '6': printf("SIX");break;
            case '7': printf("SEVEN");break;
            case '8': printf("EIGHT");break;
            case '9': printf("NINE");break;
            default: printf("ERROR");break;
        }
        if(indicator == 3)
            printf("%s", " HUNDRED ");
        else if(indicator == 4)
            printf("%s", " THOUSAND ");
    } else if ( indicator == 2 || indicator == 5){
        switch(toStr){
            case '1': switch(second){
                        case '0': printf("%s", "TEN ");break;
                        case '1': printf("%s", "ELEVEN ");break;
                        case '2': printf("%s", "TWELVE ");break;
                        case '3': printf("%s", "THIRTEEN ");break;
                        case '5': printf("%s", "FIFTEEN ");break;
                        case '4':
                        case '6':
                        case '7':
                        case '8':
                        case '9': toString(second, 1, ' ');printf("%s", "TEEN ");break;
                        default: printf("ERROR\n");break;
                    }
                    break;
            case '2': printf("%s", "TWENTY ");break;
            case '3': printf("%s", "THIRTY ");break;
            case '4': printf("%s", "FOURTY ");break;
            case '5': printf("%s", "FIFTY ");break;
            case '6': printf("%s", "SIXTY ");break;
            case '7': printf("%s", "SEVENTY ");break;
            case '8': printf("%s", "EIGHTY ");break;
            case '9': printf("%s", "NINETY ");break;
            default: printf("ERROR\n");break;
        }
        if(toStr != '1'){
            toString(second, 1, ' ');
            printf("%c", ' ');
        }
        if(indicator == 5)
            printf("%s", "THOUSAND ");
    }
}

void setCheck(char tochar[], float amount){
    sprintf(tochar, "%.2f", amount);
    int test = strlen(tochar);
    if(amount >= 10000){
        memmove(&tochar[3], &tochar[2], test-2);
        tochar[2] = ',';
        test++;
    }else if (amount >= 1000){
        memmove(&tochar[2], &tochar[1], test-1);
        tochar[1] = ',';
        test++;
    }
    if(test != 9){
        (char*)memmove(&tochar[9-test], tochar, test);
        for(int i = 0; i < 9-test;i++){
            tochar[i] = '*';
        }
    }
    tochar[9] = '\0';
}

