#ifndef INPUT_H
#define INPUT_H

#include "board.h"
#include "game.h"

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
int readInputs(File* file, const char* fileName);
int readMap(File* file, const char* fileName);
void cleanFiles();

/* Setters */


#endif