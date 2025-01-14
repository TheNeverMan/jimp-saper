#include <stdio.h>

#include "game.h"

void gameLoop()
{
    /* 
    init game
    main loop
        user input
        update board
        show board
        if bomb = loose
    show score
    cleanup
    */
}

void initGame()
{

}

void calculateScore(Game* game, int revealedCells)
{
    game->score.points = game->difficulty * revealedCells;
}