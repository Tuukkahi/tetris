#include <stdint.h>

/*******************************************************
 *  Global declarations for tetromino coordinates and  *
 *  wall kick info for rotation functions              *
 * *****************************************************/

const uint8_t tetrominos[7][4][16][2] = {
    {// ***** I *****
     {
         {0, 2}, {1, 2}, {2, 2}, {3, 2}, {4, 2}, {5, 2}, {6, 2}, {7, 2}, {0, 3}, {1, 3}, {2, 3}, {3, 3}, {4, 3}, {5, 3}, {6, 3}, {7, 3}},
     {{4, 0}, {4, 1}, {4, 2}, {4, 3}, {4, 4}, {4, 5}, {4, 6}, {4, 7}, {5, 0}, {5, 1}, {5, 2}, {5, 3}, {5, 4}, {5, 5}, {5, 6}, {5, 7}},
     {{0, 4}, {1, 4}, {2, 4}, {3, 4}, {4, 4}, {5, 4}, {6, 4}, {7, 4}, {0, 5}, {1, 5}, {2, 5}, {3, 5}, {4, 5}, {5, 5}, {6, 5}, {7, 5}},
     {{2, 0}, {2, 1}, {2, 2}, {2, 3}, {2, 4}, {2, 5}, {2, 6}, {2, 7}, {3, 0}, {3, 1}, {3, 2}, {3, 3}, {3, 4}, {3, 5}, {3, 6}, {3, 7}}},
    {// ***** J *****
     {
         {0, 0},
         {1, 0},
         {0, 2},
         {1, 2},
         {2, 2},
         {3, 2},
         {4, 2},
         {5, 2},
         {0, 1},
         {1, 1},
         {0, 3},
         {1, 3},
         {2, 3},
         {3, 3},
         {4, 3},
         {5, 3},
     },
     {
         {2, 0},
         {3, 0},
         {4, 0},
         {5, 0},
         {2, 2},
         {3, 2},
         {2, 4},
         {3, 4},
         {2, 1},
         {3, 1},
         {4, 1},
         {5, 1},
         {2, 3},
         {3, 3},
         {2, 5},
         {3, 5},
     },
     {{0, 2}, {1, 2}, {2, 2}, {3, 2}, {4, 2}, {5, 2}, {4, 4}, {5, 4}, {0, 3}, {1, 3}, {2, 3}, {3, 3}, {4, 3}, {5, 3}, {4, 5}, {5, 5}},
     {{0, 4}, {1, 4}, {2, 4}, {3, 4}, {2, 2}, {3, 2}, {2, 0}, {3, 0}, {0, 5}, {1, 5}, {2, 5}, {3, 5}, {2, 3}, {3, 3}, {2, 1}, {3, 1}}},
    {// ***** L *****
     {
         {0, 2}, {1, 2}, {2, 2}, {3, 2}, {4, 2}, {5, 2}, {4, 0}, {5, 0}, {0, 3}, {1, 3}, {2, 3}, {3, 3}, {4, 3}, {5, 3}, {4, 1}, {5, 1}},
     {{2, 0}, {3, 0}, {2, 2}, {3, 2}, {2, 4}, {3, 4}, {4, 4}, {5, 4}, {2, 1}, {3, 1}, {2, 3}, {3, 3}, {2, 5}, {3, 5}, {4, 5}, {5, 5}},
     {{0, 2}, {1, 2}, {2, 2}, {3, 2}, {4, 2}, {5, 2}, {0, 4}, {1, 4}, {0, 3}, {1, 3}, {2, 3}, {3, 3}, {4, 3}, {5, 3}, {0, 5}, {1, 5}},
     {{0, 0}, {1, 0}, {2, 0}, {3, 0}, {2, 2}, {3, 2}, {2, 4}, {3, 4}, {0, 1}, {1, 1}, {2, 1}, {3, 1}, {2, 3}, {3, 3}, {2, 5}, {3, 5}}},
    {// ***** O *****
     {
         {2, 0},
         {3, 0},
         {4, 0},
         {5, 0},
         {2, 2},
         {3, 2},
         {4, 2},
         {5, 2},
         {2, 1},
         {3, 1},
         {4, 1},
         {5, 1},
         {2, 3},
         {3, 3},
         {4, 3},
         {5, 3},
     },
     {
         {2, 0},
         {3, 0},
         {4, 0},
         {5, 0},
         {2, 2},
         {3, 2},
         {4, 2},
         {5, 2},
         {2, 1},
         {3, 1},
         {4, 1},
         {5, 1},
         {2, 3},
         {3, 3},
         {4, 3},
         {5, 3},
     },
     {
         {2, 0},
         {3, 0},
         {4, 0},
         {5, 0},
         {2, 2},
         {3, 2},
         {4, 2},
         {5, 2},
         {2, 1},
         {3, 1},
         {4, 1},
         {5, 1},
         {2, 3},
         {3, 3},
         {4, 3},
         {5, 3},
     },
     {
         {2, 0},
         {3, 0},
         {4, 0},
         {5, 0},
         {2, 2},
         {3, 2},
         {4, 2},
         {5, 2},
         {2, 1},
         {3, 1},
         {4, 1},
         {5, 1},
         {2, 3},
         {3, 3},
         {4, 3},
         {5, 3},
     }},
    {
        // ***** S *****
        {
            {0, 2},
            {1, 2},
            {2, 2},
            {3, 2},
            {2, 0},
            {3, 0},
            {4, 0},
            {5, 0},
            {0, 3},
            {1, 3},
            {2, 3},
            {3, 3},
            {2, 1},
            {3, 1},
            {4, 1},
            {5, 1},
        },
        {
            {2, 0},
            {3, 0},
            {2, 2},
            {3, 2},
            {4, 2},
            {5, 2},
            {4, 4},
            {5, 4},
            {2, 1},
            {3, 1},
            {2, 3},
            {3, 3},
            {4, 3},
            {5, 3},
            {4, 5},
            {5, 5},
        },
        {
            {0, 4},
            {1, 4},
            {2, 4},
            {3, 4},
            {2, 2},
            {3, 2},
            {4, 2},
            {5, 2},
            {0, 5},
            {1, 5},
            {2, 5},
            {3, 5},
            {2, 3},
            {3, 3},
            {4, 3},
            {5, 3},
        },
        {
            {0, 0},
            {1, 0},
            {0, 2},
            {1, 2},
            {2, 2},
            {3, 2},
            {2, 4},
            {3, 4},
            {0, 1},
            {1, 1},
            {0, 3},
            {1, 3},
            {2, 3},
            {3, 3},
            {2, 5},
            {3, 5},
        },
    },
    {
        // ***** T *****
        {
            {0, 2},
            {1, 2},
            {2, 2},
            {3, 2},
            {2, 0},
            {3, 0},
            {4, 2},
            {5, 2},
            {0, 3},
            {1, 3},
            {2, 3},
            {3, 3},
            {2, 1},
            {3, 1},
            {4, 3},
            {5, 3},
        },
        {
            {2, 0},
            {3, 0},
            {2, 2},
            {3, 2},
            {4, 2},
            {5, 2},
            {2, 4},
            {3, 4},
            {2, 1},
            {3, 1},
            {2, 3},
            {3, 3},
            {4, 3},
            {5, 3},
            {2, 5},
            {3, 5},
        },
        {
            {0, 2},
            {1, 2},
            {2, 4},
            {3, 4},
            {2, 2},
            {3, 2},
            {4, 2},
            {5, 2},
            {0, 3},
            {1, 3},
            {2, 5},
            {3, 5},
            {2, 3},
            {3, 3},
            {4, 3},
            {5, 3},
        },
        {
            {2, 0},
            {3, 0},
            {0, 2},
            {1, 2},
            {2, 2},
            {3, 2},
            {2, 4},
            {3, 4},
            {2, 1},
            {3, 1},
            {0, 3},
            {1, 3},
            {2, 3},
            {3, 3},
            {2, 5},
            {3, 5},
        },
    },
    {
        // ***** Z *****
        {
            {0, 0},
            {1, 0},
            {2, 2},
            {3, 2},
            {2, 0},
            {3, 0},
            {4, 2},
            {5, 2},
            {0, 1},
            {1, 1},
            {2, 3},
            {3, 3},
            {2, 1},
            {3, 1},
            {4, 3},
            {5, 3},
        },
        {
            {2, 2},
            {3, 2},
            {4, 0},
            {5, 0},
            {4, 2},
            {5, 2},
            {2, 4},
            {3, 4},
            {2, 3},
            {3, 3},
            {4, 1},
            {5, 1},
            {4, 3},
            {5, 3},
            {2, 5},
            {3, 5},
        },
        {
            {0, 2},
            {1, 2},
            {2, 4},
            {3, 4},
            {2, 2},
            {3, 2},
            {4, 4},
            {5, 4},
            {0, 3},
            {1, 3},
            {2, 5},
            {3, 5},
            {2, 3},
            {3, 3},
            {4, 5},
            {5, 5},
        },
        {
            {2, 0},
            {3, 0},
            {0, 2},
            {1, 2},
            {2, 2},
            {3, 2},
            {0, 4},
            {1, 4},
            {2, 1},
            {3, 1},
            {0, 3},
            {1, 3},
            {2, 3},
            {3, 3},
            {0, 5},
            {1, 5},
        },
    },

};

const int8_t kick_clockwise[4][5][2] = {
    {{0, 0}, {-2, 0}, {-2, 2}, {0, -4}, {-2, -4}},
    {{0, 0}, {2, 0}, {2, -2}, {0, 4}, {2, 4}},
    {{0, 0}, {2, 0}, {2, 2}, {0, -4}, {2, -4}},
    {{0, 0}, {-2, 0}, {-2, -2}, {0, 4}, {-2, 4}}};
const int8_t kick_I_clockwise[4][5][2] = {
    {{0, 0}, {-4, 0}, {2, 0}, {-4, 2}, {2, -4}},
    {{0, 0}, {-2, 0}, {4, 0}, {-2, -4}, {4, 2}},
    {{0, 0}, {4, 0}, {-2, 0}, {4, 2}, {-2, -4}},
    {{0, 0}, {2, 0}, {-4, 0}, {2, -4}, {-4, 2}}};
