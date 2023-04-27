#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 8

int bruteforce(int [][SIZE], int[], int[]);
void reset(int [][SIZE]);
void prc(int c[][SIZE]);

int main()
{
    int count = 0;
    srand(time(NULL));
    int test = -1;
    int chessboard[SIZE][SIZE] = {{0}};
    int horizontal[SIZE] = {2, 1, -1, -2, -2, -1, 1, 2};
    int vertical[SIZE] = {-1, -2, -2, -1, 1, 2, 2, 1};
    while(test != 1){
        test = bruteforce(chessboard, horizontal, vertical);
        if(test == 1)
            prc(chessboard);
        reset(chessboard);
        count++;
        printf("try: %d\n", count);
    }
    return 0;
}
int bruteforce(int cb[][SIZE], int h[], int v[]){
    int count = 1;
    int cv = 0, ch = 0,ran;
    for(int i = 0 ; i < 64; i++){
        ran = rand() % 8;
        if((cv + v[ran] >= 0 && cv + v[ran] < 8) && (ch + h[ran] >= 0 && ch + h[ran] < 8) && cb[ch+h[ran]][cv+v[ran]] == 0){
            cv += v[ran];
            ch += h[ran];
            cb[ch][cv] = 1;
            count++;
        }
    }
    if(count == 64) return 1;
    else return 0;
}

void reset(int cb[][SIZE]){
    for(int i = 0;i < SIZE; i++){
        for(int j = 0; j < SIZE; j++)
            cb[i][j] = 0;
    }
}

void prc(int c[][SIZE]){
    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            printf("%d ", c[i][j]);
        }
        puts("");
    }
    printf("============================\n");
}
