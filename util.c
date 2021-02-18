/***************************************
 * some util functions for game.c file,*
 * initialisations and printing of     *
 * info and stats windows              *
 ***************************************/
#include <ncurses.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

#include "game.h"

void next_tetromino(tetris_game_t *g) {
    g->current = g->next;
    g->current.j = 8;
    g->next.type = rand() % 7;
    g->next.rotation = 0;
    g->next.i = 0;
    g->next.j = 0;
}

void init_tetris(tetris_game_t *g) {
    g->width = GAME_WIDTH;
    g->height = GAME_HEIGHT;
    g->next.type = rand() % 7;
    g->next.rotation = 0;
    g->next.i = 2;
    g->next.j = 8;
    next_tetromino(g);
    g->level = 0;
    g->score = 0;
    g->cleared = 0;
    for (uint8_t i = 0; i < GAME_HEIGHT; ++i) {
        for (uint8_t j = 0; j < GAME_WIDTH; ++j) {
            g->board[j + i * GAME_WIDTH] = 0;
        }
    }
    g->game_over = 0;
}

void draw_instructions(WINDOW *w) {
    int x = 2;
    int y = 2;

    mvwprintw(w, y, x, "h: left");
    y++;
    mvwprintw(w, y, x, "j: down");
    y++;
    mvwprintw(w, y, x, "k: rotate");
    y++;
    mvwprintw(w, y, x, "l: right");
    y++;
    mvwprintw(w, y, x, "space: drop");
    y++;
    y++;
    mvwprintw(w, y, x, "p: pause/continue");
    y++;
    mvwprintw(w, y, x, "q: quit");
    wrefresh(w);
}

void draw_stats(WINDOW *w, tetris_game_t *g) {
    int x = 2;
    int y = 4;
    mvwprintw(w, y, x, "score: %u", g->score);
    y += 2;
    mvwprintw(w, y, x, "level: %lu", g->level);
    wrefresh(w);
}
