#ifndef BOARD_H
#define BOARD_H

typedef struct size
{
    int rows;
    int columns;
} Size;

typedef struct squareState
{
    int revealState; /* 0 - zakryte, 1 - odkryte */
    int mineState; /* 0 - brak miny, 1 - mina */
    int flagState; /* 0 - brak flagi, 1 - flaga */
    int minesNear;
} SquareState;

typedef struct board 
{
    SquareState** tab;
    Size size;
    int mineCount;
} Board;

Board generateBoard(int rows, int cols, int count);
Board initBoard(int rows, int cols);
void placeMines(Board* board);
void calculateMines(Board* board);
void testBoard();
void cleanBoard(Board* board);

#endif