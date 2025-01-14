#include "ui.h"

const char* logo[] = {
  "        __  __ _                                                   ",
  "__/\\__ |  \\/  (_)_ __   ___  _____      _____  ___ _ __   ___ _ __ ",
  "\\    / | |\\/| | | '_ \\ / _ \\/ __\\ \\ /\\ / / _ \\/ _ \\ '_ \\ / _ \\ '__|",
  "/_  _\\ | |  | | | | | |  __/\\__  \\ V  V /  __/  __/ |_) |  __/ |   ",
  "  \\/   |_|  |_|_|_| |_|\\___||___/ \\_/\\_/ \\___|\\___| .__/ \\___|_|   ",
  "                                                  |_|            ",
  (char*)NULL
};

const int HIDDEN_TILE = A_DIM | COLOR_PAIR(HIDDEN_TILE_COLOR);
const int EMPTY_TILE = A_DIM | COLOR_PAIR(EMPTY_TILE_COLOR);
const int TILE_1 = COLOR_PAIR(TILE_1_COLOR);
const int TILE_2 = COLOR_PAIR(TILE_2_COLOR);
const int TILE_3 = COLOR_PAIR(TILE_3_COLOR);
const int TILE_4 = A_DIM | COLOR_PAIR(TILE_4_COLOR);
const int TILE_OTHER = COLOR_PAIR(TILE_OTHER_COLOR);
const int FLAG = A_BOLD | COLOR_PAIR(FLAG_COLOR);
const int MINE = A_BOLD | COLOR_PAIR(MINE_COLOR);
void Init_UI()
{
  initscr();
  raw();
  keypad(stdscr,TRUE);
  noecho();
  fflush(stdin);
  start_color();
  init_pair(STANDARD_TEXT_COLOR, COLOR_WHITE, COLOR_BLACK);
  init_pair(SELECTED_TEXT_COLOR, COLOR_RED, COLOR_BLACK);
  init_pair(SELECTABLE_TEXT_COLOR, COLOR_YELLOW, COLOR_BLACK);
  init_pair(DISABLED_TEXT_COLOR, COLOR_YELLOW, COLOR_BLACK);
  init_pair(INPUT_TEXT_COLOR, COLOR_WHITE, COLOR_BLUE);
  init_pair(ENTERED_TEXT_COLOR, COLOR_WHITE, COLOR_BLUE);
  init_pair(HIGHLITED_TEXT_COLOR, COLOR_WHITE, COLOR_BLUE);
  init_pair(HIDDEN_TILE_COLOR, COLOR_BLACK, COLOR_WHITE);
  init_pair(EMPTY_TILE_COLOR, COLOR_BLUE, COLOR_BLACK);
  init_pair(TILE_1_COLOR, COLOR_BLUE, COLOR_BLACK);
  init_pair(TILE_2_COLOR, COLOR_GREEN, COLOR_BLACK);
  init_pair(TILE_3_COLOR, COLOR_RED, COLOR_BLACK);
  init_pair(TILE_3_COLOR, COLOR_RED, COLOR_BLACK);
  init_pair(TILE_4_COLOR, COLOR_BLUE, COLOR_BLACK);
  init_pair(TILE_OTHER_COLOR, COLOR_MAGENTA, COLOR_BLACK);
  init_pair(FLAG_COLOR, COLOR_MAGENTA, COLOR_BLACK);
  init_pair(MINE_COLOR, COLOR_BLACK, COLOR_RED);
  attron(COLOR_PAIR(STANDARD_TEXT_COLOR));
  curs_set(FALSE);
}

void Uninit_UI()
{
  endwin();
  curs_set(TRUE);

}

void Show_Highscores()
{
  char* Menu_Options[] = {
    "9999",
    "5000",
    "4500",
    "3500",
    "2000",
    "Back",
    (char*)NULL
  };
  char* Menu_Descriptions[] = {
    " - Lk",
    " - Lk",
    " - Lk",
    " - LK",
    " - LK",
    " ",
    (char*)NULL
  };
  char Menu_Title[] = "Highscores";
  UI_Menu* Highscore_Menu = Create_Menu(Menu_Options,Menu_Descriptions,Menu_Title,ARRAY_SIZE(Menu_Options),60,12);
  /* make highscores unselectable */
  int index = ARRAY_SIZE(Menu_Options) - 2;
  Print_Help_Bar("Use Cursor Keys to move up and down and Enter to confirm selection");
  while(index --> 0)
    item_opts_off(Highscore_Menu->Menu_Items[index],O_SELECTABLE);
  Display_Menu(Highscore_Menu);
  Run_Menu(Highscore_Menu);
  Destroy_Menu(Highscore_Menu);
}

Map_Properties Convert_Char_To_Map_Properties(char** tab)
{
  Map_Properties out = {0,0,0};
  if(!tab)
    return out;
  out.rows = atoi(tab[0]);
  out.cols = atoi(tab[1]);
  out.mines = atoi(tab[2]);
  free(tab);
  return out;
}

bool Validate_Map_Properties(Map_Properties Properties)
{
  size_t window_y, window_x;
  getmaxyx(stdscr,window_y,window_x);
  window_y -= 4;
  window_x -= 2;
  if((Properties.rows * Properties.cols) < Properties.mines)
    return FALSE;
  if(Properties.rows < 5 || Properties.cols < 5 || Properties.mines < 1)
    return FALSE;
  if(Properties.rows > window_y || Properties.cols > window_x || Properties.mines > 999)
    return FALSE;
  return TRUE;
}

Map_Properties Show_Custom_Size_Dialog(bool second_time)
{
  char* Field_Descriptions[] = {
    "Rows: ",
    "Columns: ",
    "Mines: ",
    "Confirm",
  };
  char* Form_Title;
  char** Menu_Out = NULL;
  UI_Form* Custom_Size_Form;
  int title_attrs = A_BOLD;
  if(!second_time)
  {
    Form_Title = "Enter Game Properties";
    title_attrs = title_attrs | COLOR_PAIR(STANDARD_TEXT_COLOR);
  }
  else
  {
    Form_Title = "Invalid Values!";
    title_attrs = title_attrs | COLOR_PAIR(SELECTED_TEXT_COLOR);
  }
  Print_Help_Bar("Use Cursor Keys to move up and down, Enter confirms input, press Enter in Confirm field to start game");
  Custom_Size_Form = Create_Form(Field_Descriptions,INPUT_NUM,Form_Title,ARRAY_SIZE(Field_Descriptions),title_attrs);
  Display_Form(Custom_Size_Form);
  Menu_Out = Run_Form(Custom_Size_Form);
  Destroy_Form(Custom_Size_Form);
  return  Convert_Char_To_Map_Properties(Menu_Out);
}



void Show_Game_Creation_Dialog()
{
  char* Menu_Options[] = {
    "Easy Difficulty",
    "Medium Difficulty",
    "Hard Difficulty",
    "Custom",
    "Back",
    (char*)NULL
  };
  char* Menu_Descriptions[] = {
    " - 9x9 10 mines",
    " - 16x16 40 mines",
    " - 16x30 99 mines",
    " - Set your own size",
    " ",
    (char*)NULL
  };
  char Menu_Title[] = "Select Difficulty";
  UI_Menu* Game_Creation_Menu = Create_Menu(Menu_Options,Menu_Descriptions,Menu_Title,ARRAY_SIZE(Menu_Options),60,12);
  Map_Properties Created_Map_Properties;
  int output = 0;
  Created_Map_Properties.points = 0;
  Print_Help_Bar("Use Cursor Keys to move up and down and Enter to confirm selection");
  Display_Menu(Game_Creation_Menu);
  output = Run_Menu(Game_Creation_Menu);
  Destroy_Menu(Game_Creation_Menu);
  switch(output)
  {
    case 0:
      Created_Map_Properties.rows = 9;
      Created_Map_Properties.cols = 9;
      Created_Map_Properties.mines = 10;
      break;
    case 1:
      Created_Map_Properties.rows = 16;
      Created_Map_Properties.cols = 16;
      Created_Map_Properties.mines = 40;
      break;
    case 2:
      Created_Map_Properties.rows = 16;
      Created_Map_Properties.cols = 30;
      Created_Map_Properties.mines = 99;
      break;
    case 3:
      {
        bool second_time = FALSE;
        do
        {
          Created_Map_Properties = Show_Custom_Size_Dialog(second_time);
          second_time = TRUE;
        }
        while(!Validate_Map_Properties(Created_Map_Properties));
      }
      break;
    default:
      return;
      break;
  }
  Show_Main_Game(Created_Map_Properties);
}

void Show_Main_Menu()
{
  char* Menu_Options[] = {
    "New Game",
    "Highscores",
    "Exit",
    (char*)NULL
  };
  char* Menu_Descriptions[] = {
    " - Start new game",
    " - Show top 5 scores",
    " - Leave program :(",
    (char*)NULL
  };
  char Menu_Title[] = "Minesweeper - Leopold Kucinski & Kajetan Wojcik";
  bool loop = TRUE;
  Init_UI();
  Print_Help_Bar("Use Cursor Keys to move up and down and Enter to confirm selection");
  while(loop)
  {
    UI_Menu* Main_Menu = Create_Menu(Menu_Options,Menu_Descriptions,Menu_Title,ARRAY_SIZE(Menu_Options),60,10);
    size_t selected_option = 0;
    Display_Menu(Main_Menu);
    Display_Logo(TRUE);
    refresh();
    selected_option = Run_Menu(Main_Menu);
    Destroy_Menu(Main_Menu);
    Display_Logo(FALSE);
    switch(selected_option)
    {
      /* New Game */
      case 0:
        Show_Game_Creation_Dialog();
        break;
      /* Highscores Table */
      case 1:
        Show_Highscores();
        break;
      /* Exit */
      case 2:
        loop = FALSE;
        break;
      default:
        fprintf(stderr, "[E] wrong menu optionen");
        loop = FALSE;
        break;
    }

  }
  Uninit_UI();
}
