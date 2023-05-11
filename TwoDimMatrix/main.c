#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void calcSums(const int** const, int);

int main()
{
    //randomize array
    srand(time(NULL));
    //get size, array will be the size of nxn
    int n;
    printf("%s", "Enter the size: ");
    scanf("%d", &n);

    while(n <= 0){
        printf("%s", "Size can't be negative or zero! Please try again: ");
        scanf("%d", &n);
    }
    //initialize the array and print it
    int **array = malloc(sizeof(int*) * n);
    for(int i = 0; i < n; i++){
        *(array + i) = malloc(sizeof(int) * n);
        for(int j = 0; j < n; j++){
            *(*(array + i)+j) = 1+ rand() % 100;
            printf("%d\t", array[i][j]);
        }
        puts("\n\n");
    }
    puts("\n");
    //print sums
    calcSums(array, n);
    return 0;
}


void calcSums(const int** const arr, int size){
    //Calculating Triangles formed by the diagonals without including diagonal elements
    int upperTriang = 0;
    int lowerTriang = 0;
    int rightTriang = 0;
    int leftTriang = 0;
    //__
    //\ |
    // \|
    int topRightTriang = 0;
    //  /|
    // /_|
    int bottomRightTriang = 0;
    // __
    //| /
    //|/
    int topLeftTriang = 0;
    // |\
    // |_\ .
    int bottomLeftTriang = 0;

    for(int i = 0;i < size; i++){

        for(int j = 0; j < size; j++){

            if(j > i){
                topRightTriang += arr[i][j];
                if(j < size - i - 1){
                    upperTriang += arr[i][j];
                    topLeftTriang += arr[i][j];
                }else if( j > size - i - 1){
                    rightTriang += arr[i][j];
                    bottomRightTriang += arr[i][j];
                }
            }else if( i > j){
                bottomLeftTriang += arr[i][j];
                if(i < size - j - 1){
                    leftTriang += arr[i][j];
                    topLeftTriang += arr[i][j];
                }else if( i > size -j - 1){
                    lowerTriang += arr[i][j];
                    bottomRightTriang += arr[i][j];
                }
            }else{// i == j
                if( i > (size-1)/2){
                    bottomRightTriang+= arr[i][j];
                }else if(i < (size-1)/2 ){
                    topLeftTriang+= arr[i][j];
                }
            }

        }
    }

    if(size%2 == 0){
        topLeftTriang+= arr[(size-1)/2][(size-1)/2];
        printf("%d ", arr[(size-1)/2][(size-1)/2]);
    }
    puts("");

    int timer = upperTriang + lowerTriang;
    int reverseTimer = rightTriang + leftTriang;


    printf("%s\t%d\n", "Upper Triangle: ", upperTriang);
    printf("%s\t%d\n", "Lower Triangle: ", lowerTriang);
    printf("%s\t%d\n", "Right Triangle: ", rightTriang);
    printf("%s\t%d\n", "Left Triangle: ", leftTriang);

    printf("%s\t%d\n", "Top Right Triangle: ", topRightTriang);
    printf("%s\t%d\n", "Bottom Right Triangle: ", bottomRightTriang);
    printf("%s\t%d\n", "Top Left Triangle: ", topLeftTriang);
    printf("%s\t%d\n", "Bottom Left Triangle: ", bottomLeftTriang);

    printf("%s\t%d\n", "Timer Triangles: ", timer);
    printf("%s\t%d\n", "Reverse Timer Triangles: ", reverseTimer);
}
