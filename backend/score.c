#include <stdio.h>
#include <stdlib.h>

#include "score.h"
#include "game.h"

void saveScore(const Score* score, const char* fileName)
{
    FILE* file = fopen(fileName, "a");
    if (!file)
    {
        perror("Error opening file for saving scores");
        return;
    }

    fprintf(file, "%s %d %d %d\n", score->name, score->correctMoves, score->points, score->success);
    fclose(file);
}

int readScores(Score* score, const char* fileName)
{
    FILE* file = fopen(fileName, "r");
    int scores = 0;
    if (!file)
    {
        perror("Error opening file for reading scores");
        return -1;
    }

    char temps[3];
    int temp;
    while(fscanf(file, " %s %d %d %d", temps, &temp, &temp, &temp) == 4)
      scores++;

    if(!scores)
    {
        fprintf(stderr, "Error reading score data from file\n");
        fclose(file);
        return -1;
    }


    score->scores = calloc(scores, sizeof(Score));
    rewind(file);

    for (int i = 0; i < scores; i++)
    {
        fscanf(file, " %s %d %d %d", score->scores[i].name, &score->scores[i].correctMoves, &score->scores[i].points, &score->scores[i].success);
    }


    fclose(file);
    return scores;
}
