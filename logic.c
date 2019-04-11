#include "logic.h"


int drop_piece(Block *block, int board[BOARD_HEIGHT][BOARD_WIDTH]) {
    block->y++;
    if (board[block->y + 2][block->x] == 1 || board[block->y + 2][block->x + 1] == 1) return 1;
    /*if (heights[block->x] == block->y + 2 || 
        heights[block->x + 1] == block->y + 2) return 1;*/
    return 0;
}

void clear_line(Block *block, int y, int board[BOARD_HEIGHT][BOARD_WIDTH], int *widths, int *max_piece_height) {
    for (int r = y; r >= *max_piece_height; r++) {
        for (int c = 0; c < BOARD_WIDTH; c++) {
            board[r][c] = board[r - 1][c];
        }
        widths[r] = widths[r - 1];
    }
    for (int c = 0; c < BOARD_WIDTH; c++) {
        board[*max_piece_height][c] = 0;
    }
    (*max_piece_height)++;
    block->y--;
    /*
    for (int i = y; i < *max_piece_height; i++) {
        for (int x = 0; x < BOARD_WIDTH; x++) {
            board[x][i] = board[x][i + 1];
        }
        widths[i] = widths[i + 1];
    }
    for (int i = 0; i < BOARD_WIDTH; i++) {
        board[i][*max_piece_height] = 0;
        heights[i]--;
    }
    *max_piece_height--;
    block->y--;
    */
}

void set_board(int x, int y, int board[BOARD_HEIGHT][BOARD_WIDTH], int *widths) {
    board[y][x] = 1;
    widths[y]++;
}

void place_piece(Block *block, int board[BOARD_HEIGHT][BOARD_WIDTH], int *widths, int *max_piece_height) {
    int x = block->x;
    int y = block->y;

    set_board(x, y, board, widths);
    set_board(x + 1, y, board, widths);
    set_board(x, y + 1, board, widths);
    set_board(x + 1, y + 1, board, widths);

    if (y < *max_piece_height) 
        *max_piece_height = y;
    if (widths[y] == BOARD_WIDTH) 
        clear_line(block, y, board, widths, max_piece_height);
    if (widths[y + 1] == BOARD_WIDTH)
        clear_line(block, y + 1, board, widths, max_piece_height);
}

void initializeAppState(AppState* appState) {
    // TA-TODO: Initialize everything that's part of this AppState struct here.
    // Suppose the struct contains random values, make sure everything gets
    // the value it should have when the app begins.
    appState->gameOver = 0;
    appState->points = 0;
    for (int i = 0; i < BOARD_HEIGHT; i++) {
        appState->widths[i] = 0;
    }
    /*for (int i = 0; i < 10; i++) {
        appState->heights[i] = BOARD_HEIGHT - 1;
    }*/
    for (int r = 0; r < BOARD_HEIGHT; r++) {
        for (int c = 0; c < BOARD_WIDTH; c++) {
            appState->board[r][c] = 0;
        }
    }
    Block *block = appState->current;
    /*block->x = BOARD_WIDTH / 2 - 2;
    block->y = BOARD_HEIGHT - 2;
    block->width = 2;
    block->length = 2;*/
    block->x = BOARD_WIDTH / 2 - 2;
    block->y = 0;
    
    appState->dropped = 0;
    appState->max_piece_height = BOARD_HEIGHT - 1;
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
            (&nextAppState)->current->y = 0;
        } else if (drop_piece(block, (&nextAppState)->board)) {
            place_piece(block, 
                (&nextAppState)->board, 
                (&nextAppState)->widths, 
                //(&nextAppState)->heights, 
                &((&nextAppState)->max_piece_height));
            (&nextAppState)->dropped = 1;
        }
    }
    (&nextAppState)->previous = currentAppState->current;
    return nextAppState;
}