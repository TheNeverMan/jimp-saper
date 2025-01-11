#include <stdio.h>
#include <stdlib.h>

#include "../backend/board.h"
#include "../backend/input.h"

void testReadFiles(const char* mapFile, const char* inputFile) 
{
  File file = readFiles(inputFile, mapFile);

  printf("Map size: %d rows, %d columns\n", file.inputBoard.size.rows, file.inputBoard.size.columns);
  
  for (int i = 0; i < file.inputBoard.size.rows; i++) 
  {
    for (int j = 0; j < file.inputBoard.size.columns; j++) 
    {
      printf("%d ", file.inputBoard.tab[i][j].mineState);
    }

    printf("\n");
  }

  printf("Inputs:\n");
  for (int i = 0; i < file.inputCount; i++) 
  {
    printf("Move: %c, Row: %d, Column: %d\n", file.inputs[i].move, file.inputs[i].row, file.inputs[i].column);
  }

  cleanBoard(&file.inputBoard);
  free(file.inputs);
}

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

void testBoard() 
{
  Board board = generateBoard(9, 9, 10);

  int mineCount = 0;
  for (int i = 0; i < board.size.rows; i++) 
  {
    for (int j = 0; j < board.size.columns; j++)
    {
      if (board.tab[i][j].mineState == 1)
      {
        mineCount++;
      }
    }
  }

  printBoard(&board);

  printf("\nExpected Mines: %d, Found Mines: %d\n", board.mineCount, mineCount);

  if (mineCount == board.mineCount)
  {
    printf("Test Passed: Correct number of mines placed.\n");
  } 
  else 
  {
    printf("Test Failed: Incorrect number of mines.\n");
  }

  cleanBoard(&board);
}

int main(int argv, char** argc)
{
  //testBoard();
  testReadFiles("test/map.txt", "test/moves.txt");
  return 0;
}
