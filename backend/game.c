#include <stdio.h>

#include "game.h"
#include "input.h"
#include "interface.h"

void gameLoopFile(char* inputFile, char* mapFile)
{
    File file = readFiles(inputFile, mapFile);
    Game game;
    game.board = file.inputBoard;
    game.ended = 0;
    calculateMines(&game.board);
    int i = 0;
    int moves = 0;
    int won;

    while(game.ended == 0)
    {   
        printf("i: %d\n", i);
        if(i == file.inputCount)
        {
            game.ended = 1;
            won = 1;
            break;
        }

        /*for (int i = 0; i < game.board.size.rows; i++) 
        {
            for (int j = 0; j < game.board.size.columns; j++) 
            {
                if(game.board.tab[i][j].mineState == 0)
                {
                    printf(" %d", game.board.tab[i][j].minesNear);
                }
                else printf(" *");
            }
            printf("\n");
        }*/

        if(file.inputs[i].move == 'r')
        {
            if(game.board.tab[file.inputs[i].row][file.inputs[i].column].flagState == 0)
            {
                if(game.board.tab[file.inputs[i].row][file.inputs[i].column].mineState == 1)
                {
                    game.ended = 1;
                    won = 1;
                    break;
                }
                else if(game.board.tab[file.inputs[i].row][file.inputs[i].column].revealState == 0)
                {
                    
                    revealCell(&game.board, file.inputs[i].row, file.inputs[i].column);
                    moves++;
                    
                }
            }
        }
        else if(file.inputs[i].move == 'f')
        {
             game.board.tab[file.inputs[i].row][file.inputs[i].column].flagState = !game.board.tab[file.inputs[i].row][file.inputs[i].column].flagState;
        }

        int cells = 0;
        for(int j = 0; j < game.board.size.rows; j++)
        {
            for(int k = 0; k < game.board.size.columns; k++)
            {
                if(game.board.tab[j][k].revealState == 1)
                {
                    cells++;
                }
                //printf("cells: %d\n", cells);
            }
        }

        game.score.points = cells;

        if(cells == (game.board.size.columns * game.board.size.rows) - game.board.mineCount)
        {
            game.ended = 1;
            won = 0;
            break;
        }

        i++;
    }
    won = 1;
    printf("Moves: %d Points: %d Won: %d\n", moves, game.score.points, won);
}

void initGame(Game* game)
{
    
}

void calculateScore(Game* game, int revealedCells)
{
    game->score.points = game->difficulty * revealedCells;
}