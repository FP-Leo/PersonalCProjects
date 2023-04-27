#include <stdio.h>
#include <stdlib.h>

#define CB 8
#define START 0

int knightstour = 0;

void move(int c[][CB], int cr, int cc, int hm[], int vm[], int acc[][CB]);
void reset(int c[][CB]);
void prc(int c[][CB]);

int main()
{
    int chessboard[CB][CB] = {{0}};
    int acc[CB][CB] = {
    {2, 3, 4, 4, 4, 4, 3, 2},
    {3, 4, 6, 6, 6, 6, 4, 3},
    {4, 6, 8, 8, 8, 8, 6, 4},
    {4, 6, 8, 8, 8, 8, 6, 4},
    {4, 6, 8, 8, 8, 8, 6, 4},
    {4, 6, 8, 8, 8, 8, 6, 4},
    {3, 4, 6, 6, 6, 6, 4, 3},
    {2, 3, 4, 4, 4, 4, 3, 2}
    };
    int horizontal[CB] = {2, 1, -1, -2, -2, -1, 1, 2};
    int vertical[CB] = {-1, -2, -2, -1, 1, 2, 2, 1};
    int currentrow = 0, currentcolumn = 0;
    for(int i = 0; i < CB; i++){
        for(int j = 0; j < CB; j++){
            currentrow = i;
            currentcolumn = j;
            chessboard[currentrow][currentcolumn] = 1;
            move(chessboard, currentrow, currentcolumn, horizontal, vertical, acc);
            reset(chessboard);
            printf("i: %d, j: %d\n", i, j);
        }
    }
    printf("It has a total of %d solutions!\n", knightstour);
    return 0;
}

void move(int c[][CB], int cr, int cc, int hm[], int vm[], int acc[][CB]){
    int optionalmove = 0;
    int counter = 1;
    for(int i = 0; i < 64;i++){
        int flag = 1;
        int smallest = 9;
        for(int j = 0; j < 8; j++){
            if((cr + hm[j] < CB && cr + hm[j] >= START) && (cc + vm[j] < CB && cc + vm[j] >= START) && c[cr + hm[j]][cc + vm[j]] == 0 && acc[cr + hm[j]][cc + vm[j]] < smallest){
                smallest = acc[cr + hm[j]][cc + vm[j]];
                optionalmove = j;
                flag = 0;
            }
        }
        if(flag == 0){
            cr += hm[optionalmove];
            cc += vm[optionalmove];
            c[cr][cc] = 1;
            counter++;
        }
    }
    if(counter == 64)
        knightstour++;
    prc(c);
    printf("Counter:%d\n============================\n", counter);
}

void reset(int c[][CB]){
    for(int i = 0; i < CB; i++)
        for(int j = 0; j < CB; j++)
            c[i][j] = 0;
}

void prc(int c[][CB]){
    for(int i = 0; i < CB; i++){
        for(int j = 0; j < CB; j++){
            printf("%d ", c[i][j]);
        }
        puts("");
    }
    printf("============================\n");
}
