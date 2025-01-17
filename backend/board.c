#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "board.h"
#include "game.h"

void generateBoard(Board* board, int rows, int cols, int count)
{
    initBoard(board, rows, cols);
    board->mineCount = count;

    placeMines(board, board->firstMoveRow, board->firstMoveCol);
    calculateMines(board);
}

void initBoard(Board* board, int rows, int cols)
{
    board->size.rows = rows;
    board->size.columns = cols;
    board->revealedCount = 0;
    board->tab = calloc(board->size.rows, sizeof(SquareState*));
    for (int i = 0; i < board->size.rows; i++)
    {
        board->tab[i] = calloc(board->size.columns, sizeof(SquareState));
    }
}

void placeMines(Board* board, int firstRow, int firstCol)
{
    int placed = 0;
    srand(time(NULL));

    while(placed < board->mineCount)
    {
        int row = rand() % board->size.rows;
        int col = rand() % board->size.columns;

        if((row == firstRow && col == firstCol) || board->tab[row][col].mineState == 1)
        {
            continue;
        }

        board->tab[row][col].mineState = 1;
        placed++;
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

void revealCell(Board* board, int row, int column)
{
    if (row < 0 || row >= board->size.rows || column < 0 || column >= board->size.columns)
    {
        return;
    }

    if (board->tab[row][column].revealState == 1 || board->tab[row][column].flagState == 1)
    {
        return;
    }

    board->tab[row][column].revealState = 1;
    board->revealedCount++;

    if (board->tab[row][column].minesNear > 0)
    {
        return;
    }

    for (int x = -1; x <= 1; x++)
    {
        for (int y = -1; y <= 1; y++)
        {
            if (x != 0 || y != 0)
            {
                revealCell(board, row + x, column + y);
            }
        }
    }
}
