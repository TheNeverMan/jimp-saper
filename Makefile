CC	  = gcc
FLAGS = -Wall -pedantic -ansi
TEST_FLAGS = -ggdb
FILES = backend/board.c backend/game.c backend/input.c backend/score.c
LIBS	= -lcurses -lmenu -lform
all: $(FILES) main.c
	$(CC) $(FLAGS) $(TEST_FLAGS) -o saper main.c $(FILES) $(LIBS)
test: $(FILES) test/test.c
	$(CC) $(FLAGS) $(TEST_FLAGS) -o saper-test test/test.c $(FILES) $(LIBS)
clean:
	rm -f saper-test
	rm -f saper
