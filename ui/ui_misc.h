#pragma once
#include <curses.h>
#include <menu.h>
#include <string.h>

#include "colors.h"

#define ENTER 10

typedef enum
{
  INPUT_NUM,
  INPUT_ALPHANUM
} Input_Type;

typedef struct
{
  size_t rows;
  size_t cols;
  size_t mines;
  size_t points;
} Map_Properties;

extern char* logo[];


void Print_In_The_Middle(WINDOW *win, int starty, int startx, int width, char *string, chtype color);
WINDOW* Create_Window_In_The_Middle(int rows, int cols);
size_t Get_Longest_String_Length(char** Array, size_t array_size);
void Move_Window_To_Center(WINDOW* win);
void Clear_Window(WINDOW* win);
void Print_Help_Bar(char* text);
void Print_Horizontal_Bar_In_Window(WINDOW* win, size_t row);
void Display_Logo(bool show);
