#ifndef BOARD_H
#define BOARD_H

typedef struct size
{
    int columns;
    int rows;
} Size;

typedef struct board 
{
    int** tab;
    Size size;
} Board;

typedef struct squareState
{
    int revealState; /* 0 - zakryte, 1 - odkryte */
    int mineState; /* 0 - brak miny, 1 - mina */
    int flagState; /* 0 - brak flagi, 1 - flaga */
} SquareState;

void generateBoard();
void changeState();

#endif