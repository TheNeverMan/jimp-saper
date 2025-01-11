#include "ui_form.h"

UI_Form* Create_Form(char** Field_Descriptions, char* Form_Title, size_t descriptions_length, size_t window_cols, size_t window_rows)
{

  /* space for field descs*/
  size_t window_cols_offset = 35;
  UI_Form* out = malloc(sizeof(UI_Form));
  size_t index = 0;
  int x,y;
  int label_margin = 0;
  out->Field_Descriptions = Field_Descriptions;
  out->Form_Title = Form_Title;
  out->window_cols = window_cols;
  out->window_rows = window_rows;
  out->descriptions_length = descriptions_length;
  out->Form_Fields = (FIELD**)calloc(descriptions_length+1, sizeof(FIELD*));
  label_margin = 2 + Get_Longest_String_Length(out->Field_Descriptions, out->descriptions_length);
  for(index = 0; index <  out->descriptions_length; ++index)
  {
    if(!out->Form_Fields)
      break;
    out->Form_Fields[index] = new_field(1,10,index*2+2,window_cols_offset,0,0);
    set_field_fore(out->Form_Fields[index], COLOR_PAIR(HIGHLITED_TEXT_COLOR) | A_BOLD);
    set_field_back(out->Form_Fields[index], COLOR_PAIR(ENTERED_TEXT_COLOR) | A_DIM);
  }
  out->Form_Fields[descriptions_length] = NULL;
  out->Form = new_form(out->Form_Fields);
  scale_form(out->Form, &x, &y);
  out->window_cols = x;
  out->window_cols = y;
  out->window_cols += window_cols_offset;
  out->window_rows = descriptions_length*2+5;
  out->Form_Window = newwin(out->window_rows,out->window_cols,0,0);
  mvwprintw(out->Form_Window,1,2,"%s",out->Form_Title);
  set_form_win(out->Form, out->Form_Window);
  /* send help please */
  set_form_sub(out->Form, derwin(out->Form_Window,out->window_rows-4,out->window_cols-label_margin-1,2,label_margin));
  for(index = 0; index <  out->descriptions_length; ++index)
    mvwprintw(out->Form_Window,index*2+4,2,"%s",out->Field_Descriptions[index]);
  keypad(out->Form_Window, TRUE);
  box(out->Form_Window,0,0);
  post_form(out->Form);
  wrefresh(out->Form_Window);
/*  Print_In_The_Middle(out->Form_Window,1,0,out->window_cols,out->Form_Title,STANDARD_TEXT_COLOR);*/
  /*wrefresh(out->Form_Window);*/
  return out;
}

void Display_Form(UI_Form* Form)
{
  Move_Window_To_Center(Form->Form_Window);
  refresh();
  curs_set(TRUE);
}

char** Run_Form(UI_Form* Form)
{
  int ch = -1;
  char** out = NULL;
  while((ch = wgetch(Form->Form_Window)) != (KEY_F(1))
	{	switch(ch)
		{	case KEY_DOWN:
				/* Go to next field */
        form_driver(Form->Form, REQ_NEXT_FIELD);
				/* Go to the end of the present buffer */
				/* Leaves nicely at the last character */
        form_driver(Form->Form, REQ_END_LINE);
				break;
			case KEY_UP:
				/* Go to previous field */
        form_driver(Form->Form, REQ_PREV_FIELD);
        form_driver(Form->Form, REQ_END_LINE);
				break;
      case KEY_ESCAPE:
        return NULL;
        break;
			default:
				/* If this is a normal character, it gets */
				/* Printed				  */
        form_driver(Form->Form, ch);
				break;
		}
	}
  return out;
}


void Destroy_Form(UI_Form* Form)
{
  curs_set(FALSE);
}
