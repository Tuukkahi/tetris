#define _POSIX_C_SOURCE 199309L
#include <stdlib.h>
#include <stdint.h>
#include <ncurses.h>
#include <unistd.h>
#include <time.h>
#include <math.h>

#include "game.h"
#include "tetrominos.h"
#include "util.h"

/**********************************************
 * main game logic is found from this file,   *
 * some functions are abstracted to util.c,   *
 * and tetromino data is written out in       *
 * tetrominos.c file                          *
 *********************************************/

// check if position (j,i) has a tetromino
static uint8_t draw(uint8_t j, uint8_t i, tetromino_t *t)
{
    int8_t current_termino_i = t->i;
    int8_t current_termino_j = t->j;
    uint8_t rot = t->rotation;
    for (uint8_t c = 0; c < 16; ++c) {
        if (tetrominos[t->type][rot][c][0] + current_termino_j == j) {
            if (tetrominos[t->type][rot][c][1] + current_termino_i == i) {
                return 1;
            }
        }
    }
    return 0;
}

// draw game to it's window according to the current state of affairs
static void draw_game(WINDOW *w, tetris_game_t *g)
{
    for (uint8_t i = 0; i < GAME_HEIGHT; ++i)
    {
        for (uint8_t j = 0; j < GAME_WIDTH; ++j)
        {
            if (draw(j, i, &g->current) || g->board[j + i * g->width])
            {
                wattron(w, A_REVERSE);
                waddch(w, 32);
                waddch(w, 32);
                wattroff(w, A_REVERSE);
            }
            else
            {
                waddch(w, 32);
                waddch(w, 32);
            }
        }
        wmove(w, i + 1, 1);
    }
    wrefresh(w);
}

// check for collisions for the current tetromino rotated and moved by delta_j, delta_i, and r
static uint8_t collision(tetris_game_t *g, int8_t delta_j, int8_t delta_i, int8_t r)
{
    uint8_t t = g->current.type;
    uint8_t rotation = (g->current.rotation + r) % 4;
    for (uint8_t i = 0; i < 16; ++i)
    {
        int8_t current_j = tetrominos[t][rotation][i][0] + g->current.j + delta_j;
        int8_t current_i = tetrominos[t][rotation][i][1] + g->current.i + delta_i;
        if (current_j < 0 || current_j >= g->width || current_i < 0 || current_i >= g->height || g->board[current_j + current_i * g->width]) {
            return 1;
        }
    }
    return 0;
}

// rotate tetromino according to the wall kick data in tetrominos.c
static void rotate(tetris_game_t *g)
{
    for (uint8_t k = 0; k < 4; ++k)
    {
        int8_t kick_j = g->current.type == 0 
            ? kick_I_clockwise[g->current.rotation][k][0]
            : kick_clockwise[g->current.rotation][k][0];
        int8_t kick_i = g->current.type == 0
            ? kick_I_clockwise[g->current.rotation][k][1]
            : kick_clockwise[g->current.rotation][k][1];
        if (!collision(g, kick_j, kick_i, 1))
        {
            g->current.j += kick_j;
            g->current.i += kick_i;
            g->current.rotation = (g->current.rotation + 1) % 4;
            return;
        }
    }
    return;
}

// store finished tetromino in the board member of game struct
static void populate_new_tetromino(tetris_game_t *g)
{
    uint8_t t = g->current.type;
    for (uint8_t i = 0; i < 16; ++i)
    {
        uint8_t current_j = tetrominos[t][g->current.rotation][i][0] + g->current.j;
        uint8_t current_i = tetrominos[t][g->current.rotation][i][1] + g->current.i;
        g->board[current_j + current_i * g->width] = 1;
    }
}

// draw next tetromino to it's window
static void draw_next(tetromino_t *t, WINDOW *w)
{
    werase(w);
    wrefresh(w);
    for (uint8_t i = 0; i < 12; ++i)
    {
        for (uint8_t j = 0; j < 12; ++j)
        {
            if ((i >= 4 && j >= 3 && draw(j - 3, i - 4, t)))
            {
                wattron(w, A_REVERSE);
                waddch(w, 32);
                waddch(w, 32);
                wattroff(w, A_REVERSE);
            }
            else 
            {
                waddch(w, 32);
                waddch(w, 32);
            }
        }
    }
    wrefresh(w);
    return;
}

static uint8_t tick(tetris_game_t *g)
{
    struct timespec now;
    clock_gettime(CLOCK_REALTIME, &now);
    double since_previous = (now.tv_sec - g->previous_tick.tv_sec) 
        + (now.tv_nsec - g->previous_tick.tv_nsec) / (double) 1000000000L;

    // if enough time has passed since last tick, drop current tetromino or initialise new one
    if (since_previous > g->tick_length) {
        g->previous_tick = now;
        if (!collision(g, 0, +2, 0))
        {
            g->current.i += 2;
        }
        else
        {
            populate_new_tetromino(g); // add finished tetromino to the game board
            next_tetromino(g);
            // if new tetromino can't move return 1 to indicate game over
            if (collision(g, 0, 0, 0)) 
                return 1;
        }
    }
    // if game not over return 0
    return 0;
}

static void check_points(tetris_game_t *g)
{
    // check if any rows are full, and increase cleared accordingly
    uint8_t cleared = 0;
    for (uint8_t i = 0; i < g->height; ++i)
    {
        uint8_t count = 0;
        for (uint8_t j = 0; j < g->width; ++j)
        {
            if (g->board[j + i * g->width])
                count++;
        }
        if (count == g->width - 1)
        {
            cleared++;
            for (uint8_t i1 = i; i1 > 0; --i1)
            {
                for (uint8_t j = 0; j < g->width; ++j)
                {
                    g->board[j + i1 * g->width] = g->board[j + (i1-1) * g->width];
                }
            }
        }
    }

    cleared /= 2;
    g->cleared += cleared;
    if (cleared == 1)
        g->score += 40*(g->level + 1);
    if (cleared == 2)
        g->score += 100*(g->level + 1);
    if (cleared == 3)
        g->score += 300*(g->level + 1);
    if (cleared >= 4)
        g->score += 1200*(g->level + 1);

    // check if level is increased, i.e. 5 cleared rows
    if (g->cleared >= (g->level+1)*5) 
    {
        g->level += 1;
        // the formula to compute dropping speed of tetromino from new level
        g->tick_length = pow(0.8 - (g->level - 1) *0.007, ((double)g->level - 1));
    }
}

void game(void)
{
    // window for the game itself
    WINDOW *game_box = newwin(GAME_HEIGHT+2, GAME_WIDTH*2+2, 0, 0);
    WINDOW *game_win = newwin(GAME_HEIGHT, GAME_WIDTH*2, 1, 1);

    // window for next tetromino
    WINDOW *next_box = newwin(12+2, 24+4, 0, GAME_WIDTH*2+4+0);
    WINDOW *next_win = newwin(12, 24, 1, GAME_WIDTH*2+4+1);

    // window for points and level
    WINDOW *stats_box = newwin(12+2, 24+4, 12 + 2, GAME_WIDTH*2+4+0);
    WINDOW *stats_win = newwin(12, 24, 12 + 3, GAME_WIDTH*2+4+1);

    // window for instructions
    WINDOW *inst_box = newwin(12+2, 24+4, 24 + 4, GAME_WIDTH*2+4+0);
    WINDOW *inst_win = newwin(12, 24, 24 + 5, GAME_WIDTH*2+4+1);

    box(next_box, 0, 0);
    wrefresh(next_box);

    box(game_box, 0, 0);
    wrefresh(game_box);

    box(stats_box, 0, 0);
    wrefresh(stats_box);

    box(inst_box, 0, 0);
    wrefresh(inst_box);

    draw_instructions(inst_win);

    tetris_game_t *g = malloc(sizeof(tetris_game_t) + GAME_WIDTH * GAME_HEIGHT * sizeof(uint8_t) + 1);
    init_tetris(g);

    halfdelay(1);  // to wait for some time in wgetch to not run the while loop too fast

    uint8_t quit = 0;
    while(!quit)
    {
        draw_next(&g->next, next_win);
        draw_stats(stats_win, g);
        check_points(g);
        quit = tick(g);
        draw_game(game_win, g);

        uint8_t c = wgetch(game_win);

        switch (c) {
            case 'h':
                if(!collision(g, -2, 0, 0)) g->current.j -= 2;
                break;
            case 'j':
                if(!collision(g, 0, 2, 0)) g->current.i += 2;
                break;
            case 'k':
                rotate(g);
                break;
            case 'l':
                if(!collision(g, 2, 0, 0)) g->current.j += 2;
                break;
            case 32:
                while(!collision(g, 0, 2, 0)) g->current.i += 2;
                break;
            case 'p':
                while(1)
                {
                    uint8_t p = wgetch(game_win);
                    if (p == 'q')
                    {
                        quit = 1;
                        break;
                    }
                    if (p == 'p') break;
                }
                break;
            case 'q':
                quit = 1;
            default:
                break;
        }
    }

    delwin(game_win);
    delwin(game_box);
    delwin(next_win);
    delwin(next_box);
    free(g);
    refresh();
}
