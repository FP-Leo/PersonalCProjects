#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 8

int checkboard(int [][SIZE]);

void clearcb(int [][SIZE]);

int placequeen(int [][SIZE]);
void setrow(int [][SIZE], int);
void setcolumn(int [][SIZE], int);
void setdiag(int [][SIZE], int, int);

void setrighup(int cb[][SIZE], int r, int c);
void setrighdown(int cb[][SIZE], int r, int c);
void setleftup(int cb[][SIZE], int r, int c);
void setleftdown(int cb[][SIZE], int r, int c);

void prc(int c[][SIZE]);
void reset(int [][SIZE]);

int main()
{
    srand(time(NULL));
    int chessboard[SIZE][SIZE] = {{0}};
    int count = 0;
    while( count < 12){
        count += placequeen(chessboard);
        reset(chessboard);
    }
    return 0;
}


int placequeen(int cb[][SIZE]){
    int row;
    int col;
    int i = 1;
    while( i < 9){
        if(checkboard(cb))
            return 0;
        row = rand() % 8;
        col = rand() % 8;
        if(cb[row][col] == 0){
            setrow(cb, row);
            setcolumn(cb, col);
            setdiag(cb, row, col);
            cb[row][col] = 2;
            i++;
        }
    }
    clearcb(cb);
    prc(cb);
    return 1;
}

void clearcb(int cb[][SIZE]){
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            if(cb[i][j] == 1)
                cb[i][j] = 0;
        }
    }
}

int checkboard(int cb[][SIZE]){
    int count = 0;
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            if(cb[i][j] == 0)
                count++;
        }
    }
    if(count == 0)
        return 1;
    else
        return 0;
}

void setrow(int cb[][SIZE], int row){
    for(int i = 0; i < SIZE;i++)
        cb[row][i] = 1;
}

void setcolumn(int cb[][SIZE], int column){
    for(int i = 0; i < SIZE;i++)
        cb[i][column] = 1;
}

void setdiag(int cb[][SIZE], int row, int column){
    setrighup(cb, row, column);
    setrighdown(cb, row, column);
    setleftup(cb, row, column);
    setleftdown(cb, row, column);
}

void setrighup(int cb[][SIZE], int r, int c){
    while(1){
        r -= 1;
        c += 1;
        if(!((r < SIZE && r >= 0) && (c < SIZE && c >= 0)))
            break;
        cb[r][c] = 1;
    }
}

void setleftup(int cb[][SIZE], int r, int c){
    while(1){
        r -= 1;
        c -= 1;
        if(!((r < SIZE && r >= 0) && (c < SIZE && c >= 0)))
            break;
        cb[r][c] = 1;
    }
}

void setrighdown(int cb[][SIZE], int r, int c){
    while(1){
        r += 1;
        c += 1;
        if(!((r < SIZE && r >= 0) && (c < SIZE && c >= 0)))
            break;
        cb[r][c] = 1;
    }
}

void setleftdown(int cb[][SIZE], int r, int c){
    while(1){
        r += 1;
        c -= 1;
        if(!((r < SIZE && r >= 0) && (c < SIZE && c >= 0)))
            break;
        cb[r][c] = 1;
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

void reset(int cb[][SIZE]){
    for(int i = 0;i < SIZE; i++){
        for(int j = 0; j < SIZE; j++)
            cb[i][j] = 0;
    }
}
