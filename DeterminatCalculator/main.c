#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int determinantMain(int **, int);
int determinantCalc(int **, int, int, int);

int main()
{
    //to produce random numbers based on seed
    srand(time(NULL));
    //get the size of matrix
    int size;
    printf("%s", "Enter the size of the matrix: ");
    scanf("%d", &size);
    //not allowing size to be <= 0
    while(size <= 0){
        printf("Size can't be 0 or negative! Try again: ");
        scanf("%d", &size);
    }
    //using ** to pass the array without knowing the size of it at compile time
    int ** matrix = malloc(sizeof(int*)*size);
    for(int i = 0; i < size; i++){
        matrix[i] = malloc(sizeof(int)*size);
        for(int j = 0; j < size; j++){
            //producing a random NxN array and printing it
            matrix[i][j] = rand() % 10;
            printf("%d\t", matrix[i][j]);
        }
        puts("");
    }
    puts("");
    //print the result of the calculation
    printf("Det: %d\n", determinantMain(matrix, size));

    //Freeing the allocated memory with malloc
    for(int i = 0; i < size; i++)
        free(matrix[i]);
    free(matrix);

    /*Test code*/{
    /*
    int size = 3;
    int ** matrix = malloc(sizeof(int*)*size);
    for(int i = 0; i < size; i++)
            matrix[i] = malloc(sizeof(int)*size);
    for(int test = 1; test <= 100; test++){
        for(int i = 0; i < size; i++){
            for(int j = 0; j < size; j++){
                matrix[i][j] = rand() % 10;
                //matrix[i][j] = 0;
            }
        }
        printf("Det: %d\n", determinantMain(matrix, size));
    }
    */
    }

    return 0;
}
//Main function to calculate the determinant. It firstly calculates which row/col has the most 0s on it then it calls another function for help.
//It takes the matrix as parameter and the size of it
int determinantMain(int ** matrix, int size){
    //Formula to calculate a 2x2 matrix's determinant
    if(size == 2){
        return matrix[0][0]*matrix[1][1] - matrix[0][1]*matrix[1][0];
    }
    //trying to find the row/col with the most 0s on it
    int zerosCount[2][size];
    for(int i = 0; i < size; i++){
        zerosCount[0][i] = 0;
        zerosCount[1][i] = 0;
    }
    //keeping the indexes of the row and the col with most 0s
    int mostZeros_i = 0;
    int mostZeros_j = 0;
    //alternative comparison
    //int mostZeros_iCount = 0;
    //int mostZeros_jCount = 0;

    //looping through the matrix to find the 0s
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            if(matrix[i][j] == 0){
                //found a zero at ith row and jth column
                zerosCount[0][i]++;
                zerosCount[1][j]++;
                //if(zerosCount[0][i] > mostZeros_iCount){ - alternative if the speed between > and >= differs
                if(zerosCount[0][i] >= zerosCount[0][mostZeros_i]){
                    //if a row's elements are all 0 then determinant is equal to 0
                    if(zerosCount[0][i] == size)
                        return 0;
                    mostZeros_i = i;
                    //mostZeros_iCount = zerosCount[0][i];
                }
                //if(zerosCount[0][i] > mostZeros_jCount){ - alternative if the speed between > and >= differs
                if(zerosCount[1][j] >= zerosCount[1][mostZeros_j]){
                    //if a columns's elements are all 0 then determinant is equal to 0
                    if(zerosCount[1][j] == size)
                        return 0;
                    mostZeros_j = j;
                    //mostZeros_jCount = zerosCount[0][j];
                }
            }
        }
    }
    //calculating the determinant using the row/col with the most 0s on it
    if(zerosCount[0][mostZeros_i] > zerosCount[1][mostZeros_j])
        return determinantCalc(matrix, size, 0, mostZeros_i);
    //else
    return determinantCalc(matrix, size, 1, mostZeros_j);
}
//DetMain function's helper, it takes the matrix, 0-1 for type which decides if it's going to calculate using a row(0) or col(0), the index of that row/col, and the s
int determinantCalc(int ** matrix, int size, int type, int index){
    int det = 0;
    //declaring the minor as ** to pass it without knowing the size of it at compile time
    int **minor = malloc(sizeof(int*)*(size-1));
    int minorRow;
    int minorCol;

    int cofactor;
    //loop to create every cofactor and minor a row/col
    for(int k = 0; k < size; k++){
        //seeing if the cofactor we use is equal to 0, if so there's no need to calculate further
        switch(type){
            case 0: cofactor = matrix[index][k];break;
            case 1: cofactor = matrix[k][index];break;
            default:
                printf("ERROR!\n");return 0;
        }
        //cofactor == 0, skip the calculating since the determinant of this specific minor is going to be 0
        if(!cofactor){
            //printf("Cofactor 0! Skipped!\n");
            continue;
        }
        //creating the minor of the matrix
        minorRow =0;
        for(int i = 0; i < size; i++){

            if(i == index) continue;

            minor[minorRow] = malloc(sizeof(int)*(size-1));
            minorCol = 0;

            for(int j = 0; j < size; j++){

                if(j == k) continue;

                minor[minorRow][minorCol] = matrix[i][j];
                printf("%d\t", minor[minorRow][minorCol]);

                minorCol++;
            }
            minorRow++;
            puts("");
        }
        //adding the result from each cofactor*minor to the main determinant
        det += cofactor*(int)pow(-1, index+k)*determinantMain(minor, size-1);
        puts("");
    }
    //free the malloc, if all cofactors are 0 the second malloc won't happen
    if(minor[1] != NULL){
        for(int i = 0; i < minorRow; i++){
            free(minor[i]);
        }
    }
    //freeing the main malloc
    free(minor);

    return det;
}
