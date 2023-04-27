#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void askqa(char *[], char*[], int);
void askqs(char *[], char*[], int);
void askqm(char *[], char*[], int);
int getans(int start, int end);

int count1 = 0, count2 = 0;

int main()
{
    srand(time(NULL));
    printf("Choose the arithmetic operation!\n1.+\n2.-\n3.*\n4.Random\n");
    int arthop = getans(1, 4);
    printf("Choose a difficulty!\n1.Easy\n2.Challenging\n3.Hard\n4.Extreme\n");
    int difficulty = getans(1, 4);
    printf("You have only the right to input 10 answers!\n");
    char * correctanswers[] = {"Very good!", "Excellent!", "Nice work!", "Keep up the good work!"};
    char * wronganswers[] = {"No. Please try again!", "Wrong. Try once more.", "Don't give up.", "No. Keep trying!"};
    if(arthop == 4)
        arthop = 1 + rand() % 3;
    switch(arthop){
    case 1:while(count1 + count2 < 10){askqa(correctanswers, wronganswers, difficulty);}break;
    case 2:while(count1 + count2 < 10){askqs(correctanswers, wronganswers, difficulty);}break;
    case 3:while(count1 + count2 < 10){askqm(correctanswers, wronganswers, difficulty);}break;
    }
    float prc = (count1*100)/10;
    printf("Percentage: %f\n" ,prc);
    printf("Play again?\n1.Yes\n2.No\n");
    int playagain = getans(1, 2);
    if(playagain == 1){
        count1 = 0;
        count2 = 0;
        main();
    }
    return 0;
}

int getans(int start, int end){
    int rnum;
    printf("%s", "Enter a number!: ");
    scanf("%d", &rnum);
    while(rnum < start || rnum > end){
        printf("%s", "Out of bounds!Try again: ");
        scanf("%d", &rnum);
    }
    return rnum;
}

void askqa(char * correcta[], char * wronga[], int difficulty){
    int num1, num2;
    switch(difficulty){
        case 1:num1 = rand() % 10;num2 = rand() % 10;break;
        case 2:num1 = rand() % 100;num2 = rand() % 100;break;
        case 3:num1 = rand() % 1000;num2 = rand() % 1000;break;
        case 4:num1 = rand() % 10000;num2 = rand() % 10000;break;
    }
    int ans, ran;
    printf("How much is %d + %d?: ", num1, num2);
    scanf("%d", &ans);
    ran = rand() % 4;
    while(ans != num1 + num2){
        count2++;
        if(count1 + count2 == 10)
            break;
        printf("%s\n", wronga[ran]);
        scanf("%d", &ans);
        ran = rand() % 4;
    }
    if(count1 + count2 != 10){
        printf("%s\n", correcta[ran]);
        count1++;
    }
}

void askqs(char * correcta[], char * wronga[], int difficulty){
    int num1, num2;
    switch(difficulty){
        case 1:num1 = rand() % 10;num2 = rand() % 10;break;
        case 2:num1 = rand() % 100;num2 = rand() % 100;break;
        case 3:num1 = rand() % 1000;num2 = rand() % 1000;break;
        case 4:num1 = rand() % 10000;num2 = rand() % 10000;break;
    }
    int ans, ran;
    printf("How much is %d - %d?: ", num1, num2);
    scanf("%d", &ans);
    ran = rand() % 4;
    while(ans != num1 - num2){
        count2++;
        if(count1 + count2 == 10)
            break;
        printf("%s\n", wronga[ran]);
        scanf("%d", &ans);
        ran = rand() % 4;
    }
    if(count1 + count2 != 10){
        printf("%s\n", correcta[ran]);
        count1++;
    }
}

void askqm(char * correcta[], char * wronga[], int difficulty){
    int num1, num2;
    switch(difficulty){
        case 1:num1 = rand() % 10;num2 = rand() % 10;break;
        case 2:num1 = rand() % 100;num2 = rand() % 100;break;
        case 3:num1 = rand() % 1000;num2 = rand() % 1000;break;
        case 4:num1 = rand() % 10000;num2 = rand() % 10000;break;
    }
    int ans, ran;
    printf("How much is %d times %d?: ", num1, num2);
    scanf("%d", &ans);
    ran = rand() % 4;
    while(ans != num1 * num2){
        count2++;
        if(count1 + count2 == 10)
            break;
        printf("%s\n", wronga[ran]);
        scanf("%d", &ans);
        ran = rand() % 4;
    }
    if(count1 + count2 != 10){
        printf("%s\n", correcta[ran]);
        count1++;
    }
}


