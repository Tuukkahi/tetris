# Tetris


<img src="demo.gif" width="500"/>

## Instructions

There is a Makefile provided that compiles the code to `tetris` binary. `make run` compiles and runs the binary. Terminal window needs to be big enough to fit the curses windows before starting the game.

In menu, j and k moves down and up, enter confirms the choice.
The controls for the game are vim-like h, j, k, l and spacebar to move left, down, rotate, right and drop a tetromino.

## About

I wanted to see how curses programs work so decided to write my own Tetris using C. As it turned out, curses was pretty easy to use and the documentation was very helpful. Tetris, however is surprisingly complex game and most of the time went to writing the game logic.

I decided to run the game in two POSIX threads, one to draw the curses windows and check for user input at 60Hz and the other to drop a tetromino at the correct speed according to current level. Some mutexes were also needed to avoid data race conditions. This solution allows the threads to sleep correct amount of time between ticks instead of constantly checking the clock.
