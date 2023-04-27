#include <stdio.h>
#include <stdlib.h>

int main()
{
    int primes[1000];
    for(int i = 1; i <= 999; i++){
        primes[i] = 1;
    }
    for(int i = 2; i <= 999; i++){
        for(int j = i+1; j <= 999; j++){
            if(j%i == 0){
                primes[j] = 0;
            }
        }
    }
    for(int i = 1; i <= 999; i++){
        if(primes[i] == 1)
            printf("%d\n", i);
    }
    return 0;
}
