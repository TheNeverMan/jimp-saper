#include "ui.h"

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
  while(index --> 0)
    item_opts_off(Highscore_Menu->Menu_Items[index],O_SELECTABLE);
  Display_Menu(Highscore_Menu);
  Run_Menu(Highscore_Menu);
  Destroy_Menu(Highscore_Menu);
}

Map_Properties Show_Custom_Size_Dialog()
{
  char* Field_Descriptions[] = {
    "Rows: ",
    "Columns: ",
    "Mines: ",
  /*  (char*)NULL*/
  };
  char Form_Title[] = "Enter Game Properties (Space accepts, ESC goes back to main menu)";
  UI_Form* Custom_Size_Form = Create_Form(Field_Descriptions,Form_Title,ARRAY_SIZE(Field_Descriptions),99,99);
  char** Menu_Out = NULL;
  Map_Properties out = {0,0,0};
  Display_Form(Custom_Size_Form);
  Menu_Out = Run_Form(Custom_Size_Form);
  Destroy_Form(Custom_Size_Form);
  return out;
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
      Created_Map_Properties = Show_Custom_Size_Dialog();
      break;
    default:
      /* exit */
      break;
  }
}

void Show_Main_Menu()
{
  char* Menu_Options[] = {
    "New Game",
    "Highscores",
    "Exit",
    "test",
    (char*)NULL
  };
  char* Menu_Descriptions[] = {
    " - Start new game",
    " - Show top 5 scores",
    " - Leave program :(",
    " - test test",
    (char*)NULL
  };
  char Menu_Title[] = "Minesweeper - Leopold Kucinski & Kajetan Wojcik";
  bool loop = TRUE;
  Init_UI();
  while(loop)
  {
    UI_Menu* Main_Menu = Create_Menu(Menu_Options,Menu_Descriptions,Menu_Title,ARRAY_SIZE(Menu_Options),60,10);
    size_t selected_option = 0;
    Display_Menu(Main_Menu);
    selected_option = Run_Menu(Main_Menu);
    Destroy_Menu(Main_Menu);
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
