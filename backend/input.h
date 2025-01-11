#ifndef INPUT_H
#define INPUT_H

#include "board.h"

typedef struct input
{
    char move;
    int row;
    int column;
} Input;

typedef struct file
{
    Board inputBoard;
    Input* inputs;
    int inputCount;
} File;

File readFiles(const char* inputFile, const char* mapFile);
void readInputs(File* file, const char* fileName);
void readMap(File* file, const char* fileName);
void changeState(Board* board, int row, int col, Action action);


#endif