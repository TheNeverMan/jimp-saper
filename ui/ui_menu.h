#pragma once
#include <stdlib.h>
#include <curses.h>
#include <menu.h>

#include "colors.h"
#include "ui_misc.h"

typedef struct
{
  char** Menu_Options;
  char** Menu_Descriptions;
  char* Menu_Title;
  size_t options_length;
  size_t window_cols;
  size_t window_rows;
  ITEM** Menu_Items;
  WINDOW* Menu_Window;
  MENU* Menu;
} UI_Menu;

UI_Menu* Create_Menu(char** Menu_Options, char** Menu_Descriptions, char* Menu_Title, size_t options_length, size_t window_cols, size_t window_rows);
size_t Run_Menu(UI_Menu* Menu);
void Destroy_Menu(UI_Menu* Menu);
void Display_Menu(UI_Menu* out);
