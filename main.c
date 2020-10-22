#include "main.h"
#include "game.h"
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <ncurses.h>

/*******************************************
 * main menu logic and calling of the game *
 * function happens here, game itself      *
 * is in game.c file                       *
 ******************************************/

int startx = 0;
int starty = 0;

const char *choices[] = {
    "Play",
    "Info",
    "Exit",
};

const uint8_t n_choices = sizeof(choices) / sizeof(char*);

// main menu window
static void print_menu(WINDOW *w, int highlight)
{
    uint8_t x, y;
    x = 1;
    y = 0;
    mvwprintw(w, y, x, "Welcome to Tetris!");
    ++y;
    mvwprintw(w, y, x, "Press k and j to move up and down,\n enter to confirm");
    y += 5;
    for (uint8_t i = 0; i < n_choices; ++i)
    {
        if (highlight == i + 1)
        {
            wattron(w, A_REVERSE);
            mvwprintw(w, y, x, "%s", choices[i]);
            wattroff(w, A_REVERSE);
        }
        else
            mvwprintw(w, y, x, "%s", choices[i]);
        ++y;
    }
    wrefresh(w);
}

// info window
static void info()
{
    WINDOW *box_win = newwin(HEIGHT + 2, WIDTH + 20 + 2, starty, startx);
    WINDOW *info_win = newwin(HEIGHT, WIDTH + 20, starty + 1, startx + 1);
    box(box_win, 0, 0);

    uint8_t x, y;
    x = 1;
    y = 0;
    mvwprintw(info_win, y, x, "This is a tetris game written in C using ncurses library\n for the 'GUI-like' interface.");
    y+=3;
    mvwprintw(info_win, y, x, "The controls in the game are h, j, k, l, spacebar\n for moving left, down, rotate, right, and drop,\n respectively.");
    y+=3;;
    mvwprintw(info_win, y, x, "Pressing p pauses the game, and q quits it.");
    y+=2;
    mvwprintw(info_win, y, x, "You get points for every cleared line and level is\n increased for every five cleared row which increases\n gravity.");
    y+=4;
    mvwprintw(info_win, y, x, "The source code for this game can be found from\n github.com/tuukkahi/tetris");
    y+=3;
    mvwprintw(info_win, y, x, "Have fun playing!");
    y+=2;
    mvwprintw(info_win, y, x, "Press q to get back to the main menu.");
    wrefresh(box_win);
    wrefresh(info_win);
    while(wgetch(info_win) != 'q') continue;

    erase();
    delwin(box_win);
    delwin(info_win);
    refresh();
}


int main() {
    uint8_t highlight = 1;
    uint8_t choice = 0;
    uint8_t c;
    initscr();
    clear();
    noecho();
    cbreak();
    curs_set(0);
    startx = (2*GAME_WIDTH + 10 - WIDTH) / 2;
    starty = (GAME_HEIGHT -  HEIGHT) / 2;
    refresh();
    WINDOW *box_win = newwin(HEIGHT + 2, WIDTH + 2, starty, startx);
    WINDOW *menu_win = newwin(HEIGHT, WIDTH, starty + 1, startx + 1);

    tetris_game_t *tetris_game = NULL;
    while(1)
    {

        box(box_win, 0, 0);
        wrefresh(box_win);
        print_menu(menu_win, highlight);
        while(1)
        {
            c = wgetch(menu_win);
            switch (c)
            {
                case 'k':
                    if (highlight != 1)
                        --highlight;
                    break;
                case 'j':
                    if (highlight != n_choices)
                        ++highlight;
                    break;
                case 10:
                    choice = highlight;
                    break;
                default:
                    break;
            }
            print_menu(menu_win, highlight);
            if (choice != 0)
                break;
        }
        if (choice == 1)  // play
        {
            erase();
            refresh();
            game(tetris_game);
            choice = 0;
            continue;
        }
        if (choice == 2)  // info
        {
            info();
            choice = 0;
            continue;
        }
        if (choice == 3)  // exit
        {
            break;
        }
    }

    erase();
    delwin(menu_win);
    delwin(box_win);
    clrtoeol();
    endwin();
    free(tetris_game);
    return 0;
}

