#include <stdio.h>
#include <stdlib.h>

#include "../backend/board.h"
#include "../backend/input.h"
#include "../backend/game.h"
#include "../backend/interface.h"

void printBoard(const Board* board) 
{
  for (int i = 0; i < board->size.rows; i++) 
  {
    for (int j = 0; j < board->size.columns; j++) 
    {
      if (board->tab[i][j].mineState == 1) 
      {
        printf("* ");
      } 
      else 
      {
        printf("%d ", board->tab[i][j].minesNear);
      }
    }
    printf("\n");
  }
}

void testReadFiles(const char* mapFile, const char* inputFile) 
{
  File file = readFiles(inputFile, mapFile);
  if(file.inputCount == -1) return;

  printf("Map size: %d rows, %d columns\n", file.inputBoard.size.rows, file.inputBoard.size.columns);
  printBoard(&file.inputBoard);

  printf("Inputs:\n");
  for (int i = 0; i < file.inputCount; i++) 
  {
    printf("Move: %c, Row: %d, Column: %d\n", file.inputs[i].move, file.inputs[i].row, file.inputs[i].column);
  }

  cleanFiles(&file);
}


void testBoard() 
{
  Game game;
  setDifficulty(&game, 1);
  generateBoard(&game.board, game.board.size.rows, game.board.size.columns, game.board.mineCount);

  int mineCount = 0;
  for (int i = 0; i < game.board.size.rows; i++) 
  {
    for (int j = 0; j < game.board.size.columns; j++)
    {
      if (game.board.tab[i][j].mineState == 1)
      {
        mineCount++;
      }
    }
  }

  printBoard(&game.board);

  printf("\nExpected Mines: %d, Found Mines: %d\n", game.board.mineCount, mineCount);

  if (mineCount == game.board.mineCount)
  {
    printf("Test Passed: Correct number of mines placed.\n");
  } 
  else 
  {
    printf("Test Failed: Incorrect number of mines.\n");
  }

  cleanBoard(&game.board);
}


int main(int argv, char** argc)
{
  testBoard();
  //testReadFiles("test/map.txt", "test/moves.txt");

  //gameLoopFile("test/moves.txt", "test/map.txt");
  return 0;
}
