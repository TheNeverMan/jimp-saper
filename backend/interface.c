#include <stdio.h>

#include "interface.h"
#include "game.h"

int setGameState(Game* game, int state)
{
    if(state != 0 && state != 1)
    {
        printf("Setting wrong game state!\n");
        return -1;
    }
    game->ended = state;
    return 0;
}

int getGameState(const Game* game)
{
    return game->ended;
}

void setSize(Game* game, int rows, int columns)
{
    game->board.size.rows = rows;
    game->board.size.columns = columns;
}

Size getSize(const Game* game)
{
    return game->board.size;
}

void setMineCount(Game* game, int count)
{
    game->board.mineCount = count;
}

int getMineCount(const Game* game)
{
    return game->board.mineCount;
}

int setRevealState(Game* game, int row, int column, int state)
{
    if(row < 0 || row >= game->board.size.rows || column < 0 || column >= game->board.size.columns)
    {
        printf("Setting invalid row or column!\n");
        return -1;
    }

    game->board.tab[row][column].revealState = state;
    return 0;
}

int getRevealState(const Game* game, int row, int column)
{
    if(row < 0 || row >= game->board.size.rows || column < 0 || column >= game->board.size.columns)
    {
        printf("Getting invalid row or column!\n");
        return -1;
    }

    return game->board.tab[row][column].revealState;
}

int setMineState(Game* game, int row, int column, int state)
{
    if(row < 0 || row >= game->board.size.rows || column < 0 || column >= game->board.size.columns)
    {
        printf("Setting invalid row or column!\n");
        return -1;
    }
    game->board.tab[row][column].mineState = state;
    return 0;
}

int getMineState(const Game* game, int row, int column)
{
    if(row < 0 || row >= game->board.size.rows || column < 0 || column >= game->board.size.columns)
    {
        printf("Getting invalid row or column!\n");
        return -1;
    }
    return game->board.tab[row][column].mineState;
}

int setflagState(Game* game, int row, int column, int state)
{
    if(row < 0 || row >= game->board.size.rows || column < 0 || column >= game->board.size.columns)
    {
        printf("Setting invalid row or column!\n");
        return -1;
    }
    game->board.tab[row][column].flagState = state;
    return 0;
}

int getFlagState(const Game* game, int row, int column)
{
    if(row < 0 || row >= game->board.size.rows || column < 0 || column >= game->board.size.columns)
    {
        printf("Getting invalid row or column!\n");
        return -1;
    }
    return game->board.tab[row][column].flagState;
}








