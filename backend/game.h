#ifndef GAME_H
#define GAME_H

#include "board.h"
#include "score.h"

typedef struct game
{
    Board board;
    Score score;
    int ended;
} Game;

void initGame();
void gameLoop();

/* TODO: CHANGE */
typedef enum 
{
    REVEAL = 0,
    FLAG,
    UNFLAG
} Action;
int setState(Game* game, int row, int col, Action action); /* eventually 0 - Reveal, 1 - flag, 2 - unflag */


#endif