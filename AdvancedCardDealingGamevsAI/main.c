#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SUIT 4
#define FACE 13
#define CARDS 52
#define PHAND 5
#define CCH 3

int dealerwincount = 0;
int playerwincount = 0;
int draw = 0;

//H<3

int cartpos = 1;

void setDeck(int d[][FACE]);
void reshuffle(int d[][FACE]);
void shuffleDeck(int d[][FACE]);
void resetDeck(int d[][FACE]);
void prcdeck(const int d[][FACE]);
void dealHand(const int d[][FACE]);
void evaluate(int [], int[]);

int numcomp(const int, const int);
void sort(int []);


//Deck based on card's values
//Lowest to highest

const char * const suits[SUIT] = {"Clubs", "Diamonds", "Hearts", "Spades"};
const char * const faces[FACE] = {"Deuce", "Three", "Four", "Five",
                         "Six", "Seven", "Eight","Nine",
                         "Ten", "Jack", "Queen", "King", "Ace"};

int main()
{
    //randomize numbers
    srand(time(NULL));

    //deck initialization
    int deck[SUIT][FACE] = {0};

    //formating
    for(int i = 0; i < 64;i++)
        printf("%s", "=");
    puts("\n");

    //deal 10 hands
    for(int i = 0; i < 20;i++){
        //reset in order to do it again
        setDeck(deck);

        //reset the position of the cards
        cartpos = 1;

        //randomizes the deck
        for(int j = 0; j < 4; j++)
            reshuffle(deck);

        //deals two hands and evaluates them
        dealHand(deck);

        //formating
        for(int i = 0; i < 64;i++)
            printf("%s", "=");
        puts("");puts("");
    }

    printf("Player wins: %d\nDealer wins: %d\nDraws: %d\n", playerwincount, dealerwincount, draw);

    return 0;
}

void setDeck(int deck[][FACE]){
    int card = 1;
    //order the deck
    for(int j = 0; j < SUIT; j++){
        for(int k = 0; k < FACE; k++){
            deck[j][k] = card;
            card++;
        }
    }
}

void reshuffle(int deck[][FACE]){
    int ranrow, rancol, temp;
    for(int i = 0; i < SUIT; i++){
        for(int j = 0; j < FACE;j++){
            ranrow = rand() % 4;
            rancol = rand() % 13;
            temp = deck[i][j];
            deck[i][j] = deck[ranrow][rancol];
            deck[ranrow][rancol] = temp;
        }
    }
}

void shuffleDeck(int d[][FACE]){
    int row, column;
    //places 52 cards in random order,cards are represented by row*col not i;
    for(int i = 1; i <= CARDS; i++){
        row = rand() % SUIT;
        column = rand() % FACE;
        while(d[row][column] != 0){
            row = rand() % SUIT;
            column = rand() % FACE;
        }
        d[row][column] = i;
    }
}

void prcdeck(const int d[][FACE]){
    int flag;
    //prints the current deck;
    for(int i = 1; i <= CARDS; i++){
        flag = 0;
        for(int j = 0; j < SUIT; j++){
            if(flag == 1)
                break;
            for(int k = 0; k < FACE; k++){
                if(d[j][k] == i){
                    printf("The %s of %s, ", faces[k], suits[j]);
                    flag = 1;
                    break;
                }
            }
        }
        if(i % 4 == 0)
            puts("");
    }
}

void resetDeck(int d[][FACE]){
    //resets the randomized deck
    for(int j = 0; j < SUIT; j++){
        for(int k = 0; k < FACE; k++){
            d[j][k] = 0;
        }
    }
}

void dealHand(const int d[][FACE]){

    int flag;

    //one function to compare two evaluations
    void compare(int[], int[], const int[][FACE]);

    //declare two hands

    int hand1[10] = {0};
    int hand2[10] = {0};

    int h1count = 0, h2count = 0;

    printf("%s%44s\n", "Hand one", "Hand two");puts("");
    for(; cartpos <= PHAND * 2; cartpos++){
        flag = 0;
        for(int j = 0; j < SUIT; j++){
            if(flag == 1)
                break;
            for(int k = 0; k < FACE; k++){
                if(d[j][k] == cartpos){
                    //doing a fair dealing one to each hand until both reach 5 cards
                    if( cartpos % 2 == 1){
                        printf("%s%s%s\t", faces[k], " of the ", suits[j]);
                        hand1[h1count] = k+2;
                        hand1[h1count+5] = j;
                        h1count++;
                    }
                    if( cartpos % 2 == 0){
                        printf("%-20s%s%s%s\n", "", "Unknown", " of the ", "Unknown");//splitting it into two columns
                        hand2[h2count] = k+2;
                        hand2[h2count + 5] = j;
                        h2count++;
                    }
                    flag = 1;
                    break;
                }
            }
        }
    }
    puts("");

    //sort the hand for easier comparison
    sort(hand1);
    sort(hand2);

    compare(hand1, hand2, d);

}

void compare(int hand1[], int hand2[], const int currentdeck[][FACE]){

    //functions to decide which chards to change and to print the hand
    void decideCardChange(int currentcase[], int currenthand[], const int currentdeck[][FACE], int currentplayer);
    void printHand(const int [], const int[], const int);

    //first-second hand evaluation score;
    int fhe[3] = {0}, she[3] = {0};

    printf("Your current hand: \n");
    printHand(hand1, fhe, 0);
    decideCardChange(fhe, hand1, currentdeck, 0);
    sort(hand1);
    evaluate(hand1, fhe);

    evaluate(hand2, she);
    printf("Dealer's original hand: \n");
    printHand(hand2, she, 1);
    decideCardChange(she, hand2, currentdeck, 1);
    sort(hand2);
    evaluate(hand2, she);

    printf("Your final hand:\n");
    printHand(hand1, fhe, 1);
    printf("Dealers final hand:\n");
    printHand(hand2, she, 1);

    //function to compare the scores
    int result(const int [], const int [], const int[], const int[]);

    int rez = result(fhe, she, hand1, hand2);
    switch(rez){
        case 1:printf("%42s", "You win!\n");
        playerwincount++;break;
        case 0:printf("%42s", "Pot split!\n");
        draw++;break;
        case -1:printf("%40s", "Dealer wins!\n");
        dealerwincount++;break;
    }
}

void printHand(const int currenthand[], const int currenteval[] ,const int type){
    for(int i = 0; i < PHAND * 2; i++)
        printf("%d ", currenthand[i]);
    puts("");
    if(type == 1){
        for(int i = 0; i < 2; i++)
            printf("%d ", currenteval[i]);
        puts("");
    }
}

void evaluate(int hand[], int eval[]){

    int flush = 1, straightcount = 1, royalstraight = 1, pairs = 0, triple = 0, quad = 0, p1, p2, t, q;

    int sh[FACE] = {0};

    for(int i = 0; i < 4; i++){
        //rearranging the hand to calculate pairs
        sh[hand[i] - 2]++;
        //calculating the flush
        if(hand[i+5] == hand[i+6])
            flush++;
        //calculating straight
        if(hand[i] + 1 == hand[i+1]){
            straightcount++;
            if(hand[i] == 2 && hand[4] == 14 && hand[3] != 13)
                straightcount++;
            if(hand[i] >= 10)
                royalstraight++;
        }
    }
    sh[hand[4] - 2]++;

    //rearranging in case of 5 4 3 2 1 straight
    if(straightcount == 5 && hand[4] == 14 && hand[3] == 5){
        hand[4] = 1;
        sort(hand);
    }

    if(royalstraight == 5 && flush == 5){
        //return 9 && hand[5]
        eval[0] = 9;
        eval[1] = hand[5];

    }else if(straightcount == 5 && flush == 5){
        //return 8 && hand[4] && hand[5]
        eval[0] = 8;
        eval[1] = hand[5];

    }else {
        for(int i = 0; i < FACE; i++){
            switch(sh[i]){
                case 2:if(pairs == 1)p2 = i+2;else p1= i+2;pairs++;break;
                case 3:triple++;t = i+2;break;
                case 4:quad++;q = i+2;break;
                default:break;
            }
        }
        if(quad == 1){
            //Four of a kind!
            //return 7 && quad number
            eval[0] = 7;
            eval[1] = q;
        }else if (triple == 1 && pairs == 1){
            //Full House!
            //return 6 && triple number
            eval[0] = 6;
            eval[1] = t;
            eval[2] = p1;
        } else if (flush == 5){
            //Flush!
            //return 5 && suit
            eval[0] = 5;
            eval[1] = hand[5];

        } else if (straightcount == 5){
            //Straight!
            //return 4 && suit
            eval[0] = 4;
        } else if (triple == 1){
            //Three of a kind
            //return 3 && triple number
            eval[0] = 3;
            eval[1] = t;

        } else if (pairs == 2){
            //Two pair
            //return 2 && pairs
            eval[0] = 2;
            eval[1] = p1;
            eval[2] = p2;

        } else if ( pairs == 1){
            //Pair
            //return 1 && compare hands
            eval[0] = 1;
            eval[1] = p1;

        } else {
            //return 0 && compare hands
            eval[0] = 0;
            eval[1] = hand[4];
        }
    }
}

int result(const int fhe[], const int she[], const int hand1[], const int hand2[]){
    if(fhe[0] > she [0])
        return 1;
    else if(fhe[0] < she [0])
        return -1;
    else{
        switch(fhe[0]){
            case 9:
            case 7:
            case 6:
            case 3:
                return numcomp(fhe[1], she[1]);break;
            case 2: if(numcomp(fhe[2], she[2]) != 0) return numcomp(fhe[2], she[2]);
            case 1:
                if(numcomp(fhe[1], she[1]) != 0) return numcomp(fhe[1], she[1]);
            case 8:
            case 5:
            case 4:
            case 0:
                for(int i = 4; i >= 0; i--){
                    if(numcomp(hand1[i], hand2[i]) != 0)
                        return numcomp(hand1[i], hand2[i]);
                }break;
        }
        return 0;
    }
}

void decideCardChange(int currentcase[], int currenthand[], const int currentdeck[][FACE], int currentplayer){
    //function to change a single card
    void changeCard(int pos, int hand[], const int currentdeck[][FACE]);

    if(currentplayer == 0){
        int choice;
        printf("You have the right to change 3 cards!\nHow many do you want to change: ");
        scanf("%d", &choice);
        while(choice < 0 || choice > 3){
            printf("%s", "Error!Only enter 0, 1, 2, 3!: ");
            scanf("%d", &choice);
        }
        for(int i = 0; i < choice;i++){
            int pos;
            printf("%s", "Enter the position of the card you want to change: ");
            scanf("%d", &pos);
            while(pos < 1 || pos > 5){
                printf("%s", "Error!Only enter 1, 2, 3, 4 or 5!: ");
                scanf("%d", &pos);
            }
            changeCard( pos-1, currenthand, currentdeck);
        }
    }else{

        void calcPossibleFlush(int [], const int[]);
        void calcPossibleStraight(int [], const int[]);

        //to calculatig flushes and straights(0->color/starter, 1->count), using a var to save memory
        int fp[2] = {-1, 0}, sp[2] = {-1,0},                                sparingmem = 0;

        calcPossibleFlush(fp, currenthand);
        calcPossibleStraight(sp, currenthand);

        switch(currentcase[0]){
        case 0:
        case 1: if(fp[1] == 4 || (fp[1] == 3 && (sp[1] != 4 && currentcase[0] != 1))){
                    for(int i = 0; i < PHAND; i++){
                        if(currenthand[i+PHAND] != fp[0]){
                            changeCard(i, currenthand, currentdeck);
                        }
                    }
                }
                else if((sp[1] == 3 && currentcase[0] != 1 )|| sp[1] == 4){
                    int cardcount = 0;
                    for(int i = 0; i < PHAND; i++){
                        if(cardcount == CCH)
                            break;
                        if((currenthand[i] > sp[0] + 4 || currenthand[i] < sp[0]) && !(currenthand[i] == 14 && sp[0] == 2)){
                            changeCard(i, currenthand, currentdeck);
                            cardcount++;
                        }
                    }
                }else{
                    int counter = 0;
                    for(int i = 0; i < PHAND; i++){
                        if(counter == CCH)
                            break;
                        if(currenthand[i] != currentcase[1]){
                            changeCard(i, currenthand, currentdeck);
                            counter++;
                        }
                    }
                }break;
        case 2: for(int i = 0; i < PHAND; i++){
                    if(currenthand[i] != currentcase[2])
                        changeCard(i, currenthand, currentdeck);
                }
                break;
        case 3:
        case 6: for(int i = 0; i < PHAND; i++)
                    if(currenthand[i] != currentcase[1] && currenthand[i] != currentcase[2])
                        changeCard(i, currenthand, currentdeck);
                break;
        case 7: if(currenthand[sparingmem] == currentcase[1])
                     sparingmem = 4;
                if(currenthand[sparingmem] < 10)
                     changeCard(sparingmem, currenthand, currentdeck);
                break;
        case 4:
        case 5:
        case 8:
        case 9:
            break;
        }
    }
}

void changeCard(int pos, int hand[], const int currentdeck[][FACE]){
    int flag = 0;
    for(int i = 0; i < SUIT; i++){
        if(flag == 1)
            break;
        for(int j = 0; j < FACE;j++){
            if(currentdeck[i][j] == cartpos){
                hand[pos] = j + 2;
                hand[pos+5] = i;
                flag = 1;
                break;
            }
        }
    }
    cartpos++;
}

void calcPossibleFlush(int fp[], const int hand[]){
    int flushcalc[4] = {0};
    for(int i = 0; i < PHAND; i++){
        flushcalc[hand[i+PHAND]]++;
    }
    for(int i = 0; i < 4; i++){
        if(flushcalc[i] >= 3){
            fp[0] = i;
            fp[1] = flushcalc[i];
        }
    }
}

void calcPossibleStraight(int sp[], const int hand[]){
    int potentialstraights[PHAND] = {1, 1, 1, 1, 1};
    int sstarter = 0, prevchecked = -1, count = -1;
    for(int i = 0; i < PHAND; i++){
       if(hand[i] == 2 && hand[4] == 14)
           potentialstraights[i]++;
       for(int j = 0; j < PHAND;j++){
           if( i != j && hand[j] != prevchecked && hand[i] + 4 >= hand[j] && hand[j] > hand[i] && hand[i] != hand[j])
                potentialstraights[i]++;
           prevchecked = hand[j];
       }
    }
    sstarter = 0;
    for(int i = 1; i < PHAND;i++){
        if(potentialstraights[i] >= count){
            count = potentialstraights[i];
            sstarter = i;
        }
    }
    sp[0] = hand[sstarter];
    sp[1] = potentialstraights[sstarter];
}

int numcomp(const int i, const int j){
    if (i > j)
        return 1;
    else if (i < j)
        return -1;
    else
        return 0;
}

void sort(int hand[]){
    int temp;
    int temp2;
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            if(hand[j] > hand[j+1]){
                temp = hand[j];
                hand[j] = hand[j+1];
                hand[j+1] = temp;
                temp2 = hand[j+5];
                hand[j+5] = hand[j+6];
                hand[j+6] = temp2;
            }
        }
    }
}
