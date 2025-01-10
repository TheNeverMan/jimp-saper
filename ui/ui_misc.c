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
