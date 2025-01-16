#pragma once
#include <stdlib.h>
#include <curses.h>

#include "ui_misc.h"
#include "colors.h"
#include "ui_form.h"
#include "../backend/interface.h"
#include "../backend/game.h"

typedef struct
{
  WINDOW* Main_Game_Window;
  WINDOW* Board_Window;
} Game_Windows;

void Show_Main_Game(Game* Main_Game);
void Destroy_Main_Game(Game_Windows Windows);
