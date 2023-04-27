#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define INPUT 10

int main()
{
    char date[100];
    fgets(date, 99, stdin);
    date[strlen(date)-1] = '\0';

    for(int i = 0; i < strlen(date); i++)
        if(!isdigit(date[i]) && date[i] != '-')
            date[i] = ' ';

    int month, day, year;
    sscanf(date, "%d%d%d", &month, &day, &year);



    char *conMonth;
    switch(month){
        case 1: conMonth = "January";break;
        case 2: conMonth = "February";break;
        case 3: conMonth = "March";break;
        case 4: conMonth = "April";break;
        case 5: conMonth = "May";break;
        case 6: conMonth = "June";break;
        case 7: conMonth = "July";break;
        case 8: conMonth = "August";break;
        case 9: conMonth = "September";break;
        case 10:conMonth = "October";break;
        case 11:conMonth = "November";break;
        case 12:conMonth = "December";break;
        default:printf("Error, no such month");return 0;
    }

    if(day < 0 || day > 31){
        printf("Error, months have between 1 and 31 days!\n");
        return 0;
    }
    else if(day  ==  31 && (month == 4 || month == 6 || month == 9 || month == 11)){
        printf("Error, %s has only 30 days!\n", conMonth);
        return 0;
    }
    else if(month == 2 && day == 29 && year % 4 == 0 && year % 100 == 0 && year % 400 != 0 ){
        printf("Error, Leap Year skipped!\n");
        return 0;
    }else if(month == 2 && day == 29 && year % 4 != 0){
        printf("Error, not a Leap Year!\n");
        return 0;
    }else if(month == 2 && day > 29){
        printf("Error, %s has only 28 days!\n", conMonth);
        return 0;
    }
    else if(year < 0){
        printf("Error no such year!\n");
        return 0;
    }

    char result[strlen(conMonth)+INPUT];
    sprintf(result, "%s %02d, %04d", conMonth, day, year);

    printf("Converted date: %s\n", result);

    return 0;
}
