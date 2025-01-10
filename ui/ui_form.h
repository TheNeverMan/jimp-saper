#pragma once
#include <curses.h>
#include <form.h>
#include <string.h>
#include <stdlib.h>

#include "ui_misc.h"
#include "colors.h"

typedef struct
{
  char** Field_Descriptions;
  FIELDTYPE** Field_Types;
  char* Form_Title;
  size_t descriptions_length;
  size_t window_cols;
  size_t window_rows;
  FIELD** Form_Fields;
  WINDOW* Form_Window;
  FORM* Form;
} UI_Form;

UI_Form* Create_Form(char** Field_Descriptions, FIELDTYPE** Field_Types, char* Form_Title, size_t descriptions_length, size_t window_cols, size_t window_rows);
char** Run_Form(UI_Form* Form);
void Destroy_Form(UI_Form* Form);
void Display_Form(UI_Form* Form);
