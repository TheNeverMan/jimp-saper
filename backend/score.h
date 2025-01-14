#ifndef SCORE_H
#define SCORE_H

typedef struct score
{
    struct score* scores;
    int correctMoves;
    int points; /* Mnożniki: 1 - łatwy, 2 - normalny, 3 trudny */
    int success; /* 0 - Sukces, 1 - Przegrana */
    char name[3];
} Score;

void saveScore(const Score* score, const char* fileName);
int readScores(Score* score, const char* fileName);

#endif