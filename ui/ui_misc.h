#pragma once
#include <curses.h>
#include <menu.h>
#include <string.h>

#define ENTER 10

void Print_In_The_Middle(WINDOW *win, int starty, int startx, int width, char *string, chtype color);
WINDOW* Create_Window_In_The_Middle(int rows, int cols);
