#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SUIT 4
#define FACE 13
#define CARDS 52

//notfineshed

int ranNum(int);
void shuffleDeck(int d[][FACE]);
void dealCards(int deck[][FACE], const char *wFACE[], const char *wSUIT[]);
void decidePair(int deck[][FACE], const char *wFACE[], const char *wSUIT[], int numofcards);

int main()
{
    srand(time(NULL));
    const char *suit[SUIT] = {"Hearts", "Diamond" , "Clubs", "Spades"};
    const char *face[FACE] = {"Ace", "Deuce" , "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King"};
    for(int i = 1; i < 10; i++){
        int deck[SUIT][FACE] = {0};
        shuffleDeck(deck);
        decidePair(deck, face, suit, 7);
    }
    return 0;
}

int ranNum(int x){ return rand() % x;}

void shuffleDeck(int d[][FACE]){
    for(size_t card = 0; card < CARDS; card++){
        int x = ranNum(SUIT);
        int y = ranNum(FACE);
        while(d[x][y] != 0){
            x = ranNum(SUIT);
            y = ranNum(FACE);
        }
        d[x][y] = card;
    }
}

void dealCards(int deck[][FACE], const char *wFACE[], const char *wSUIT[]){
    puts("");
    for(size_t card = 0; card < CARDS; card++){
        for(size_t row = 0; row < SUIT; row++){
            for(size_t column = 0; column < FACE; column++){
                if(deck[row][column] == card){
                    printf("%d.%5s of the %-8s\n", card, wFACE[column], wSUIT[row]);
                }
            }
        }
    }
}
void decidePair(int deck[][FACE], const char *wFACE[], const char *wSUIT[], int numofcards){
    puts("");
    int currentHand[FACE] = {0};
    int currentSuits[SUIT] = {0};
    for(size_t card = 0; card < numofcards; card++){
        for(size_t row = 0; row < SUIT; row++){
            for(size_t column = 0; column < FACE; column++){
                if(deck[row][column] == card){
                    printf("%5s of the %-8s\n", wFACE[column], wSUIT[row]);
                    currentHand[column]++;
                    currentSuits[row]++;
                }
            }
        }
    }
    int paircount = 0;
    for(size_t i = 0; i < FACE; i++){
        if(currentHand[i] > 0){
            switch(currentHand[i]){
                case 4: printf("Four of a kind!\n");break;
                case 3: printf("Three of a kind!\n");break;
                case 2: printf("A Pair\n");paircount++;break;
                case 1: break;
            }
        }
    }
    if(paircount == 2)
        printf("%s","TWO PAIR!\n");
    for(size_t i = 0; i < SUIT; i++){
        if(currentSuits[i] == 5)
            printf("Flush");
    }
}
