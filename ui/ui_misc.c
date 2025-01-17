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

void Clear_Area_In_Window(WINDOW* win, int rows, int cols)
{
	int x = 0;
	int y = 0;
  while(x < rows)
  {
		mvwhline(win,x,y,' ', cols);
    x++;
  }
}


void Clear_Window(WINDOW* win)
{
	int start_x, start_y,rows,cols;
	getbegyx(win,start_x,start_y);
	getmaxyx(win,rows,cols);
	Clear_Area_In_Window(win,rows,cols);
	wrefresh(win);
	delwin(win);
	Clear_Area(start_x,start_y,rows,cols);
	refresh();
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

void Print_Help_Bar(char* text)
{
	size_t size_x, size_y;
	getmaxyx(stdscr,size_x,size_y);
	mvhline(size_x-1,0,' ',size_y);
	attron(A_DIM);
	mvprintw(size_x-1,0,"%s",text);
	attroff(A_DIM);
	refresh();
}

void Print_Horizontal_Bar_In_Window(WINDOW* win, size_t row)
{
	mvwaddch(win,row,0,ACS_LTEE);
	mvwhline(win,row,1,ACS_HLINE,getmaxx(win)-2);
	mvwaddch(win,row,getmaxx(win)-1, ACS_RTEE);
	wrefresh(win);
}

void Display_Logo(bool show)
{
  size_t logo_length = strlen(logo[1]);
	size_t size_x = getmaxx(stdscr);
  size_t col_beg = 0;
	const char* tmp = logo[0];
  size_t index = 0;
	col_beg = size_x/2 - logo_length/2;
  attron(A_BOLD | COLOR_PAIR(SELECTED_TEXT_COLOR));
  while(tmp)
  {
    if(show)
      mvprintw(index+1,col_beg,"%s",tmp);
    else
      mvhline(index+1,col_beg,' ',logo_length);
    tmp = logo[++index];
  }
  attroff(A_BOLD | COLOR_PAIR(SELECTED_TEXT_COLOR));
  refresh();
}
