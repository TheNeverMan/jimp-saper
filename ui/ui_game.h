#pragma once
#include <stdlib.h>
#include <curses.h>

#include "ui_misc.h"
#include "colors.h"
#include "ui_form.h"
#include "../backend/interface.h"

typedef struct
{
  WINDOW* Main_Game_Window;
  WINDOW* Board_Window;
} Game_Windows;

void Show_Main_Game(Map_Properties Properties);
void Destroy_Main_Game(Game_Windows Windows);
