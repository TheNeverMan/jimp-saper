#include "ui_game.h"

void Update_Game_Title(Game_Windows Windows,Game* Main_Game)
{
  int rows = getSize(Main_Game).rows;
  int cols = getSize(Main_Game).columns;
  int mines = getMineCount(Main_Game);
  int points = getScore(Main_Game);
  wattron(Windows.Main_Game_Window,A_BOLD);
  mvwprintw(Windows.Main_Game_Window,1,1,"Map %ix%i (%i mines left) Points: %i",rows,cols,mines,points);
  wattroff(Windows.Main_Game_Window,A_BOLD);
  wrefresh(Windows.Main_Game_Window);
}

Game_Windows Create_Game_Window(Game* Main_Game)
{
  Game_Windows out;
  int size_y = 7+4;
  int size_x = 38+2;
  out.Main_Game_Window = NULL;
  out.Board_Window = NULL;
  if(size_y < (getSize(Main_Game).rows+4))
    size_y = getSize(Main_Game).rows+4;
  if(size_x < (getSize(Main_Game).columns+2))
    size_x = getSize(Main_Game).columns+2;
  out.Main_Game_Window = newwin(size_y,size_x,0,0);
  box(out.Main_Game_Window,0,0);
  Update_Game_Title(out, Main_Game);
  Move_Window_To_Center(out.Main_Game_Window);
  /* fuck this useless crap of library, not even moving subwindows when moving parents
  so i need to add derwin *after* centering parent, like this bug has 35 years
  https://stackoverflow.com/questions/53445527/moving-windows-in-ncurses
  why is this still a thing */
  out.Board_Window = derwin(out.Main_Game_Window,getSize(Main_Game).rows,getSize(Main_Game).columns,3,1);
  Display_Logo(TRUE);
  Print_Help_Bar("Use Cursor Keys to navigate on the map, Space to toggle flag, Enter reveals tile. Alternatively C opens command prompt.");
  Print_Horizontal_Bar_In_Window(out.Main_Game_Window,2);
  curs_set(TRUE);
  keypad(out.Main_Game_Window, TRUE);
  keypad(out.Board_Window, TRUE);
  return out;
}

int Get_Tile_Atrs(Game* Main_Game, int y, int x)
{
  int out = 0;
  if(getRevealState(Main_Game,y,x))
  {
    switch(getMinesNear(Main_Game,y,x))
    {
      case 0:
        out = EMPTY_TILE;
        break;
      case 1:
        out = TILE_1;
        break;
      case 2:
        out = TILE_2;
        break;
      case 3:
        out = TILE_3;
        break;
      case 4:
        out = TILE_4;
        break;
      default:
        out = TILE_OTHER;
    }
    if(getMineState(Main_Game,y,x))
      out = MINE_TILE;
  }
  else
    if(getFlagState(Main_Game,y,x))
      out = FLAG_TILE;
    else
      out = HIDDEN_TILE;
  return out;
}

char Get_Tile_Char(Game* Main_Game,int y, int x)
{
  char out = ' ';
  if(getRevealState(Main_Game,y,x))
  {
    switch(getMinesNear(Main_Game,y,x))
    {
      case 0:
        out = '.';
        break;
      case 1:
        out = '1';
        break;
      case 2:
        out = '2';
        break;
      case 3:
        out = '3';
        break;
      case 4:
        out = '4';
        break;
      default:
        out = '0' + getMinesNear(Main_Game,y,x);
    }
    if(getMineState(Main_Game,y,x))
      out = '*';
  }
  if(getFlagState(Main_Game,y,x))
    out = 'F';
  return out;
}

void Reveal_Whole_Map(Game* Main_Game)
{
  size_t index_y = getSize(Main_Game).rows;
  size_t index_x = getSize(Main_Game).columns;
  while(index_y --> 0)
  {
    while(index_x --> 0)
      setRevealState(Main_Game,index_y,index_x,1);
    index_x = getSize(Main_Game).columns;
  }
}

void Refresh_Map(Game* Main_Game, Game_Windows Windows, bool was_generated)
{
  size_t index_y = getSize(Main_Game).rows;
  size_t index_x = getSize(Main_Game).columns;
  size_t orig_y = getcury(Windows.Board_Window);
  size_t orig_x = getcurx(Windows.Board_Window);
  werase(Windows.Board_Window);
  wmove(Windows.Board_Window,0,0);
  while(index_y --> 0)
  {
    while(index_x --> 0)
    {
      int tile_attrs = 0;
      char tile_char = 0;
      if(was_generated)
      {
        tile_attrs = Get_Tile_Atrs(Main_Game,index_y,index_x);
        tile_char = Get_Tile_Char(Main_Game,index_y,index_x);
        // tile_char = '0' + getMinesNear(Main_Game,index_y,index_x);
      }
      else
      {
        tile_attrs = HIDDEN_TILE;
        tile_char = ' ';
      }
      wattron(Windows.Board_Window,tile_attrs);
      mvwaddch(Windows.Board_Window,index_y,index_x,tile_char);
      wattroff(Windows.Board_Window,tile_attrs);
    }
    index_x = getSize(Main_Game).columns;
  }
  wmove(Windows.Board_Window,orig_y,orig_x);
  refresh();
}

void Game_Loop(Game* Main_Game, Game_Windows Windows)
{
  int ch = -1;
  bool was_generated = FALSE;
  Refresh_Map(Main_Game,Windows,was_generated);
  while((ch = wgetch(Windows.Board_Window)) != (ESCAPE))
  {
  	switch(ch)
    {
      case ENTER:
        {
          if(!was_generated)
          {
            placeMines(&Main_Game->board,getcury(Windows.Board_Window),getcurx(Windows.Board_Window));
            was_generated = TRUE;
          }
          // Reveal_Whole_Map(Main_Game);
          if(!getFlagState(Main_Game,getcury(Windows.Board_Window),getcurx(Windows.Board_Window)))
            setRevealState(Main_Game,getcury(Windows.Board_Window),getcurx(Windows.Board_Window),1);
          break;
        }
      case ' ':
        {
          if(!was_generated)
            break;
          if(getRevealState(Main_Game,getcury(Windows.Board_Window),getcurx(Windows.Board_Window)))
            break;
          int cur_state = getFlagState(Main_Game,getcury(Windows.Board_Window),getcurx(Windows.Board_Window));
          setFlagState(Main_Game,getcury(Windows.Board_Window),getcurx(Windows.Board_Window),1-cur_state);
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
      case 'c':
        {
          char* Field_Descriptions[] = {
            "Enter command:",
            "Confirm",
            (char*)NULL,
          };
          UI_Form* Command_Form = Create_Form(Field_Descriptions,INPUT_ALPHANUM,"Enter command",2,A_BOLD);
          Display_Form(Command_Form);
          char** Output = Run_Form(Command_Form);
          Destroy_Form(Command_Form);
          box(Windows.Main_Game_Window,0,0);
          curs_set(TRUE);
          refresh();
          wrefresh(Windows.Board_Window);
          wrefresh(Windows.Main_Game_Window);
        }
    }
        Refresh_Map(Main_Game,Windows,was_generated);
  }
}

void Show_Main_Game(Game* Main_Game)
{
<<<<<<< HEAD
  Game_Windows Windows = Create_Game_Window(Properties);
  /*Properties.Game_Board = generateBoard(Properties.rows,Properties.cols,Properties.mines);*/
=======
  Game_Windows Windows = Create_Game_Window(Main_Game);
>>>>>>> ui
  wmove(Windows.Board_Window,0,0);
  wrefresh(Windows.Board_Window);
  Game_Loop(Main_Game,Windows);
  Destroy_Main_Game(Windows);
}

void Destroy_Main_Game(Game_Windows Windows)
{
  delwin(Windows.Board_Window);
  Clear_Window(Windows.Main_Game_Window);
  curs_set(FALSE);
}
