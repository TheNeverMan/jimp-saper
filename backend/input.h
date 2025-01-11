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
    Board inputBoard; /* Dane z plików */
    Input* inputs;
} File;

void readInputs();
void readMap();

#endif