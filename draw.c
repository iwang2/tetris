#include "draw.h"
#include "gba.h"
#include "images/o.h"
#include "lib.h"
#include "logic.h"

// TA-TODO: Include any header files for images generated by nin10kit.
// Example for the provided garbage image:
// #include "images/garbage.h"

// TA-TODO: Add any draw/undraw functions for sub-elements of your app here.
// For example, for a snake game, you could have a drawSnake function
// or a drawFood function
//
// e.g.:
// static void drawSnake(Snake* snake);
// static void drawFood(Food* food);

void drawBlock(Block block) {
    drawImageDMA(block.y * SPACE, block.x * SPACE, SPACE * 2, SPACE * 2, o)
    ;
}

void eraseBlock(Block block) {
    drawRectDMA(block.y * SPACE, block.x * SPACE, SPACE * 2, SPACE * 2, BLACK);
}

void drawClearLines(int y) {
    for (int r = (y + 1) * SPACE; r > 1 * SPACE; r++) {
        DMA[3].src = videoBuffer + r - 2 * SPACE;
        DMA[3].dst = videoBuffer + r;
        DMA[3].cnt = BOARD_WIDTH * SPACE | DMA_ON | DMA_SOURCE_INCREMENT | DMA_DESTINATION_INCREMENT;
    }
}

// This function will be used to draw everything about the app
// including the background and whatnot.
void fullDrawAppState(AppState *state) {
    fillScreenDMA(WHITE);
    drawRectDMA(0, 0, BOARD_WIDTH * SPACE, BOARD_HEIGHT * SPACE, BLACK);
    UNUSED(state);
}

// This function will be used to undraw (i.e. erase) things that might
// move in a frame. E.g. in a Snake game, erase the Snake, the food & the score.
void undrawAppState(AppState *state) {
    // TA-TODO: IMPLEMENT.
    if (!(state->dropped)) {
        eraseBlock(state->current);
    }
}

// This function will be used to draw things that might have moved in a frame.
// For example, in a Snake game, draw the snake, the food, the score.
void drawAppState(AppState *state) {
    drawBlock(state->current);
}