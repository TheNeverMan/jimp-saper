#include "ui_game.h"

void Update_Game_Title(Game_Windows Windows,Map_Properties Properties)
{
  wattron(Windows.Main_Game_Window,A_BOLD);
  mvwprintw(Windows.Main_Game_Window,1,1,"Map %lux%lu (%lu mines left) Points: %lu",Properties.rows,Properties.cols,Properties.mines, Properties.points);
  wattroff(Windows.Main_Game_Window,A_BOLD);
  wrefresh(Windows.Main_Game_Window);
}

Game_Windows Create_Game_Window(Map_Properties Properties)
{
  Game_Windows out;
  size_t size_x = 7+4;
  size_t size_y = 38+2;
  out.Main_Game_Window = NULL;
  out.Board_Window = NULL;
  if(size_x < (Properties.rows+3))
    size_x = Properties.rows+4;
  if(size_y < (Properties.cols+2))
    size_y = Properties.cols+2;
  out.Main_Game_Window = newwin(size_x,size_y,0,0);
  box(out.Main_Game_Window,0,0);
  Update_Game_Title(out, Properties);
  Move_Window_To_Center(out.Main_Game_Window);
  /* fuck this useless crap of library, not even moving subwindows when moving parents
  so i need to add derwin *after* centering parent, like this bug has 35 years
  https://stackoverflow.com/questions/53445527/moving-windows-in-ncurses
  why is this still a thing */
  out.Board_Window = derwin(out.Main_Game_Window,Properties.rows,Properties.cols,3,1);
  Display_Logo(TRUE);
  Print_Help_Bar("Use Cursor Keys to navigate on the map, Space to toggle flag, Enter reveals tile. Alternatively C opens command prompt.");
  Print_Horizontal_Bar_In_Window(out.Main_Game_Window,2);
  curs_set(TRUE);
  keypad(out.Main_Game_Window, TRUE);
  keypad(out.Board_Window, TRUE);
  return out;
}

void Refresh_Map(Map_Properties Properties, Game_Windows Windows)
{
  size_t index_x = Properties.rows;
  size_t index_y = Properties.cols;
  size_t orig_y = getcury(Windows.Board_Window);
  size_t orig_x = getcurx(Windows.Board_Window);
  werase(Windows.Board_Window);
  wmove(Windows.Board_Window,0,0);
  while(index_y --> 0)
  {
    while(index_x --> 0)
    {

    }
    index_x = Properties.rows;
    wmove(Windows.Board_Window,index_y-1,index_x);
  }
  wmove(Windows.Board_Window,orig_y,orig_x);
  refresh();
}

void Game_Loop(Map_Properties Properties, Game_Windows Windows)
{
  int ch = -1;
  while((ch = wgetch(Windows.Board_Window)) != (KEY_F(1)))
  {
    Refresh_Map(Properties,Windows);
  	switch(ch)
    {
      case ENTER:
        {
          break;
        }
      case KEY_DOWN:
        {
          wmove(Windows.Board_Window,getcury(Windows.Board_Window)+1,getcurx(Windows.Board_Window));
          break;
        }
      case KEY_UP:
        {
          wmove(Windows.Board_Window,getcury(Windows.Board_Window)-1,getcurx(Windows.Board_Window));
          break;
        }
      case KEY_LEFT:
        {
          wmove(Windows.Board_Window,getcury(Windows.Board_Window),getcurx(Windows.Board_Window)-1);
          break;
        }
      case KEY_RIGHT:
        {
          wmove(Windows.Board_Window,getcury(Windows.Board_Window),getcurx(Windows.Board_Window)+1);
          break;
        }
    }
  }
}

void Show_Main_Game(Map_Properties Properties)
{
  Game_Windows Windows = Create_Game_Window(Properties);
  Properties.Game_Board = generateBoard(Properties.rows,Properties.cols,Properties.mines);
  wmove(Windows.Board_Window,0,0);
  wrefresh(Windows.Board_Window);
  Game_Loop(Properties,Windows);
  Destroy_Main_Game(Windows);
}

void Destroy_Main_Game(Game_Windows Windows)
{
  delwin(Windows.Board_Window);
  Clear_Window(Windows.Main_Game_Window);
  curs_set(FALSE);
}
