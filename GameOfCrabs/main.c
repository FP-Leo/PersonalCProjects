#include <stdio.h>
#include <stdlib.h>
#include <time.h>

enum Status { WON, LOST, CONTINUE};

typedef enum Status S;

int rollDice(void);
void play();
int * bankbalance();
int ask();
int getamount();
void prb();


int main()
{
    srand(time(NULL));
    prb();
    play();
    int ans = 1;
    while(ans == 1){
        prb();
        printf("Do you want to play again?\n");
        ans = ask();
        if(ans == 1)
            play();
    }
    return 0;
}

void prb(){
    int *cb = bankbalance();
    printf("CB: %d\n", *cb);
}

int rollDice(){
    int dice1 = 1 + rand() % 6;
    int dice2 = 1 + rand() % 6;

    printf("The player rolled : %d and %d,total = %d\n", dice1, dice2, dice1 + dice2);

    return dice1 + dice2;
}

int *bankbalance(){
    static int bankbalance = 1000;
    return &bankbalance;
}

int ask(){
    int ans = 0;
    while(ans != 1 && ans != 2){
        printf("%s", "Press 1 for yes, 2 for no: ");
        scanf("%d", &ans);
    }
    return ans;
}

int getamount(){
    int amount;
    printf("%s", "Enter the amount: ");
    scanf("%d", &amount);
    return amount;
}

void play(){
    printf("Do you want to wager money?\n");
    int wager = ask();
    int *currentbalance =  bankbalance();
    int amount;
    while( wager == 1){
        amount = getamount();
        if(amount > *currentbalance)
            printf("Error!Not enough money,try again!\n");
        else
            break;
    }
    int myPoint;
    int total = rollDice();
    S gameS;
    switch(total){
        case 7:
        case 11:
            gameS = WON;break;
        case 2:
        case 3:
        case 12:
            gameS = LOST;break;
        default:
            gameS = CONTINUE;
            myPoint = total;
            printf("Current point is: %d\n", myPoint);
            break;
    }
    while(gameS == CONTINUE){
        total = rollDice();
        if(total == myPoint)
            gameS = WON;
        else if(total == 7)
            gameS = LOST;
    }
    if( gameS == WON ){
        printf("Congrats you won!\n");
        *currentbalance += amount;
    }
    else{
        printf("You lose!\n");
        *currentbalance -= amount;
    }
}
