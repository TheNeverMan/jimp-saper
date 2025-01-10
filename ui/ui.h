#pragma once
#include <curses.h>
#include <menu.h>
#include <stdlib.h>
#include <string.h>

#include "colors.h"
#include "ui_menu.h"

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))

typedef struct
{
  size_t rows;
  size_t cols;
  size_t mines;
} Map_Properties;

void Show_Main_Menu();
void Show_Highscores();
void Show_Game_Creation_Dialog();
Map_Properties Show_Custom_Size_Dialog();
