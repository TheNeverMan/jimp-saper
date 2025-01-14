#ifndef INTERFACE_H
#define INTERFACE_H

#include "game.h"
#include "board.h"
#include "input.h"

/* Setters */
int setGameState(Game* game, int state); /* 0 - playing, 1 - ended */
void setSize(Game* game, int rows, int columns);
void setMineCount(Game* game, int count);
int setRevealState(Game* game, int row, int column, int state); /* 0 - zakryte, 1 - odkryte */
int setMineState(Game* game, int row, int column, int state); /* 0 - brak miny, 1 - mina */
int setflagState(Game* game, int row, int column, int state); /* 0 - brak flagi, 1 - flaga */


/* Getters */
int getGameState(const Game* game);
Size getSize(const Game* game); /* Size = int rows, int columns */
int getMineCount(const Game* game);
int getRevealState(const Game* game, int row, int column); /* 0 - zakryte, 1 - odkryte */
int getMineState(const Game* game, int row, int column); /* 0 - brak miny, 1 - mina */
int getflagState(const Game* game, int row, int column); /* 0 - brak flagi, 1 - flaga */

#endif