bin=tetris
CC=gcc
SRC_FILES=main.c game.c tetrominos.c util.c
CFLAGS=-pthread -lncurses -lm -Wall -Wextra -std=c11

tetris: $(SRC_FILES)
	$(CC) $(CFLAGS) $(SRC_FILES) -o $@

run: tetris 
	./$(bin)
