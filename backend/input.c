#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

#include "input.h"
#include "board.h"
#include "game.h"

File readFiles(const char* inputFile, const char* mapFile)
{
    File file = {.inputs = NULL};

    if(readMap(&file, mapFile) != 0) file.inputCount = -1;
    else if(readInputs(&file, inputFile) != 0) file.inputCount = -1;

    return file;
}


int readInputs(File* file, const char* fileName)
{
    FILE* fileStream = fopen(fileName, "r");

    if (!fileStream) 
    {
        printf("Error opening file!\n");
        return 1;
    }

    char action;
    int row, col;
    file->inputCount = -1;
    int result;

    do
    {
        result = fscanf(fileStream, " %c %d %d", &action, &row, &col);
        if(action != 'f' && action != 'r')
        {
            printf("Invalid action!\n");
            fclose(fileStream);
            return 2;
        }
        else if(row < 0 || row >= file->inputBoard.size.rows || col < 0 || col >= file->inputBoard.size.columns)
        {
            printf("Invalid postion!\n");
            fclose(fileStream);
            return 3;
        }
        else if(result == 1 || result == 2)
        {
            printf("Error!\n");
            fclose(fileStream);
            return 4;
        }
        file->inputCount++;
    }
    while(result == 3);
    
    rewind(fileStream);

    file->inputs = calloc(file->inputCount, sizeof(Input));

    for(int i = 0; i < file->inputCount; i++)
    {
        fscanf(fileStream, "%s %d %d", &file->inputs[i].move, &file->inputs[i].row, &file->inputs[i].column);
    }

    fclose(fileStream);
    return 0;
}

int readMap(File* file, const char* fileName)
{
    FILE* fileStream = fopen(fileName, "r");

    if (!fileStream) 
    {
        printf("Error opening file!\n");
        return 1;
    }

    int result = fscanf(fileStream, "%d %d", &file->inputBoard.size.rows, &file->inputBoard.size.columns);
    if(result != 2)
    {
        printf("Wrong map file format!\n");
        fclose(fileStream);
        return 2;
    }

    int count = 0;
    int temp;

    while(fscanf(fileStream, "%d", &temp) == 1) count++;
    if(count != file->inputBoard.size.rows * file->inputBoard.size.columns)
    {
        printf("Wrong map file format!\n");
        fclose(fileStream);
        return 3;
    }

    rewind(fileStream);
    for(int i = 0; i < 2; i++) fscanf(fileStream, "%d", &temp);

    file->inputBoard = initBoard(file->inputBoard.size.rows, file->inputBoard.size.columns);

    for(int i = 0; i < file->inputBoard.size.rows; i++)
    {
        for(int j = 0; j < file->inputBoard.size.columns; j++)
        {
            result = fscanf(fileStream, "%d", &file->inputBoard.tab[i][j].mineState);
            if(file->inputBoard.tab[i][j].mineState == 1) file->mineCount++;
            if(result != 1)
            {
                printf("Wrong map file format!\n");
                fclose(fileStream);
                return 4;
            }
            else if(file->inputBoard.tab[i][j].mineState != 0 && file->inputBoard.tab[i][j].mineState != 1)
            {
                printf("Wrong map file format!\n");
                fclose(fileStream);
                return 5; 
            }
        }
    }

    fclose(fileStream);
    return 0;
}

void cleanFiles(File* file)
{
    if(file->inputs != NULL) free(file->inputs);
    cleanBoard(&file->inputBoard);
}