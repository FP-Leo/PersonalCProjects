#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//IO operations:
#define READ 10
#define READSTRING 11
#define WRITE 12
#define WRITELINE 13
#define WRITESTRING 14
//Load/Store operations:
#define LOAD 20
#define STORE 21
//Arithmetic operations:
#define ADD 30
#define SUBTRACT 31
#define DIVIDE 32
#define MULTIPLY 33
#define REM 34
#define EXP 35
//Transfer-of-control operations:
#define BRANCH 40
#define BRANCHNEG 41
#define BRANCHZERO 42
//To tell if the program has completed its task:
#define HALT 43

void prMenu();

void load(float mem[]);
void execute(float mem[], float * acc, int * iC, int * iR, int * oC, int * o, int * flag);
void dump(const float mem[], const float acc, const int iC, const int iR, const int oC, const int o);

void checkError(int type, int * flag, const float * const acc, const float * const opr);
int getinstruction(int);
int toint(char);
int todecimal(int, int);
void tochar(int);

int main(){

    int instructionCounter = 0, instructionRegister = 0, operationCode = 0, operand = 0, flag = 0;
    float accumulator = 0;
    float memory[1000] = {0};

    prMenu();
    load(memory);
    execute(memory, &accumulator, &instructionCounter, &instructionRegister, &operationCode, &operand, &flag);
    dump(memory, accumulator, instructionCounter, instructionRegister, operationCode, operand);

    if(flag == 1)
        printf("\n*** Program completed ***\n");
    else if (flag == 2)
        printf("\n*** Simpletron execution abnormally terminated ***\n");

    return 0;
}

void prMenu(){
    printf("*** Welcome to Simpletron! ***\n*** Please enter your program one instruction ***\n*** (or data word) at a time. I will type the ***\n*** location number and a question mark (?). ***\n*** You then type the word for that location. ***\n*** Type the sentinel -99999 to stop entering ***\n*** your program. ***\n\n");
}

void load(float mem[]){
    int tobestored, opnTest;
    for(int i = 0; i < 100;){
        tobestored = getinstruction(i);
        printf("Decimal equivalence: %d\n", tobestored);
        if(tobestored == -99999)
            break;
        else if(tobestored == -1){
            opnTest = -1;
        }else
            opnTest = tobestored/100;
        if(opnTest < 0 || (opnTest > 0 && opnTest < 10) || (opnTest > 14 && opnTest < 20) || (opnTest > 21 && opnTest < 30) || ( opnTest > 35 && opnTest < 40) || opnTest > 43 ){
            printf("*** Fatal error, invalid operand ***\n");
        }else {
            mem[i] = tobestored;
            i++;
        }
    }
    puts("");
    puts("*** Program loading completed ***");
    puts("*** Program execution begins  ***");
    puts("");
}

void execute(float mem[], float * acc, int * iC, int * iR, int * oC, int * o, int * flag){
    while(1){
        if(*flag != 0)
            break;

        *iR = mem[*iC];
        *oC = (*iR)/100;
        *o = (*iR)%100;

        switch(*oC){
            case READ:printf("%02d%s", *o, " ? ");scanf("%f", &mem[*o]);*iC += 1;
                      break;
            case READSTRING:
                      {
                          printf("%02d%s", *o, " ? ");
                          int tobeplaced, strlen, location;
                          scanf("%d", &tobeplaced);
                          strlen = tobeplaced/100;
                          mem[*o] = tobeplaced;

                          location = *o+1;

                          for(int i = 1; i < strlen;i++){
                              printf("%02d%s", location, " ? ");
                              scanf("%d", &tobeplaced);
                              mem[location] = tobeplaced;
                              location++;
                          }
                      *iC += 1;
                      }
                      break;

            case WRITE:printf("\nREZ = %f\n\n", mem[*o]);*iC += 1;break;
            case WRITELINE:puts("");*iC += 1;break;
            case WRITESTRING:
                      {
                          puts("");
                          int concopy = mem[*o];
                          int adrcopy = *o;
                          int start = concopy%100;
                          int len = concopy/100;
                          for(int i = 0; i < len; i++){
                              tochar(start);
                              adrcopy++;
                              concopy = mem[adrcopy];
                              start = concopy;
                          }
                          puts("");puts("");
                      *iC+=1;
                      }
                      break;

            case LOAD:*acc = mem[*o];*iC += 1;
                      break;
            case STORE:mem[*o] = *acc;*acc = 0;*iC += 1;
                      break;

            case ADD:
                      *acc += mem[*o];
                      checkError(1, flag, acc, &mem[*o]);
                      *iC += 1;
                      break;
            case SUBTRACT:
                      *acc -= mem[*o];
                      checkError(1, flag, acc, &mem[*o]);
                      *iC += 1;
                      break;
            case DIVIDE:
                      checkError(0, flag, acc, &mem[*o]);
                      if( *flag != 2){
                          *acc /= mem[*o];
                          checkError(1, flag, acc, &mem[*o]);
                      }
                      *iC += 1;
                      break;
            case MULTIPLY:
                      *acc *= mem[*o];
                      checkError(1, flag, acc, &mem[*o]);
                      *iC += 1;
                      break;
            case REM:
                      *acc = (int)*acc%(int)mem[*o];
                      *iC += 1;
                      break;
            case EXP:
                      {
                      int copy = *acc;
                      for(int i = 1; i < mem[*o]; i++)
                          *acc *= copy;
                      checkError(1, flag, acc, &mem[*o]);
                      *iC += 1;
                      }
                      break;
            case BRANCH:*iC = *o;
                      break;
            case BRANCHNEG:if(*acc < 0)*iC = *o;else *iC += 1;
                      break;
            case BRANCHZERO:if(*acc == 0)*iC = *o;else *iC += 1;
                      break;

            case HALT:*flag = 1;
                      break;
        }

    }
}

void dump(const float mem[], const float acc, const int iC, const int iR, const int oC, const int o){
    printf("REGISTERS:\n%-25s%+05.1f\n%-28s%02d\n%-25s%+05d\n%-28s%02d\n%-28s%02d\n\n", "accumulator", acc, "instructionCounter", iC, "instructionRegister", iR, "operationCode", oC, "operand", o);
    puts("MEMORY:");
    printf("%s", "   ");
    for(int i = 0; i < 10;i++)
        printf(" %4d ", i);
    puts("");
    for(int i = 0; i < 10;i++){
        printf("%2d", i*10);
        for(int j = 0+(i*10); j < 10*(i+1); j++)
            printf(" %+05d", (int)mem[j]);
        puts("");
    }
}

void checkError(int type, int * flag, const float * const acc, const float * const opr){
    switch(type){
        case 0: if(*opr == 0){
                    printf("\n*** Attempt to divide by zero ***\n\n");
                    *flag = 2;
                }break;
        case 1: if(*acc > 9999 || *acc < -9999){
                    printf("\n*** Accumulator OVERFLOW ***\n\n");
                    *flag = 2;
                }
                break;
    }
}

int getinstruction(int i){
    char arr[100];

    printf("%02d ? ", i);
    scanf("%99s", arr);

    if(arr[0] != '+' && arr[0] != '-')
        return -1;
    if (arr[0] == '-' && arr[1] == '1' && arr[2] == '8' && arr[3] == '6' && arr[4] == '9' && arr[5] == 'F')
        return -99999;

    char * ptr = &arr[1];
    int count = 0, pos = 0,total = 0, num;

    for(; *ptr != '\0'; ptr++)
        count++;
    for(; count > 0; count--){
        num = toint(arr[count]);
        if(num == -1)
            return num;
        total += todecimal(num, pos);
        pos++;
    }

    if(arr[0] == '-')
        return -total;

    return total;
}

int toint(char x){
    int y;

    switch(x){
        case '0': y = 0 ;break;
        case '1': y = 1 ;break;
        case '2': y = 2 ;break;
        case '3': y = 3 ;break;
        case '4': y = 4 ;break;
        case '5': y = 5 ;break;
        case '6': y = 6 ;break;
        case '7': y = 7 ;break;
        case '8': y = 8 ;break;
        case '9': y = 9 ;break;
        case 'A': y = 10;break;
        case 'B': y = 11;break;
        case 'C': y = 12;break;
        case 'D': y = 13;break;
        case 'E': y = 14;break;
        case 'F': y = 15;break;
        default:  y = -1;break;
    }

    return y;
}

int todecimal(int num, int position){
    int total, first = 0, second = 0, third = 0, fourth = 0, fm = pow(2, 3+(position*4)), sm = pow(2, 2+(position*4)), tm = pow(2, 1+(position*4)), lm = pow(2, 0+(position*4));;
    if(num >= 8){
        first = 1;
        num -= 8;
    }
    if(num >= 4){
        second = 1;
        num -= 4;
    }
    if(num >= 2){
        third = 1;
        num -= 2;
    }
    if(num == 1)
        fourth = 1;

    total = first*fm + second*sm + third*tm + fourth*lm;

    return total;
}

void tochar(int tochange){
    switch(tochange){
    case 32: printf("%c", ' ');break;
    case 33: printf("%c", '!');break;
    case 34: printf("%c", '\"');break;
    case 35: printf("%c", '#');break;
    case 36: printf("%c", '$');break;
    case 37: printf("%c", '%');break;
    case 38: printf("%c", '&');break;
    case 39: printf("%c", '\'');break;
    case 40: printf("%c", '(');break;
    case 41: printf("%c", ')');break;
    case 42: printf("%c", '*');break;
    case 43: printf("%c", '+');break;
    case 44: printf("%c", ',');break;
    case 45: printf("%c", '-');break;
    case 46: printf("%c", '.');break;
    case 47: printf("%c", '/');break;
    case 48: printf("%c", '0');break;
    case 49: printf("%c", '1');break;
    case 50: printf("%c", '2');break;
    case 51: printf("%c", '3');break;
    case 52: printf("%c", '4');break;
    case 53: printf("%c", '5');break;
    case 54: printf("%c", '6');break;
    case 55: printf("%c", '7');break;
    case 56: printf("%c", '8');break;
    case 57: printf("%c", '9');break;
    case 58: printf("%c", ':');break;
    case 59: printf("%c", ';');break;
    case 60: printf("%c", '<');break;
    case 61: printf("%c", '=');break;
    case 62: printf("%c", '>');break;
    case 63: printf("%c", '?');break;
    case 64: printf("%c", '@');break;
    case 65: printf("%c", 'A');break;
    case 66: printf("%c", 'B');break;
    case 67: printf("%c", 'C');break;
    case 68: printf("%c", 'D');break;
    case 69: printf("%c", 'E');break;
    case 70: printf("%c", 'F');break;
    case 71: printf("%c", 'G');break;
    case 72: printf("%c", 'H');break;
    case 73: printf("%c", 'I');break;
    case 74: printf("%c", 'J');break;
    case 75: printf("%c", 'K');break;
    case 76: printf("%c", 'L');break;
    case 77: printf("%c", 'M');break;
    case 78: printf("%c", 'N');break;
    case 79: printf("%c", 'O');break;
    case 80: printf("%c", 'P');break;
    case 81: printf("%c", 'Q');break;
    case 82: printf("%c", 'R');break;
    case 83: printf("%c", 'S');break;
    case 84: printf("%c", 'T');break;
    case 85: printf("%c", 'U');break;
    case 86: printf("%c", 'V');break;
    case 87: printf("%c", 'W');break;
    case 88: printf("%c", 'X');break;
    case 89: printf("%c", 'Y');break;
    case 90: printf("%c", 'Z');break;
    case 91: printf("%c", '[');break;
    case 92: printf("%c", '\\');break;
    case 93: printf("%c", ']');break;
    case 94: printf("%c", '^');break;
    case 95: printf("%c", '_');break;
    case 96: printf("%c", '`');break;
    case 97: printf("%c", 'a');break;
    case 98: printf("%c", 'b');break;
    case 99: printf("%c", 'c');break;
    case 100:printf("%c", 'd');break;
    case 101:printf("%c", 'e');break;
    case 102:printf("%c", 'f');break;
    case 103:printf("%c", 'g');break;
    case 104:printf("%c", 'h');break;
    case 105:printf("%c", 'i');break;
    case 106:printf("%c", 'j');break;
    case 107:printf("%c", 'k');break;
    case 108:printf("%c", 'l');break;
    case 109:printf("%c", 'm');break;
    case 110:printf("%c", 'n');break;
    case 111:printf("%c", 'o');break;
    case 112:printf("%c", 'p');break;
    case 113:printf("%c", 'q');break;
    case 114:printf("%c", 'r');break;
    case 115:printf("%c", 's');break;
    case 116:printf("%c", 't');break;
    case 117:printf("%c", 'u');break;
    case 118:printf("%c", 'v');break;
    case 119:printf("%c", 'w');break;
    case 120:printf("%c", 'x');break;
    case 121:printf("%c", 'y');break;
    case 122:printf("%c", 'z');break;
    case 123:printf("%c", '{');break;
    case 124:printf("%c", '|');break;
    case 125:printf("%c", '}');break;
    case 126:printf("%c", '~');break;
    default: printf("%s", "(Unknown character)");
    }
}
