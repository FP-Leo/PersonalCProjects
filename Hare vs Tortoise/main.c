#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

int rannum();

int main()
{
    int hare = 1;
    int tor = 1;
    srand(time(NULL));
    printf("BANG\nAnd they're OFF!!\n");
    while(hare <= 70 && tor <= 70){
        int zar = rannum();
        switch(zar){
            case 10:
            case 9:
            case 8:
                tor += 1;break;
            case 7:
            case 6:
                if(tor -= 6 < 0)
                    tor = 1;
                else
                    tor -= 6;
                break;
            case 5:
            case 4:
            case 3:
            case 2:
            case 1:
                tor += 3;
        }
        switch(zar){
            case 10:
            case 9:
                if(hare -= 2 < 0)
                    hare = 1;
                else
                    hare -= 2;
                break;
            case 8:
            case 7:
            case 6:
                hare += 1;
                break;
            case 5:
                if(hare -= 12 < 0)
                    hare = 1;
                else
                    hare -= 12;
                break;
            case 4:
            case 3: hare += 9;break;
            case 2:
            case 1:
                break;
        }
        for(int i = 1; i < 70;i++){
            if(i == hare)
                printf("H");
            else
                printf(" ");
        }
        puts("");
        for(int i = 1; i < 70;i++){
            if(i == tor)
                printf("T");
            else
                printf(" ");
        }
        puts("");
        if(hare == tor){
            printf("Ouchhh\n");
        }
        if(hare > 70 && tor < 70)
            printf("Yuuuck Hare won :(\n");
        else if(hare < 70 && tor > 70)
            printf("Yaaaaaay Tor won!\n");
        else if(hare > 70 && tor > 70)
            printf("It's a tie");
        Sleep(100);
        system("cls");
    }
    return 0;
}

int rannum(){
    return 1+rand()%10;
}
