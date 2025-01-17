#include "ui_menu.h"

UI_Menu* Create_Menu(char** Menu_Options, char** Menu_Descriptions, char* Menu_Title, size_t options_length, size_t window_cols, size_t window_rows)
{
  UI_Menu* out = malloc(sizeof(UI_Menu));
  size_t index = 0;
  out->Menu_Options = Menu_Options;
  out->Menu_Descriptions = Menu_Descriptions;
  out->Menu_Title = Menu_Title;
  out->window_cols = window_cols;
  out->window_rows = options_length + 5;
  out->options_length = options_length;
  out->Menu_Items = (ITEM**)calloc(options_length+1, sizeof(ITEM*));
  out->Menu_Window = Create_Window_In_The_Middle(out->window_rows,out->window_cols);

  for(index = 0; index <  out->options_length; ++index)
    out->Menu_Items[index] = new_item(out->Menu_Options[index],out->Menu_Descriptions[index]);
  out->Menu_Items[out->options_length] = (ITEM *)NULL;
  return out;
}

void Display_Menu(UI_Menu* out)
{
  out->Menu = new_menu(out->Menu_Items);
  keypad(out->Menu_Window, TRUE);
  set_menu_win(out->Menu, out->Menu_Window);
  set_menu_sub(out->Menu, derwin(out->Menu_Window,out->window_rows-4,out->window_cols-2,3,1));
  set_menu_mark(out->Menu, " -> ");
  set_menu_fore(out->Menu, COLOR_PAIR(SELECTED_TEXT_COLOR) | A_BOLD);
  set_menu_back(out->Menu, COLOR_PAIR(SELECTABLE_TEXT_COLOR) | A_DIM);
  set_menu_grey(out->Menu, COLOR_PAIR(DISABLED_TEXT_COLOR) | A_BOLD | A_UNDERLINE);
  box(out->Menu_Window,0,0);
  int title_pos = (getmaxx(out->Menu_Window)-strlen(out->Menu_Title))/2;
  wattron(out->Menu_Window,STANDARD_TEXT_COLOR | A_BOLD);
  mvwprintw(out->Menu_Window,1,title_pos,"%s",out->Menu_Title);
  wattroff(out->Menu_Window,STANDARD_TEXT_COLOR | A_BOLD);
  Print_Horizontal_Bar_In_Window(out->Menu_Window,2);
  refresh();
  post_menu(out->Menu);
  wrefresh(out->Menu_Window);
}

void Destroy_Menu(UI_Menu* Menu)
{
  size_t index = Menu->options_length;
  unpost_menu(Menu->Menu);
  free_menu(Menu->Menu);
  while(index --> Menu->options_length)
    free_item(Menu->Menu_Items[index]);
  Clear_Window(Menu->Menu_Window);
  free(Menu);
}

size_t Run_Menu(UI_Menu* Menu)
{
  int c = -1;
  while((c = wgetch(Menu->Menu_Window)) != ESCAPE)
  {
    switch(c)
    {
      case KEY_DOWN:
        menu_driver(Menu->Menu, REQ_DOWN_ITEM);
        break;
      case KEY_UP:
        menu_driver(Menu->Menu, REQ_UP_ITEM);
        break;
      case ENTER:
        return item_index(current_item(Menu->Menu));
    }
    wrefresh(Menu->Menu_Window);
  }
  return c;
}
