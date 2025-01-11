#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

#include "input.h"
#include "board.h"

File readFiles(const char* inputFile, const char* mapFile)
{
    File file;

    readMap(&file, mapFile);
    readInputs(&file, inputFile);

    return file;
}

void readInputs(File* file, const char* fileName)
{
    FILE* fileStream = fopen(fileName, "r");

    if (!fileStream) 
    {
        printf("Error opening file!\n");
        return;
    }

    char action;
    int row, col;
    file->inputCount = 0;

    while(fscanf(fileStream, " %c %d %d", &action, &row, &col) == 3)
    {
        if(action != 'f' && action != 'r')
        {
            printf("Invalid action!\n");
            fclose(fileStream);
            return;
        }
        else if(row < 0 || row >= file->inputBoard.size.rows || col < 0 || col >= file->inputBoard.size.columns)
        {
            printf("Invalid postion!\n");
            fclose(fileStream);
            return;
        }
        file->inputCount++;
    }
    rewind(fileStream);

    file->inputs = calloc(file->inputCount, sizeof(Input));

    for(int i = 0; i < file->inputCount; i++)
    {
        fscanf(fileStream, "%s %d %d", &file->inputs[i].move, &file->inputs[i].row, &file->inputs[i].column);
    }

    fclose(fileStream);
}

void readMap(File* file, const char* fileName)
{
    FILE* fileStream = fopen(fileName, "r");

    if (!fileStream) 
    {
        printf("Error opening file!\n");
        return;
    }

    int result = fscanf(fileStream, "%d %d", &file->inputBoard.size.rows, &file->inputBoard.size.columns);
    if(result != 2)
    {
        printf("Wrong map file format!\n");
        fclose(fileStream);
        return;
    }

    file->inputBoard = initBoard(file->inputBoard.size.rows, file->inputBoard.size.columns);

    for(int i = 0; i < file->inputBoard.size.rows; i++)
    {
        for(int j = 0; j < file->inputBoard.size.columns; j++)
        {
            result = fscanf(fileStream, "%d", &file->inputBoard.tab[i][j].mineState);
            if(result != 1)
            {
                printf("Wrong map file format!\n");
                fclose(fileStream);
                return;
            }
        }
    }

    fclose(fileStream);
}

void changeState(Board* board, int row, int col, Action action)
{
    if(row < 0 || row >= board->size.rows || col < 0 || col >= board->size.columns)
    {
        printf("Invalid row or column\n");
        return;
    }
    
    SquareState* square = &board->tab[row][col];

    switch(action)
    {
        case REVEAL:
        if(square->revealState == 0)
        {
            square->revealState = 1;
            if(square->mineState == 1)
            {
                /* GAME OVER :[ */
            }
            else
            {
                /* show revealed square */
            }
        }
        else
        {
            /* handle already revealed */
        }
        break;

        case FLAG:
        if(square->flagState == 0)
        {
            square->flagState = 1;
            /* flag square */
        }
        else
        {
            /* handle already flagged */
        }
        break;

        case UNFLAG:
        if(square->flagState == 1)
        {
            square->flagState = 0;
            /* unflag square */
        }
        else
        {
            /* handle already unflagged */
        }
        break;

        default:
        printf("Invalid action!\n");
        break;
    }
}