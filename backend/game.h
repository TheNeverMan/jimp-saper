#ifndef GAME_H
#define GAME_H

#include "score.h"
#include "board.h"

typedef struct game
{
    Board board;
    Score score;
    int ended;
    int difficulty;
} Game;

void initGame();
void gameLoopFile(char* inputFile, char* mapFile);
void calculateScore(Game* game, int revealedCells);



#endif