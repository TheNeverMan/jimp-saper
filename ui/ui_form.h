#pragma once
#include <curses.h>
#include <form.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "ui_misc.h"
#include "colors.h"



typedef struct
{
  char** Field_Descriptions;
  char* Form_Title;
  size_t descriptions_length;
  size_t window_cols;
  size_t window_rows;
  FIELD** Form_Fields;
  WINDOW* Form_Window;
  FORM* Form;
  Input_Type Approved_Chars;
} UI_Form;

UI_Form* Create_Form(char** Field_Descriptions,Input_Type Approved_Chars, char* Form_Title, size_t descriptions_length);
char** Run_Form(UI_Form* Form);
void Destroy_Form(UI_Form* Form);
void Display_Form(UI_Form* Form);
bool Is_Character_Approved(UI_Form* Form, int ch);
