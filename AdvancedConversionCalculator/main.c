#include <stdio.h>
#include <stdlib.h>
//for string and character manipulations
#include <ctype.h>
#include <string.h>
//to get the columns, clear input and output
#include <windows.h>
//for getch() function
#include <conio.h>

//Max Unit String Size
#define UN 25
//Supporting up to 999999
#define NUM 7
//"How many  \0" size
#define PAR_1 10
//"are in \0" size
#define PAR_2 8
//Max Unit Type String Size
#define TYPE 7

//list of supported unit types
const char * const UnitTypes = "-length-mass-volume-area-time-";
//Supported Units
const char * const lengthUnits = "-meters-kilometers-decimeters-centimeters-millimeters-miles-yards-feet-inches-";
const char * const massAndVolumeUnits = "-kilograms-grams-milligrams-tons-pounds-ounces-carats-";
const char * const volumeUnits = "-cubic kilometers-cubic meters-cubic decimeters-cubic centimeters-cubic millimeters-cubic miles-cubic yards-cubic feet-cubic inches-liters-milliliters-gallons-barrels-";
const char * const areaUnits= "-square meters-square kilometers-square centimeters-square millimeters-square miles-square yards-square feet-square inches-acres-hectares-";
const char * const timeUnits = "-seconds-milliseconds-minutes-hours-days-weeks-months-years-decades-centuries-millenniums-";

//base function to start the program
void startConversion();

//function to print supported unit and unit types
void printValidUnits();
void printUnit(const char *);
//Get user's choice from the menu
int getCommand();
//function to get the question from the user
int getUnits(char [], char[], char[], int *);
//function to set the unit's type based on the entered unit
void setUnitType(char[] , char []);
//function to check if the unit entered is valid
int checkUnitType(char[], char);

void convertUnit(char[], char[], char[], int);

//function to check if the entered unit is valid and supported by the program
int checkString(char[], const char * const );
//function to catch special character errors when entering the unit
int checkStringArr(char str[], int size);

//If the quantity is 1 it makes unit two plural
void toPlural(char[]);
//converts a string to lower cases;
void toLower(char[], int);

//function to get the width of the screen for centering text
int getcolumn();
//function to print error msgs
int err();
//full = line
void line();
//function to center text with the help of getcolumn()
void centerText(char *);
//function to clear cmd
void clearoutput();




int main(){
    //Maximize cmd from the execution of the program
    ShowWindow(GetConsoleWindow(), SW_SHOWMAXIMIZED);
    //keep running until the user chooses otherwise
    int run = -1;
    while(run != 0){
        run = getCommand();
        if(run == 2)
           startConversion();
        system("cls");
        Sleep(100);
    }

    return 0;
}

void startConversion(){
    //declare the two units and their types(to be decided) that you're going to get from the users
    char unitOne[UN];
    char unitTwo[UN];
    char unitType[15];
    unitType[0] = '\0';

    int quantity = -1;
    //get units and set their type
    int run = getUnits(unitOne, unitTwo, unitType, &quantity);
    //start conversion if the units are valid
    if(run)
        convertUnit(unitType, unitOne, unitTwo, quantity);

}

int getCommand(){
    line();
    puts("");
    centerText("MENU:\n");
    puts("");
    centerText("1.Ask for conversion\n");
    centerText("2.Check the valid Units\n");
    centerText("3.About\n");
    centerText("4.Help\n");
    centerText("5.Quit\n");
    puts("");
    line();
    centerText("Press a number\n");
    char choice = getch();
    puts("");
    line();
    system("cls");
    fflush(stdin);
    line();
    switch (choice){
        case '1':return 2;
        case '2':printValidUnits();break;
        case '3':centerText("About\n");
        printf("\nThis is a program to take a specific question about conversion from the user, to proceed the question, do the right calculations, and print the answer!\n");
        printf("If you want to know how to ask a question please refer to the \"Help\" option in the menu.Be aware that the commands are taken upon the key press, pressing Enter is not required!\n\n");
        break;
        case '4':
        centerText("The questions are asked in this format:\n");
        printf("\nHow many ________(unit one) are in ___ (quantity of unit two) ________(unit two)?\n");
        printf("\nEx. How many inches are in 5 meters?\n    How many centimeters are in 1 meter?\n\n");
        printf("Note:\nCheck the available Units by pressing 2 in the menu.\nUnit one must always be in its plural form.\n");
        printf("Unit two can be in its single form if and only if the quantity of it is equal to 1.\n");
        printf("Quantity of the second unit can be from 1 to 999,999.\n");
        printf("When entering the quantity only use numbers, no special characters.\n\n");
        break;
        case '5':centerText("Goodbye!\n");line();Sleep(2000);return 0;break;
        default: centerText("Invalid input, only press 1, 2, 3, 4 or 5!\n");break;
    }
    line();
    clearoutput();
    return 1;
}

int getUnits(char unOne[],  char unTwo[], char unType[], int * quantity ){
    centerText("-----Reminder questions end with a ? mark!-----\n");
    printf("%s", "Ask your question: ");
    //to store specifically the strings "How many" and "are in"
    char part_1[PAR_1];
    char part_2[PAR_2];

    //to get the first part of the question - "How many"
    fgets(part_1, PAR_1, stdin);
    toLower(part_1, PAR_1);
    if(strcmp(part_1, "how many ") != 0) {puts("");return err(0);}

    //To read the units and the quantity
    char unit;

    //get the first unit
    int count = 0;
    while((unit = getchar()) != ' ' && count < UN - 1){
        unOne[count] = unit;
        count++;
    }
    unOne[count] = '\0';
    toLower(unOne, count);
    if(strcmp(unOne, "square") == 0 || strcmp(unOne, "cubic") == 0){
        unOne[count] = ' ';
        count++;
        while((unit = getchar()) != ' ' && count < UN - 1){
            unOne[count] = unit;
            count++;
        }
        unOne[count] = '\0';
        toLower(unOne, count);
    }
    if(checkStringArr(unOne, count)) return err(1);

    //set the first unit's type
    char unOneT[TYPE];
    unOneT[0] = '\0';
    setUnitType(unOne, unOneT);
    if(strcmp(unOneT, "NULL") == 0) return err(1);

    //to get the second part of the question - "are in"
    fgets(part_2, PAR_2, stdin);
    toLower(part_2, PAR_2);
    if(strcmp(part_2, "are in ") != 0) return err(0);

    //to get the quantity of the second unit and read it in an int variable
    //to store the quantity of unit two - tip: move it down the program
    char number[NUM];
    count = 0;
    while((unit = getchar()) != ' ' && count < NUM - 1){
        //check for a bad input
        if(!isdigit(unit)){
            //if the first and only inputed character is an 'a' replace it with a 1
            if(count == 0 && unit == 'a'){
                unit = getchar();
                if(unit == ' '){
                    number[count] = '1';
                    count++;
                    break;
                }
                return err(3);
            }
            return err(3);
        }
        number[count] = unit;
        count++;

        //check to see if it surpasses the supported amount, or if it's a bad input
        if(count == NUM - 1){
            unit = getchar();
            if(isdigit(unit))
                return err(2);
            else if(!isspace(unit))
                return err(3);
            else
                break;
        }
    }
    number[count] = '\0';
    count = 0;
    sscanf(number, "%d", quantity);

    int bounds = 1;
    if(*quantity == 1)
        bounds = 2;
    //to get the second unit
    while((unit = getchar()) != '?' && unit != '\n' && count < UN - bounds){
        unTwo[count] = unit;
        count++;
    }
    unTwo[count] = '\0';
    toLower(unTwo, count);
    if(checkStringArr(unTwo, count)) return err(4);

    if(*quantity == 1) toPlural(unTwo);

    //set the second unit's type,check if valid, if it's not the same as the first unit's, or if both of the units are the same
    char unTwoT[TYPE];
    unTwoT[0] = '\0';
    setUnitType(unTwo, unTwoT);
    if(strcmp(unTwoT, "NULL") == 0)
        return err(4);
    else if(strcmp(unOneT, unTwoT) != 0)
        return err(5);
    else if(strcmp(unOne, unTwo) == 0)
        return err(6);

    //save the units' type and return the go signal
    strcpy(unType, unOneT);
    return 1;

}

void setUnitType(char tobechecked[], char tobestored[]){
    //determines inputed unit's type, NULL if not supported
    if( checkUnitType(tobechecked, 'l') ){
        strcpy(tobestored, "length");
    } else if ( checkUnitType(tobechecked, 'm') ){
        strcpy(tobestored, "mass");
    }else if ( checkUnitType(tobechecked, 'v') ){
        strcpy(tobestored, "volume");
    }else if ( checkUnitType(tobechecked, 'a') ){
        strcpy(tobestored, "area");
    }else if ( checkUnitType(tobechecked, 't') ){
        strcpy(tobestored, "time");
    }else
        strcpy(tobestored, "NULL");
}

int checkUnitType(char tobechecked[], char type){
    //Checks if the inputed unit is supported
    int flag = 0;
    switch(type){
        case 'l':flag = checkString(tobechecked, lengthUnits);break;
        case 'm':flag = checkString(tobechecked, massAndVolumeUnits);break;
        case 'v':flag = checkString(tobechecked, volumeUnits);break;
        case 'a':flag = checkString(tobechecked, areaUnits);break;
        case 't':flag = checkString(tobechecked, timeUnits);break;
    }
    return flag;
}

void convertUnit(char type[], char unitOne[], char unitTwo[], int quantity){
    centerText("---CONVERTING---\n\n");

    float rate, result;

    if(strcmp(type, "length") == 0){
        if(strcmp(unitOne, "kilometers") == 0){
             if(strcmp(unitTwo, "meters") == 0){
                rate = 0.001;
            }else if(strcmp(unitTwo, "decimeters") == 0){
                rate  = 0.0001;
            }else if(strcmp(unitTwo, "centimeters") == 0){
                rate = 0.00001;
            }else if(strcmp(unitTwo, "millimeters") == 0){
                rate = 0.000001;
            }else if(strcmp(unitTwo, "miles") == 0){
                rate = 0.62137119;
            }else if(strcmp(unitTwo, "yards") == 0){
                rate =  0.000914;
            }else if(strcmp(unitTwo, "feet") == 0){
                rate = 0.000305;
            }else {
                rate = 0.0000254;
            }
        }else if(strcmp(unitOne, "meters") == 0){
            if(strcmp(unitTwo, "kilometers") == 0){
                rate = 1000;
            }else if(strcmp(unitTwo, "decimeters") == 0){
                rate  = 0.1;
            }else if(strcmp(unitTwo, "centimeters") == 0){
                rate = 0.01;
            }else if(strcmp(unitTwo, "millimeters") == 0){
                rate = 0.001;
            }else if(strcmp(unitTwo, "miles") == 0){
                rate = 1609.344;
            }else if(strcmp(unitTwo, "yards") == 0){
                rate = 0.9144;
            }else if(strcmp(unitTwo, "feet") == 0){
                rate = 0.3048;
            }else {
                rate = 0.0254;
            }
        } else if(strcmp(unitOne, "decimeters") == 0){
            if(strcmp(unitTwo, "kilometers") == 0){
                rate  = 10000;
            }else if(strcmp(unitTwo, "meters") == 0){
                rate = 10;
            }else if(strcmp(unitTwo, "centimeters") == 0){
                rate = 0.1;
            }else if(strcmp(unitTwo, "millimeters") == 0){
                rate = 0.01;
            }else if(strcmp(unitTwo, "miles") == 0){
                rate = 16093.44;
            }else if(strcmp(unitTwo, "yards") == 0){
                rate =  9.144;
            }else if(strcmp(unitTwo, "feet") == 0){
                rate = 3.048;
            }else {
                rate = 0.254;
            }
        } else if(strcmp(unitOne, "centimeters") == 0){
            if(strcmp(unitTwo, "kilometers") == 0){
                rate  = 100000;
            }else if(strcmp(unitTwo, "meters") == 0){
                rate = 100;
            }else if(strcmp(unitTwo, "decimeters") == 0){
                rate = 10;
            }else if(strcmp(unitTwo, "millimeters") == 0){
                rate = 0.1;
            }else if(strcmp(unitTwo, "miles") == 0){
                rate = 160934.4;
            }else if(strcmp(unitTwo, "yards") == 0){
                rate =  91.44;
            }else if(strcmp(unitTwo, "feet") == 0){
                rate = 30.48;
            }else {
                rate = 2.54;
            }
        }   else if(strcmp(unitOne, "millimeters") == 0){
            if(strcmp(unitTwo, "kilometers") == 0){
                rate  = 1000000;
            }else if(strcmp(unitTwo, "meters") == 0){
                rate = 1000;
            }else if(strcmp(unitTwo, "decimeters") == 0){
                rate = 100;
            }else if(strcmp(unitTwo, "centimeters") == 0){
                rate = 10;
            }else if(strcmp(unitTwo, "miles") == 0){
                rate = 1609344;
            }else if(strcmp(unitTwo, "yards") == 0){
                rate =  914.4;
            }else if(strcmp(unitTwo, "feet") == 0){
                rate = 304.8;
            }else {
                rate = 25.4;
            }
        } else if(strcmp(unitOne, "miles") == 0){
            if(strcmp(unitTwo, "kilometers") == 0){
                rate  = 0.621371192;
            }else if(strcmp(unitTwo, "meters") == 0){
                rate = 0.000621371192;
            }else if(strcmp(unitTwo, "decimeters") == 0){
                rate = 0.0000621371192;
            }else if(strcmp(unitTwo, "centimeters") == 0){
                rate = 0.00000621371192;
            }else if(strcmp(unitTwo, "millimeters") == 0){
                rate = 0.000000621371192;
            }else if(strcmp(unitTwo, "yards") == 0){
                rate =  0.000568181818;
            }else if(strcmp(unitTwo, "feet") == 0){
                rate = 0.000189393939;
            }else {
                rate = 0.0000157828283;
            }
        } else if(strcmp(unitOne, "yards") == 0){
            if(strcmp(unitTwo, "kilometers") == 0){
                rate  = 1093.6133;
            }else if(strcmp(unitTwo, "meters") == 0){
                rate = 1.0936133;
            }else if(strcmp(unitTwo, "decimeters") == 0){
                rate = 0.10936133;
            }else if(strcmp(unitTwo, "centimeters") == 0){
                rate = 0.010936133;
            }else if(strcmp(unitTwo, "millimeters") == 0){
                rate = 0.0010936133;
            }else if(strcmp(unitTwo, "miles") == 0){
                rate =  1760;
            }else if(strcmp(unitTwo, "feet") == 0){
                rate = 0.333333333;
            }else {
                rate = 0.0277777778;
            }
        } else if(strcmp(unitOne, "feet") == 0){
            if(strcmp(unitTwo, "kilometers") == 0){
                rate  = 3280.8399;
            }else if(strcmp(unitTwo, "meters") == 0){
                rate = 3.2808399;
            }else if(strcmp(unitTwo, "decimeters") == 0){
                rate = 0.32808399;
            }else if(strcmp(unitTwo, "centimeters") == 0){
                rate =0.032808399;
            }else if(strcmp(unitTwo, "millimeters") == 0){
                rate = 0.0032808399;
            }else if(strcmp(unitTwo, "miles") == 0){
                rate =  5280;
            }else if(strcmp(unitTwo, "yards") == 0){
                rate = 3;
            }else {
                rate = 0.0833333333;
            }
        } else {//inches
            if(strcmp(unitTwo, "kilometers") == 0){
                rate  = 39370.0787;
            }else if(strcmp(unitTwo, "meters") == 0){
                rate = 39.3700787;
            }else if(strcmp(unitTwo, "decimeters") == 0){
                rate = 3.93700787;
            }else if(strcmp(unitTwo, "centimeters") == 0){
                rate = 0.393700787;
            }else if(strcmp(unitTwo, "millimeters") == 0){
                rate = 0.0393700787;
            }else if(strcmp(unitTwo, "miles") == 0){
                rate =  63360;
            }else if(strcmp(unitTwo, "yards") == 0){
                rate = 36;
            }else {//feet
                rate = 12;
            }
            result = quantity*rate;
            printf("There are %f %s in %d %s!\n\n", result, unitOne, quantity, unitTwo);
        }
    }else if(strcmp(type, "mass") == 0){
        if(strcmp(unitOne, "kilograms") == 0){
            if(strcmp(unitTwo, "grams") == 0){
                rate = 0.001;
            }else if(strcmp(unitTwo, "milligrams") == 0){
                rate = 0.000001;
            }else if(strcmp(unitTwo, "tons") == 0){
                rate = 1000;
            }else if(strcmp(unitTwo, "pounds") == 0){
                rate = 0.45359237;
            }else if(strcmp(unitTwo, "ounces") == 0){
                rate = 0.028349523;
            }else {//carats
                rate = 0.0002;
            }
        } else if(strcmp(unitOne, "grams") == 0){
            if(strcmp(unitTwo, "kilograms") == 0){
                rate = 1000;
            }else if(strcmp(unitTwo, "milligrams") == 0){
                rate = 0.001;
            }else if(strcmp(unitTwo, "tons") == 0){
                rate = 1000000;
            }else if(strcmp(unitTwo, "pounds") == 0){
                rate = 453592;
            }else if(strcmp(unitTwo, "ounces") == 0){
                rate = 28.34952;
            }else {//carats
                rate = 0.2;
            }
        }else if(strcmp(unitOne, "milligrams") == 0){
            if(strcmp(unitTwo, "kilograms") == 0){
                rate = 1000000;
            }else if(strcmp(unitTwo, "grams") == 0){
                rate = 1000;
            }else if(strcmp(unitTwo, "tons") == 0){
                rate = 907184740;
            }else if(strcmp(unitTwo, "pounds") == 0){
                rate = 453592.37;
            }else if(strcmp(unitTwo, "ounces") == 0){
                rate = 28349.523125;
            }else {//carats
                rate = 200;
            }
        }else if(strcmp(unitOne, "tons") == 0){
            if(strcmp(unitTwo, "kilograms") == 0){
                rate = 0.001;
            }else if(strcmp(unitTwo, "grams") == 0){
                rate = 0.0000011023;
            }else if(strcmp(unitTwo, "milligrams") == 0){
                rate = 0.000000001102311310924388;
            }else if(strcmp(unitTwo, "pounds") == 0){
                rate = 0.0005;
            }else if(strcmp(unitTwo, "ounces") == 0){
                rate = 0.00003125;
            }else {//carats
                rate = 0.00000022046;
            }
        }else if(strcmp(unitOne, "pounds") == 0){
            if(strcmp(unitTwo, "kilograms") == 0){
                rate = 2.2;
            }else if(strcmp(unitTwo, "grams") == 0){
                rate = 0.0022;
            }else if(strcmp(unitTwo, "milligrams") == 0){
                rate = 0.000002204622621848776;
            }else if(strcmp(unitTwo, "tons") == 0){
                rate = 2000;
            }else if(strcmp(unitTwo, "ounces") == 0){
                rate = 0.0625;
            }else {//carats
                rate = 0.000441;
            }
        }else if(strcmp(unitOne, "ounces") == 0){
            if(strcmp(unitTwo, "kilograms") == 0){
                rate = 35.2739619;
            }else if(strcmp(unitTwo, "grams") == 0){
                rate = 0.0352739658378696;
            }else if(strcmp(unitTwo, "milligrams") == 0){
                rate = 0.000035274;
            }else if(strcmp(unitTwo, "tons") == 0){
                rate = 32000;
            }else if(strcmp(unitTwo, "pounds") == 0){
                rate = 16;
            }else {//carats
                rate = 0.007055;
            }
        }else{//carats
            if(strcmp(unitTwo, "kilograms") == 0){
                rate = 5000;
            }else if(strcmp(unitTwo, "grams") == 0){
                rate = 5;
            }else if(strcmp(unitTwo, "milligrams") == 0){
                rate = 0.005;
            }else if(strcmp(unitTwo, "tons") == 0){
                rate = 4535923.7;
            }else if(strcmp(unitTwo, "pounds") == 0){
                rate = 2267.96185;
            }else {//ounces
                rate = 141.747616;
            }
        }
        result = quantity*rate;
        printf("There are %f %s in %d %s!\n\n", result, unitOne, quantity, unitTwo);
    }else if(strcmp(type, "volume") == 0){
        centerText("UNDER CONSTRUCTION!\n");
        centerText("---CHECK BACK LATER---\n");
    }else if(strcmp(type, "area") == 0){
        centerText("UNDER CONSTRUCTION!\n");
        centerText("---CHECK BACK LATER---\n");
    }else {
        centerText("UNDER CONSTRUCTION!\n");
        centerText("---CHECK BACK LATER---\n\n");
    }

    result = quantity*rate;
    printf("There are %f %s in %d %s!\n\n", result, unitOne, quantity, unitTwo);

    line();
    clearoutput();
}

void printValidUnits(){
    const char * uCopy = &UnitTypes[2];
    const char * lCopy = &lengthUnits[1];
    const char * mCopy = &massAndVolumeUnits[1];
    const char * vCopy = &volumeUnits[1];
    const char * aCopy = &areaUnits[1];
    const char * tiCopy = &timeUnits[1];
    int sign = 1;
    puts("");puts("");
    //by using pointers to go through the strings it prints the type of units followed by the units itself
    printf("%c", toupper(uCopy[-1]));
    while(1){
        if(*uCopy == '-'){
            printf("%c%c", ':', ' ');
            switch(sign){
                case 1: printUnit(lCopy);break;
                case 2: printUnit(mCopy);break;
                case 3: printUnit(vCopy);break;
                case 4: printUnit(aCopy);break;
                case 5: printUnit(tiCopy);break;
            }
            sign++;
            uCopy++;
            puts("");puts("");
            if(*uCopy == '\0')
                break;
            printf("%c", toupper(*uCopy));
            uCopy++;
        }
        printf("%c", *uCopy);
        uCopy++;
    }
}

void printUnit(const char * unitPtr){
    //prints the units of a certain type
    int count = 0;
    int columns = getcolumn();
    while(*unitPtr != '\0'){
        count++;
        if(*unitPtr == '-'){
            if(unitPtr[1] != '\0')
                printf("%c%c", ',', ' ');
            if(count >= columns - 30){
                puts("");
                count = 0;
            }
        }
        else
            printf("%c", *unitPtr);
        unitPtr++;
    }
    printf("%c", '.');
}

int checkString(char found[], const char * const searchIn){
    //Function to determine if the unit is supported by the program, all units are stored in a string separated by '-' character,returns 1 if found, else 0.
    char * token = strstr(searchIn, found);
    while(token != NULL && (token[-1] != '-' || token[strlen(found)] != '-')){
        token++;
        token = strstr(token, found);
    }
    if (token == NULL)
        return 0;
    else
        return 1;
}

int checkStringArr(char tobechecked[], int size){
    //Checks for bad input when writing units
    int flag = 0;
    for(int i = 0; i < size;i++){
        if(!isalpha(tobechecked[i]) && !isspace(tobechecked[i])){
            flag = 1;
            break;
        }
    }
    return flag;
}

void toPlural(char str[]){
    //When the quantity of the second unit is 1, it transforms the unit to plural for an easier comparison with the first unit
    //Special cases are supported units with irregular plural form
    char * specialcase_1 = "-foot-cubic foot-square foot-";
    char * specialcase_2 = "-inch-cubic inch-square inch-";
    char * specialcase_3 = "-century-";

    if( checkString(str, specialcase_1) ){
        char * replace = strstr(str, "foot");
        replace[0] = 'f';
        replace[1] = 'e';
        replace[2] = 'e';
        replace[3] = 't';
    } else if(checkString(str, specialcase_2) ){
        char * replace = strstr(str, "inch");
        replace[4] = 'e';
        replace[5] = 's';
        replace[6] = '\0';
    } else if ( checkString(str, specialcase_3) ){
        str[6] = 'i';
        str[7] = 'e';
        str[8] = 's';
        str[9] = '\0';
    }else{
        int len = strlen(str);
        str[len] = 's';
        str[len+1] = '\0';
    }
}

void toLower(char str[], int len){
    //transforms a string to lower characters
    for(int i = 0; i < len; i++)
        str[i] = tolower(str[i]);
}

int getcolumn(){
    //returns the number of columns of the cmd
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int columns;

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;

    return columns;
}

int err(int type){
    line();
    //function to print various errors that the program might encounter from bad input from the user
    if(type == 0)
        centerText("Invalid question!Please refer to the help option to know how to ask a question!\n");
    else if(type == 1)
        centerText("Invalid first unit, check the available unit list in the menu!\n");
    else if(type == 2)
        centerText("Error! Quantity exceeds supported amount(up to 999999)\n");
    else if(type == 3)
        centerText("Error, wrong quantity input!Please only enter positive integers!\n");
    else if(type == 4)
        centerText("Invalid second unit, check the available unit list in the menu!\n");
    else if(type == 5)
        centerText("Units don't match, only enter two units from the same type!\n");
    else if(type == 6)
        centerText("Logical error! Converting from the same unit is meaningless. Please write two different units from the same type!\n");

    line();
    clearoutput();

    return 0;
}

void line(){
    //prints a line across the screen
    int columns = getcolumn();
    for(int i = 0; i < columns;i++)
        printf("%c", '=');
}

void centerText(char * txt){
    //basic function to print blank spaces till the half way of the screen
    int columns = getcolumn();
    int charcount = 0;

    char * txtcopy = txt;
    while(*txtcopy != '\0'){
        charcount++;
        txtcopy++;
    }

    int half = columns/2 - charcount/2;

    for(int i = 0; i < half;i++){
        printf("%c", ' ');
    }
    printf("%s", txt);
}

void clearoutput(){
    centerText("Press Any Key to continue!");
    if(getch()){
        //Upon key press clear the console and the input
        system("cls");
        fflush(stdin);
    }
}

