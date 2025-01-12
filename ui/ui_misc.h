#pragma once
#include <curses.h>
#include <menu.h>
#include <string.h>

#define ENTER 10

typedef enum
{
  INPUT_NUM,
  INPUT_ALPHANUM
} Input_Type;

void Print_In_The_Middle(WINDOW *win, int starty, int startx, int width, char *string, chtype color);
WINDOW* Create_Window_In_The_Middle(int rows, int cols);
size_t Get_Longest_String_Length(char** Array, size_t array_size);
void Move_Window_To_Center(WINDOW* win);
void Clear_Window(WINDOW* win);
void Print_Help_Bar(char* text);
