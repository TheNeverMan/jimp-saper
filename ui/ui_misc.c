#include "ui_misc.h"

void Print_In_The_Middle(WINDOW *win, int starty, int startx, int width, char *string, chtype color)
{	int length, x, y;
	float temp;

	if(win == NULL)
		win = stdscr;
	getyx(win, y, x);
	if(startx != 0)
		x = startx;
	if(starty != 0)
		y = starty;
	if(width == 0)
		width = 80;

	length = strlen(string);
	temp = (width - length)/ 2;
	x = startx + (int)temp;
	wattron(win, color);
	mvwprintw(win, y, x, "%s", string);
	wattroff(win, color);
	refresh();
}

WINDOW* Create_Window_In_The_Middle(int rows, int cols)
{
  int x,y,x_fin,y_fin;
  getmaxyx(stdscr,x,y);
  x_fin = x/2-rows/2;
  y_fin = y/2-cols/2;
  return newwin(rows,cols,x_fin,y_fin);
}

void Clear_Area(int x, int y, int rows, int cols)
{
  while(x < rows)
  {
    mvhline(x,y,' ', cols);
    x++;
  }
}

void Move_Window_To_Center(WINDOW* win)
{
  int x,y,x_fin,y_fin,rows,cols,start_x,start_y;
  getmaxyx(win,rows,cols);
  getmaxyx(stdscr,x,y);
  getbegyx(win,start_x,start_y);
  x_fin = x/2-rows/2;
  y_fin = y/2-cols/2;
  mvwin(win,x_fin,y_fin);
  Clear_Area(start_x,start_y,rows,cols);
  refresh();
}

size_t Get_Longest_String_Length(char** Array, size_t array_size)
{
  size_t out = strlen(Array[0]);
  array_size--;
  while(array_size --> 0)
    if(strlen(Array[array_size]) > out)
      out = strlen(Array[array_size]);
  return out;
}
