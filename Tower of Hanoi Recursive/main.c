#include <stdio.h>
#include <stdlib.h>

void toh_r(int, int ,int );
void toh(int, int ,int );
int findmid(int, int);

int main()
{
    toh_r(4, 1, 3);
    printf("==============================\n");
    return 0;
}

void toh_r(int count, int start, int end){
    int mid = findmid(start, end);
    if(count == 1)
        printf("%d->%d\n", start, end);
    else{
        toh_r(count-1, start, mid);
        printf("%d->%d\n", start, end);
        toh_r(count-1, mid, end);
    }
}

int findmid(int start, int end){
        if( (start == 1 && end == 2) || (start == 2 && end == 1) )
            return 3;
        else if( (start == 2 && end  == 3) || (start == 3 && end == 2))
            return 1;
        else
            return 2;
}
