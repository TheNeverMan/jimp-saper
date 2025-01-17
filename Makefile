CC	  = gcc
FLAGS = -Wall -pedantic -std=c99
TEST_FLAGS = -ggdb
FILES = backend/board.c backend/game.c backend/input.c backend/score.c backend/interface.c ui/ui.c ui/ui_form.c ui/ui_menu.c ui/ui_misc.c ui/ui_game.c
LIBS	= -lcurses -lmenu -lform -lm
all: $(FILES) main.c
	$(CC) $(FLAGS) $(TEST_FLAGS) -o saper main.c $(FILES) $(LIBS)
test-saper: $(FILES) test/test.c
	$(CC) $(FLAGS) $(TEST_FLAGS) -o saper-test test/test.c $(FILES) $(LIBS)
clean:
	rm -f saper-test
	rm -f saper
