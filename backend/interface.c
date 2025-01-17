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

int calcWinState(Game* game)
{
    if(game->board.revealedCount == ((game->board.size.columns * game->board.size.rows) - game->board.mineCount))
    {
        game->won = 1;
        game->ended = 1;
    }
    return game->won;
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

    if(state == 1)
    {
        revealCell(&game->board, row, column);
    }
    else
    {
        game->board.tab[row][column].revealState = state;
    }

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

int setFlagState(Game* game, int row, int column, int state)
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

void setDifficulty(Game* game, int difficulty)
{
    switch (difficulty)
    {
    case 0:
        game->difficulty = 1;
        game->board.size.columns = 9;
        game->board.size.rows = 9;
        game->board.mineCount = 10;
        break;

    case 1:
        game->difficulty = 2;
        game->board.size.columns = 16;
        game->board.size.rows = 16;
        game->board.mineCount = 40;
        break;

    case 2:
        game->difficulty = 3;
        game->board.size.columns = 30;
        game->board.size.rows = 16;
        game->board.mineCount = 99;
        break;

    case 3:
        game->difficulty = 2;
        game->board.size = getSize(game);
        game->board.mineCount = getMineCount(game);
        break;

    default:
        game->difficulty = 1;
        game->board.size.columns = 9;
        game->board.size.rows = 9;
        game->board.mineCount = 10;
        break;
    }

    initBoard(&game->board,game->board.size.rows, game->board.size.columns);
    // generateBoard(&game->board, game->board.size.rows, game->board.size.columns, game->board.mineCount);
}

int getScore(const Game* game)
{
    calculateScore(game, game->board.revealedCount);
    return game->score.points;
}

int getMinesNear(const Game* game, int row, int column)
{
    return game->board.tab[row][column].minesNear;
}

void generateMap(Game* game, int firstMoveRow, int firstMoveCol)
{
    placeMines(&game->board, firstMoveRow, firstMoveCol);
    calculateMines(&game->board);
}
