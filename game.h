#ifndef GAME_H
#define GAME_H

#include <stdint.h>
#include <time.h>
#include <ncurses.h>

#define GAME_WIDTH 21
#define GAME_HEIGHT 40

typedef struct {
    uint8_t type;
    uint8_t rotation;

    int8_t i;
    int8_t j;

} tetromino_t;

typedef struct {
    uint8_t width;
    uint8_t height;

    tetromino_t current;
    tetromino_t next;

    uint8_t level;
    uint16_t score;
    uint16_t cleared;
    struct timespec previous_tick;
    double tick_length;
    uint8_t board[1];

} tetris_game_t;

void game();

#endif
