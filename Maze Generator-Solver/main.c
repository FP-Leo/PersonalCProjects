#include <stdio.h>
#include <stdlib.h>
#include <windows.h> // to clear cmd
#include <time.h> // to randomize numbers
#include <math.h> // to use pow function for cleaner code

#define SIZE 10 // code works from size 3 onwards up to 40

//to have an easier time coding solution,it keeps track of starting point(x, y) and endpoint(x, y), starting and ending col stays the same, rows are randomized.
int startingrow;
int endrow;
const int startingcol = 0;
const int endcol = SIZE-1;

//to stop recursion
int found = 0;
int count = 0;
int preferedcount = (pow(SIZE-2, 2)*6)/10;
int stuck = 0;

//for stats purposes
int reset = 0;
unsigned int solved = 0;
unsigned int generated = 0;

//functions that generate the maze
//generates the outside of the maze
void generateMaze(char [][SIZE]);
//generates the inside of the maze
void mazeMaker(char[][SIZE], int * , int * , int * );
//checks if the next path can be placed,we place the path between two walls
void checkTarget(char[][SIZE], int *, int *, int *);
//lays down the path
void setDirection(char [][SIZE], int *, int *, int, int, int);


//functions to solve the maze
//to guide the person
void mazeTraverse(char[][SIZE], int * , int * , int * );
//to change the directions of the person
void changeDirection(char maze[][SIZE], int * x, int * y, int tobechanged, int operation);

//to reset the maze from whichever number we desire to whichever
void resetMaze(char [][SIZE], int, int);
//when the current maze is stuck, resetting only the inside and the points
void restartStuckMaze(char [][SIZE], int *, int *, int *);

//prc to print the current state of the maze
void prc(const char [][SIZE]);
//fully resets everything after the maze is generated and solved
void fullRes(char [][SIZE]);

int main()
{
    //code to hide the cursor in cmd
    HANDLE hStdOut = NULL;
    CONSOLE_CURSOR_INFO curInfo;

    hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleCursorInfo(hStdOut, &curInfo);
    curInfo.bVisible = FALSE;
    SetConsoleCursorInfo(hStdOut, &curInfo);

    //randomize starting direction
    srand(time(NULL));
    //declaring the maze
    char testmaze[SIZE][SIZE];
    for(unsigned int i = 0; i < 1; i++){
        //generate and solve the maze automatically!
        generateMaze(testmaze);
        //for stats purposes
        printf("Gen: %u, Reset: %d, Solved : %u\n", generated, reset, solved);
    }


    return 0;
}



void generateMaze(char maze[][SIZE]){
    //set Maze to blanks
    for(int i = 0; i < SIZE; i++)
        for(int j = 0; j < SIZE; j++){
            if(i == 0 || i == SIZE-1 || j == 0 || j == SIZE-1)
                maze[i][j] = '#';
            else{
                maze[i][j] = ' ';
            }
        }

    //randomly generating starting and ending rows
    startingrow = 1+ rand() % (SIZE-2);
    endrow = 1+ rand() % (SIZE-2);

    //setting the starting point,end point will be set automatically when the maze is generated
    maze[startingrow][startingcol] = '.';
    maze[endrow][endcol] = ' ';

    //copy of the starting point in order to not lose that point
    int x = startingrow, y = startingcol, dir;

    mazeMaker(maze, &x, &y, &dir);
    //for stats purposes
    generated++;

    //resetting the copy in order to solve the generated maze
    x = startingrow;
    y = startingcol;
    dir = 1;

    mazeTraverse(maze, &x, &y, &dir);

    fullRes(maze);
}

void mazeMaker(char maze[][SIZE], int * rowd, int * cold, int * direction){
    //reset the current maze if it cannot find the endpoint
    if (stuck >= pow(SIZE-2, 2) && found == 0)
        restartStuckMaze(maze, rowd, cold, direction);
    //finish the maze if it found the endpoint but there's no place to lay more path
    else if (stuck >= pow(SIZE-2, 2) && found == 1){
            for(int i = 1; i <= SIZE-2; i++){
                for(int j = 1; j <= SIZE-2; j++)
                    if(maze[i][j] == ' ')
                        maze[i][j] = '#';
            }
    }
    //finish the maze if it found the endpoint and it laid more than 60% of available space with path
    else if(count >= preferedcount && found == 1){
            for(int i = 1; i <= SIZE-2; i++){
                for(int j = 1; j <= SIZE-2; j++)
                    if(maze[i][j] == ' ')
                        maze[i][j] = '#';
            }
    } else {
        switch(found){
            case 0: //to help find the endpoint more easily and avoid resets
                    if( *rowd == endrow && *cold == endcol) {found = 1;}
                    else if (*rowd == endrow && *cold > SIZE/3 && ( maze[*rowd][*cold + 1] == '.' || (maze[*rowd][*cold + 1] == ' ' && maze[*rowd + 1][*cold + 1] != '.' && maze[*rowd-1][*cold+1] != '.'))) *direction = 1;
                    else if (*rowd == endrow - 1 && *cold == endcol - 1 && (maze[*rowd+1][*cold] == '.' || (maze[*rowd+1][*cold] == ' ' && maze[*rowd+1][*cold-1] != '.' && maze[*rowd+1][*cold + 1] != '.')))*direction = 2;
                    else if (*rowd == endrow + 1 && *cold == endcol - 1 && (maze[*rowd-1][*cold] == '.' || (maze[*rowd-1][*cold] == ' ' && maze[*rowd-1][*cold-1] != '.' && maze[*rowd-1][*cold + 1] != '.')))*direction = 4;
                    else *direction = 1 + rand() % 4;
                    break;
            case 1:
                    //lay path in a random direction
                    *direction = 1 + rand() % 4;
                    break;
        }

        checkTarget(maze, rowd, cold, direction);
        //recursive call until the conditions are met
        prc(maze);
        Sleep(100);
        system("cls");
        mazeMaker(maze, rowd, cold, direction);
    }
}

void checkTarget(char maze[][SIZE], int * x, int * y, int * dir){
    switch(*dir){
        //first checking if it hit a wall or is going out of bounds,if so do nothing and wait for the call that changes direction
        //if it encounters a path continue on that path
        //if it does not lays the path automatically
        case 1: if(maze[*x][ *y + 1] == '#' || *y+1 >= SIZE){}
                else if(maze[*x][*y + 1] == '.')
                    setDirection(maze, x, y, 1, 1, 0);
                else if(maze[*x][*y + 1] == ' ' && maze[*x + 1][*y + 1] != '.' && maze[*x-1][*y+1] != '.')
                    setDirection(maze, x, y, 1, 1, 1);
        break;
        case 2: if(maze[*x+1][*y] == '#' || *x+1 >= SIZE){}
                else if (maze[*x+1][*y] == '.')
                    setDirection(maze, x, y, 0, 1, 0);
                else if(maze[*x+1][*y] == ' ' && maze[*x+1][*y+1] != '.' && maze[*x+1][*y-1] != '.')
                    setDirection(maze, x, y, 0, 1, 1);
        break;
        case 3: if(maze[*x][*y-1] == '#' || *y-1 < 0){}
                else if(maze[*x][*y-1] == '.')
                    setDirection(maze, x, y, 1, -1, 0);
                else if(maze[*x][*y-1] == ' ' && maze[*x+1][*y-1] != '.' && maze[*x-1][*y-1] != '.')
                    setDirection(maze, x, y, 1, -1, 1);
        break;
        case 4: if(maze[*x-1][*y] == '#' || *x-1 < 0){}
                else if(maze[*x-1][*y] == '.')
                    setDirection(maze, x, y, 0, -1, 0);
                else if(maze[*x-1][*y] == ' ' && maze[*x-1][*y+1] != '.' && maze[*x-1][*y-1] != '.')
                    setDirection(maze, x, y, 0, -1, 1);
        break;
    }
}

void setDirection(char maze[][SIZE], int * x , int * y, int direction, int operation, int type){
    //changes the x and y values of the current point
    switch(direction){
        case 0: *x += operation; break;
        case 1: *y += operation; break;
    }
    //type 1 = new path
    //else it means that it did not find a new path
    if(type == 1){
        maze[*x][*y] = '.';
        stuck = 0;
        count++;
    } else
        stuck++;
}

void mazeTraverse(char maze[][SIZE], int * rowd, int * cold, int * direction){
    //recursive function,every time it's called it checks if it reached the final destination
    if(*rowd == endrow && *cold == endcol){
        //ending recursion
        //for stats purposes
        solved++;
    }else {
        //using the right hand algorithm to solve the maze, algorithm goes like this: place your right hand on the wall and follow a path while never letting go of the wall with your right hand
        switch(*direction){
            case 1: if(maze[*rowd+1][*cold] == '.'){
                        changeDirection(maze, rowd, cold, 0, 1);
                        *direction = 2;
                    } else if(maze[*rowd][*cold+1] == '.'){
                        changeDirection(maze, rowd, cold,  1, 1);
                    } else if(maze[*rowd-1][*cold] == '.'){
                        changeDirection(maze, rowd, cold,  0, -1);
                        *direction = 4;
                    } else
                        *direction = 3;
                    break;
            case 2: if(maze[*rowd][*cold-1] == '.'){
                        changeDirection(maze, rowd, cold,  1, -1);
                        *direction = 3;
                    } else if (maze[*rowd+1][*cold] == '.') {
                        changeDirection(maze, rowd, cold,  0, 1);
                    } else if (maze[*rowd][*cold+1] == '.') {
                        changeDirection(maze, rowd, cold,  1, 1);
                        *direction = 1;
                    } else
                        *direction = 4;
                    break;
            case 3: if(maze[*rowd-1][*cold] == '.'){
                        changeDirection(maze, rowd, cold,  0, -1);
                        *direction = 4;
                    } else if(maze[*rowd][*cold-1] == '.') {
                        changeDirection(maze, rowd, cold,  1, -1);
                    } else if(maze[*rowd+1][*cold] == '.') {
                        changeDirection(maze, rowd, cold,  0, 1);
                        *direction = 2;
                    } else
                        *direction = 1;
                    break;
            case 4: if(maze[*rowd][*cold+1] == '.'){
                        changeDirection(maze, rowd, cold,  1, 1);
                        *direction = 1;
                    } else if(maze[*rowd-1][*cold] == '.') {
                        changeDirection(maze, rowd, cold,  0, -1);
                    } else if(maze[*rowd][*cold-1] == '.') {
                        changeDirection(maze, rowd, cold,  1, -1);
                        *direction = 3;
                    } else
                        *direction = 2;
                    break;
            }
            //recursion call until the maze is solved
            prc(maze);
            Sleep(100);
            system("cls");
            mazeTraverse(maze, rowd, cold, direction);

    }
}

void changeDirection(char maze[][SIZE], int * x , int * y, int direction, int operation){
    //reseting the current location
    maze[*x][*y] = '.';
    //changing the current location based on which direction for which value is gonna change.
    switch(direction){
        case 0: if(*x + operation >= 0 && *x + operation < SIZE) *x += operation;
                break;
        case 1: if(*y + operation >= 0 && *y + operation < SIZE)*y += operation;
                break;
    }
    //setting the current location
    maze[*x][*y] = 'X';
}

void resetMaze(char maze[][SIZE], int start, int finish){
    //resetting maze from border a to border b
    for(int i = start; i < finish; i++)
        for(int j = start; j < finish; j++)
            maze[i][j] = ' ';
}

void restartStuckMaze(char maze[][SIZE], int * x, int * y, int * dir){
    //resets the inside and the starting point
    resetMaze(maze, 1, SIZE-1);

    *x = startingrow;
    *y = startingcol;
    *dir = 1 + rand() % 4;

    count = 0;
    stuck = 0;

    //for stats purpose
    reset++;

    //to try and create another maze with those start and endpoints
    mazeMaker(maze, x, y, dir);

}

void prc(const char currentmaze[][SIZE]){
    //simple function to print a 2D array
    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE;j++){
            printf("%c ", currentmaze[i][j]);
        }
        //after every row a new line
        puts("");
    }
}

void fullRes(char maze[][SIZE]){

    //fully resets everything

    resetMaze(maze, 0, SIZE);

    count = 0;
    stuck = 0;
    found = 0;

}
