#ifndef LOGIC_H
#define LOGIC_H

#include "gba.h"
#include "lib.h"

typedef struct {
    int x; // left-most
    int y; // top-most
    //int width;
    //int length;
    int type;
    int rotation;
} Block;

typedef struct {
    // Store whether or not the game is over in this member:
    int gameOver;
    int points;
    int widths[BOARD_HEIGHT]; // holds the width of each row; for clear_rows
    //int heights[BOARD_WIDTH]; // holds the height of each column by index; for dropping pieces
    int board[BOARD_HEIGHT][BOARD_WIDTH]; // origin at bottom left
    Block current; // only O-blocks for now
    //Block *next;
    int dropped;
    //int max_piece_height;
    //int cleared;
} AppState;

// This function can initialize an unused AppState struct.
void initializeAppState(AppState *appState);

// This function will be used to process app frames.
AppState processAppState(AppState *currentAppState, u32 keysPressedBefore, u32 keysPressedNow);

// If you have anything else you need accessible from outside the logic.c
// file, you can add them here. You likely won't.

#endif
