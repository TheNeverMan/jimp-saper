#ifndef GAME_H
#define GAME_H

#include "board.h"
#include "score.h"

typedef struct game
{
    Board board;
    Score score;
} Game;

void initGame();
void gameLoop();


#endif