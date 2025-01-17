#include "ui_game.h"

void Update_Game_Title(Game* Main_Game,Game_Windows Windows)
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
  Update_Game_Title(Main_Game,out);
  Move_Window_To_Center(out.Main_Game_Window);
  /* fuck this useless crap of library, not even moving subwindows when moving parents
  so i need to add derwin *after* centering parent, like this bug has 35 years
  https://stackoverflow.com/questions/53445527/moving-windows-in-ncurses
  why is this still a thing */
  out.Board_Window = derwin(out.Main_Game_Window,getSize(Main_Game).rows,getSize(Main_Game).columns,3,1);
  Display_Logo(TRUE);
  Print_Help_Bar("Use Cursor Keys to navigate on the map, Space to toggle flag, Enter reveals tile. Alternatively C opens command prompt. Escape leaves game.");
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
      case 5:
        out = TILE_5;
        break;
      case 6:
        out = TILE_6;
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
    if(getMinesNear(Main_Game,y,x))
      out = '0' + getMinesNear(Main_Game,y,x);
    else
      out = '.';
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

void Refresh(Game* Main_Game,Game_Windows Windows,bool was_generated)
{
  curs_set(FALSE);
  Update_Game_Title(Main_Game,Windows);
  Refresh_Map(Main_Game,Windows,was_generated);
  curs_set(TRUE);
}

void Save_Score(Game* Main_Game, bool is_victorious,int score)
{
  char* Field_Descriptions[] = {
    "Enter name:",
    "Confirm",
    (char*)NULL,
  };
  char* form_title;
  int title_attrs;
  if(is_victorious)
    {
      form_title = "You have won!";
      title_attrs = A_BOLD;
    }
  else
    {
      form_title = "You have lost!";
      title_attrs = A_BOLD | SELECTED_TEXT_COLOR;
    }
  UI_Form* Command_Form = Create_Form(Field_Descriptions,INPUT_ALPHANUM,form_title,2,title_attrs);
  Display_Form(Command_Form);
  char** Output = Run_Form(Command_Form);
  Destroy_Form(Command_Form);
  Main_Game->score.success = is_victorious;
  Main_Game->score.points = score;
  memcpy(Main_Game->score.name,Output[0],3);
  Main_Game->score.name[2] = '\0';
  if(Output[0][0] == ' ' && Output[0][1] == ' ')
  {
    Main_Game->score.name[0] = 'N';
    Main_Game->score.name[1] = 'N';
  }
  saveScore(&Main_Game->score,SCORES_FILE);
  curs_set(FALSE);
}

void End_Game(Game* Main_Game, Game_Windows Windows, bool is_victorious)
{
  Refresh(Main_Game,Windows,TRUE);
  flash();
  beep();
  refresh();
  int score = getScore(Main_Game);
  Reveal_Whole_Map(Main_Game);
  Refresh_Map(Main_Game,Windows,TRUE);
  wgetch(Windows.Board_Window);
  Save_Score(Main_Game,is_victorious,score);
}

void Game_Loop(Game* Main_Game, Game_Windows Windows)
{
  int ch = -1;
  bool was_generated = FALSE;
  bool loop = TRUE;
  Refresh(Main_Game,Windows,was_generated);
  while(((ch = wgetch(Windows.Board_Window)) != (ESCAPE)) && loop)
  {
    //Refresh_Map(Properties,Windows);
  	switch(ch)
    {
      case ENTER:
        {
          if(!was_generated)
          {
            generateMap(Main_Game,getcury(Windows.Board_Window),getcurx(Windows.Board_Window));
            was_generated = TRUE;
          }
          // Reveal_Whole_Map(Main_Game);
          if(getFlagState(Main_Game,getcury(Windows.Board_Window),getcurx(Windows.Board_Window)))
            break;
          setRevealState(Main_Game,getcury(Windows.Board_Window),getcurx(Windows.Board_Window),1);
          if(getMineState(Main_Game,getcury(Windows.Board_Window),getcurx(Windows.Board_Window)))
          {
            loop = FALSE;
            End_Game(Main_Game,Windows,FALSE);
          }
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
      case 'd':
        {
          Reveal_Whole_Map(Main_Game);
          Refresh(Main_Game,Windows,was_generated);
          continue;
        }
      case KEY_RIGHT:
        {
          wmove(Windows.Board_Window,getcury(Windows.Board_Window),getcurx(Windows.Board_Window)+1);
          break;
        }
      case 'c':
        {
          char action = ' ';
          int row = 0;
          int col = 0;
          bool second_time = FALSE;
          int title_attrs = A_BOLD;
          int result = 0;
          do
          {
            char* form_title = "Enter Command";
            char* Field_Descriptions[] = {
              "Enter command:",
              "Confirm",
              (char*)NULL,
            };
            if(!second_time)
            {
              form_title = "Enter Command";
              title_attrs = A_BOLD | COLOR_PAIR(STANDARD_TEXT_COLOR);
            }
            else
            {
              form_title = "Invalid Command!";
              title_attrs = A_BOLD | COLOR_PAIR(SELECTED_TEXT_COLOR);
            }
            UI_Form* Command_Form = Create_Form(Field_Descriptions,INPUT_ALPHANUM,form_title,2,title_attrs);
            Display_Form(Command_Form);
            char** Output = Run_Form(Command_Form);
            Destroy_Form(Command_Form);
            box(Windows.Main_Game_Window,0,0);
            curs_set(TRUE);
            refresh();
            wrefresh(Windows.Board_Window);
            wrefresh(Windows.Main_Game_Window);
            result = sscanf(Output[0],"%c %d %d",&action,&row,&col);
            free(Output[0]);
            free(Output);
            if(action != 'r' && action != 'f')
              result = 0;
            if(row < 0 || row > getSize(Main_Game).rows)
              result = 0;
            if(col < 0 || col > getSize(Main_Game).columns)
              result = 0;
            second_time = TRUE;
          }
          while(result != 3);

          if(action == 'r')
          {
            if(!was_generated)
            {
              generateMap(Main_Game,getcury(Windows.Board_Window),getcurx(Windows.Board_Window));
              was_generated = TRUE;
            }
            setRevealState(Main_Game,row,col,1);
            if(getMineState(Main_Game,row,col))
            {
              loop = FALSE;
              End_Game(Main_Game,Windows,FALSE);
            }
          }
          else if(was_generated)
            setFlagState(Main_Game,row,col,1-getFlagState(Main_Game,row,col));


        }
    }
    Refresh(Main_Game,Windows,was_generated);
    if(calcWinState(Main_Game))
    {
      loop = FALSE;
      End_Game(Main_Game,Windows,TRUE);
    }
    if(!loop)
     break;
  }
}

void Play(Game* Main_Game)
{
  Game_Windows Windows = Create_Game_Window(Main_Game);
  /*Properties.Game_Board = generateBoard(Properties.rows,Properties.cols,Properties.mines);*/
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
