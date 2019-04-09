#include "logic.h"

int max_piece_height = 0;

void initializeAppState(AppState* appState) {
    // TA-TODO: Initialize everything that's part of this AppState struct here.
    // Suppose the struct contains random values, make sure everything gets
    // the value it should have when the app begins.
    appState->gameOver = 0;
    appState->points = 0;
    for (int i = 0; i < 20; i++) {
        appState->widths[i] = 0;
    }
    for (int i = 0; i < 10; i++) {
        appState->heights[i] = 0;
    }
    for (int r = 0; r < 20; r++) {
        for (int c = 0; c < 10; c++) {
            appState->board[r][c] = 0;
        }
    }
    Block *block = appState->current;
    block->x = BOARD_WIDTH / 2 - 2;
    block->y = BOARD_HEIGHT;
    block->width = 2;
    block->length = 2;
    
    appState->dropped = 0;
}

// TA-TODO: Add any process functions for sub-elements of your app here.
// For example, for a snake game, you could have a processSnake function
// or a createRandomFood function or a processFoods function.
//
// e.g.:
// static Snake processSnake(Snake* currentSnake);
// static void generateRandomFoods(AppState* currentAppState, AppState* nextAppState);

// This function processes your current app state and returns the new (i.e. next)
// state of your application.
AppState processAppState(AppState *currentAppState, u32 keysPressedBefore, u32 keysPressedNow) {
    /* TA-TODO: Do all of your app processing here. This function gets called
     * every frame.
     *
     * To check for key presses, use the KEY_JUST_PRESSED macro for cases where
     * you want to detect each key press once, or the KEY_DOWN macro for checking
     * if a button is still down.
     *
     * To count time, suppose that the GameBoy runs at a fixed FPS (60fps) and
     * that VBlank is processed once per frame. Use the vBlankCounter variable
     * and the modulus % operator to do things once every (n) frames. Note that
     * you want to process button every frame regardless (otherwise you will
     * miss inputs.)
     *
     * Do not do any drawing here.
     *
     * TA-TODO: VERY IMPORTANT! READ THIS PART.
     * You need to perform all calculations on the currentAppState passed to you,
     * and perform all state updates on the nextAppState state which we define below
     * and return at the end of the function. YOU SHOULD NOT MODIFY THE CURRENTSTATE.
     * Modifying the currentAppState will mean the undraw function will not be able
     * to undraw it later.
     */
    
    UNUSED(keysPressedBefore);
    UNUSED(keysPressedNow);

    AppState nextAppState = *currentAppState;
    Block *block = (&nextAppState)->current;
    if (vBlankCounter % 30 == 0) {
        if (currentAppState->dropped == 1) {
            (&nextAppState)->dropped = 0;
            (&nextAppState)->current->x = BOARD_WIDTH / 2 - 2;
            (&nextAppState)->current->y = BOARD_HEIGHT;
        } else if (drop_piece(block, (&nextAppState)->heights)) {
            place_piece(block, (&nextAppState)->board, (&nextAppState)->widths, (&nextAppState)->heights);
            (&nextAppState)->dropped = 1;
        }
    }
    return nextAppState;
}

int drop_piece(Block *block, int *heights) {
    block->y--;
    if (heights[block->x] == block->y || 
        heights[block->x + 1] == block->y) return 1;
    return 0;
}

void place_piece(Block *block, int **board, int *widths, int *heights) {
    int x = block->x;
    int y = block->y;

    set_board(x, y, board, widths, heights);
    set_board(x + 1, y, board, widths, heights);
    set_board(x, y + 1, board, widths, heights);
    set_board(x + 1, y + 1, board, widths, heights);

    if (y + 1 > max_piece_height) 
        max_piece_height = y + 1;
    if (widths[y + 1] == BOARD_WIDTH)
        clear_line(block, y + 1, board, widths, heights);
    if (widths[y] == BOARD_WIDTH) 
        clear_line(block, y, board, widths, heights);
}

void set_board(int x, int y, int **board, int *widths, int *heights) {
    board[x][y] = 1;
    widths[y]++;
    heights[x]++;
}

void clear_line(Block *block, int y, int **board, int *widths, int *heights) {
    for (int i = y; i < max_piece_height; i++) {
        for (int x = 0; x < BOARD_WIDTH; x++) {
            board[x][i] = board[x][i + 1];
        }
        widths[i] = widths[i + 1];
    }
    for (int i = 0; i < BOARD_WIDTH; i++) {
        board[i][max_piece_height] = 0;
        heights[i]--;
    }
    max_piece_height--;
    block->y--;
}