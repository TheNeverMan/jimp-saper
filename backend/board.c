#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "board.h"

Board generateBoard(int rows, int cols, int count)
{
    Board board = initBoard(rows, cols);
    board.mineCount = count;

    placeMines(&board);
    calculateMines(&board);

    return board;
}

Board initBoard(int rows, int cols)
{
    Board board;
    board.size.rows = rows;
    board.size.columns = cols;

    board.tab = calloc(board.size.rows, sizeof(SquareState*));
    for (int i = 0; i < board.size.rows; i++)
    {
        board.tab[i] = calloc(board.size.columns, sizeof(SquareState));
    }

    return board;
}

void placeMines(Board* board)
{
    int placed = 0;
    srand(time(NULL));

    while(placed < board->mineCount)
    {
        int row = rand() % board->size.rows;
        int col = rand() % board->size.columns;

        if (board->tab[row][col].mineState == 0) 
        {
            board->tab[row][col].mineState = 1; 
            placed++;
        }
    }
}

void calculateMines(Board* board)
{
    for(int i = 0; i < board->size.rows; i++)
    {
        for(int j = 0; j < board->size.columns; j++)
        {
            if (board->tab[i][j].mineState == 1) continue;

            int count = 0;
            for(int k = -1; k <=1; k++)
            {
                for(int l = -1; l <= 1; l++)
                {
                    int s = i + k;
                    int t = j + l;

                    if(s >= 0 && s < board->size.rows && t >= 0 && t < board->size.columns && board->tab[s][t].mineState ==1)
                    {
                        count++;
                    }
                }
            }
            board->tab[i][j].minesNear = count;
        }
    }
}

void cleanBoard(Board* board)
{
    for (int i = 0; i < board->size.rows; i++)
    {
        free(board->tab[i]);
    }
    free(board->tab);
}