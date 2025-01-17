#include "ui_form.h"

UI_Form* Create_Form(char** Field_Descriptions, Input_Type Approved_Chars, char* Form_Title, size_t descriptions_length, int title_attrs)
{
  /* space for field descs*/
  UI_Form* out = malloc(sizeof(UI_Form));
  size_t index = 0;
  int x,y;
  int label_margin = 0;
  out->Field_Descriptions = Field_Descriptions;
  out->Form_Title = Form_Title;
  out->Approved_Chars = Approved_Chars;
  out->descriptions_length = descriptions_length;
  out->Form_Fields = (FIELD**)calloc(descriptions_length+1, sizeof(FIELD*));
  label_margin = 2 + Get_Longest_String_Length(out->Field_Descriptions, out->descriptions_length)+1;
  for(index = 0; index <  out->descriptions_length; ++index)
  {
    if(!out->Form_Fields)
      break;
    out->Form_Fields[index] = new_field(1,10,index*2+2, label_margin + 2,0,0);
    set_field_fore(out->Form_Fields[index], COLOR_PAIR(HIGHLITED_TEXT_COLOR) | A_BOLD);
    set_field_back(out->Form_Fields[index], COLOR_PAIR(ENTERED_TEXT_COLOR) | A_BOLD);
  }
  out->Form_Fields[descriptions_length] = NULL;
  out->Form = new_form(out->Form_Fields);
  scale_form(out->Form, &x, &y);
  out->window_cols = x;
  out->window_cols = y;
  out->window_cols += strlen(Form_Title) + 2 + 5;
  out->window_rows = descriptions_length*2+5;
  out->Form_Window = newwin(out->window_rows,out->window_cols,0,0);
  Move_Window_To_Center(out->Form_Window);
  set_form_win(out->Form, out->Form_Window);
  set_form_sub(out->Form, derwin(out->Form_Window,out->window_rows-4,out->window_cols-label_margin-1,2,label_margin));
  int title_pos = (getmaxx(out->Form_Window)-strlen(out->Form_Title))/2;
  wattron(out->Form_Window,title_attrs);
  mvwprintw(out->Form_Window,1,title_pos,"%s",out->Form_Title);
  wattroff(out->Form_Window,title_attrs);
  /* send help please */
  for(index = 0; index <  out->descriptions_length; ++index)
    mvwprintw(out->Form_Window,index*2+4,2,"%s",out->Field_Descriptions[index]);
  return out;
}

void Display_Form(UI_Form* Form)
{
  keypad(Form->Form_Window, TRUE);
  box(Form->Form_Window,0,0);
  post_form(Form->Form);
  Print_Horizontal_Bar_In_Window(Form->Form_Window,2);
  curs_set(TRUE);
  form_driver(Form->Form,REQ_FIRST_FIELD);
  form_driver(Form->Form,REQ_BEG_FIELD);
}

char** Create_Ouput_Data(UI_Form* Form)
{
  char** out;
  size_t index = Form->descriptions_length;
  out = malloc(sizeof(char*)*Form->descriptions_length);
  while(index --> 0)
    out[index] = field_buffer(Form->Form_Fields[index],0);
  return out;
}

char** Run_Form(UI_Form* Form)
{
  int ch = -1;
  while((ch = wgetch(Form->Form_Window)) != (ESCAPE))
	{
    switch(ch)
		{
      case 10: /* new line */
          if(field_index(current_field(Form->Form)) == (Form->descriptions_length-1))
            return Create_Ouput_Data(Form);
      case KEY_DOWN:
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
      case 27: /* ESC key */
        return NULL;
        break;
      case KEY_BACKSPACE:
        form_driver(Form->Form, REQ_DEL_PREV);
			default:
				/* If this is a normal character, it gets */
				/* Printed				  */
        if(Is_Character_Approved(Form,ch))
          form_driver(Form->Form, ch);
				break;
		}
	}
  return NULL;
}

bool Is_Character_Approved(UI_Form* Form, int ch)
{
  switch(Form->Approved_Chars)
  {
    case INPUT_NUM:
      return isdigit(ch);
    case INPUT_ALPHANUM:
      return isalnum(ch) || ch == ' ';
    default:
      return TRUE;
  }
}

void Destroy_Form(UI_Form* Form)
{
  size_t index = Form->descriptions_length;
  curs_set(FALSE);
  unpost_form(Form->Form);
  free_form(Form->Form);
  while(index --> Form->descriptions_length)
    free_field(Form->Form_Fields[index]);
  Clear_Window(Form->Form_Window);
  free(Form);
}
