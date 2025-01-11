#ifndef SCORE_H
#define SCORE_H

typedef struct score
{
    int correctMoves;
    int points; /* Mnożniki: 1 - łatwy, 2 - normalny, 3 trudny */
    int success; /* 0 - Sukces, 1 - Przegrana */
} Score;

void saveScore();
void calculateScore();

#endif