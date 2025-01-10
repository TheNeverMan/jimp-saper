CC	  = gcc
FLAGS = -Wall -pedantic -ansi
FILES = ui/ui.c ui/ui_menu.c ui/ui_misc.c
LIBS	= -lcurses -lmenu
all: $(FILES) main.c
	$(CC) $(FLAGS) -o saper main.c $(FILES) $(LIBS)
test: $(FILES) test/test.c
	$(CC) $(FLAGS) -o saper-test test/test.c $(FILES) $(LIBS)
clean:
	rm -f saper-test
	rm -f saper
