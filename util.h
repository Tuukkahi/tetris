#ifndef UTIL_H
#define UTIL_H

#include <ncurses.h>
#include "game.h"

void next_tetromino(tetris_game_t *g);

void init_tetris(tetris_game_t *g);

void draw_instructions(WINDOW *w);

void draw_stats(WINDOW *w, tetris_game_t *g);

#endif
