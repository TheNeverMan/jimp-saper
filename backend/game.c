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

/*
int setState(Game* game, int row, int col, Action action) its more like game loop than a setter so i moved it TODO: change this to fit game loop
{
    if(row < 0 || row >= game->board.size.rows || col < 0 || col >= game->board.size.columns)
    {
        printf("Invalid row or column\n");
        return 1;
    }
    
    SquareState* square = &game->board.tab[row][col];

    switch(action)
    {
        case REVEAL:
        if(square->revealState == 0)
        {
            square->revealState = 1;
            if(square->mineState == 1)
            {
                 GAME OVER :[ 
                setGameState(game, 1);
            }
            else
            {
                 show revealed square 
            }
        }
        else
        {
            handle already revealed 
        }
        break;

        case FLAG:
        if(square->flagState == 0)
        {
            square->flagState = 1;
            flag square
        }
        else
        {
            handle already flagged 
        }
        break;

        case UNFLAG:
        if(square->flagState == 1)
        {
            square->flagState = 0;
             unflag square 
        }
        else
        {
            handle already unflagged 
        }
        break;

        default:
        printf("Invalid action!\n");
        return 2;
        break;
    }
    return 0;
} 
*/