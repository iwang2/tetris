#include "draw.h"
#include "gba.h"
#include "images/i.h"
#include "images/j.h"
#include "images/l.h"
#include "images/o.h"
#include "images/s.h"
#include "images/t.h"
#include "images/z.h"
#include "lib.h"

void drawBlock(Block block) {
    //drawImageDMA(block.y * SPACE, block.x * SPACE + BOARD_OFFSET, SPACE, SPACE, o);
    int type = block.type;
    for (int r = 0; r < 4; r++) {
        for (int c = 0; c < 4; c++) {
            if (BLOCKS[type][block.rotation][r][c] == 1 && block.y + r >= 0) {
                if (type == 0) {
                    drawImageDMA((block.y + r) * SPACE, (block.x + c) * SPACE + BOARD_OFFSET, SPACE, SPACE, i);
                } else if (type == 1) {
                    drawImageDMA((block.y + r) * SPACE, (block.x + c) * SPACE + BOARD_OFFSET, SPACE, SPACE, j);
                } else if (type == 2) {
                    drawImageDMA((block.y + r) * SPACE, (block.x + c) * SPACE + BOARD_OFFSET, SPACE, SPACE, l);
                } else if (type == 3) {
                    drawImageDMA((block.y + r) * SPACE, (block.x + c) * SPACE + BOARD_OFFSET, SPACE, SPACE, o);
                } else if (type == 4) {
                    drawImageDMA((block.y + r) * SPACE, (block.x + c) * SPACE + BOARD_OFFSET, SPACE, SPACE, s);
                } else if (type == 5) {
                    drawImageDMA((block.y + r) * SPACE, (block.x + c) * SPACE + BOARD_OFFSET, SPACE, SPACE, t);
                } else if (type == 6) {
                    drawImageDMA((block.y + r) * SPACE, (block.x + c) * SPACE + BOARD_OFFSET, SPACE, SPACE, z);
                }
            }
        }
    }
}

void eraseBlock(Block block) {
    //drawRectDMA(block.y * SPACE, block.x * SPACE + BOARD_OFFSET, SPACE * 2, SPACE * 2, BLACK);
    int type = block.type;
    for (int r = 0; r < 4; r++) {
        for (int c = 0; c < 4; c++) {
            if (BLOCKS[type][block.rotation][r][c] == 1 && block.y + r >= 0) {
                drawRectDMA((block.y + r) * SPACE, (block.x + c) * SPACE + BOARD_OFFSET, SPACE, SPACE, BLACK);
            }
        }
    }
}

/*void drawClearLines(int y) {
    for (int r = (y + 1) * SPACE; r > 1 * SPACE; r++) {
        DMA[3].src = videoBuffer + r - 2 * SPACE;
        DMA[3].dst = videoBuffer + r;
        DMA[3].cnt = BOARD_WIDTH * SPACE | DMA_ON | DMA_SOURCE_INCREMENT | DMA_DESTINATION_INCREMENT;
    }
}*/

// This function will be used to draw everything about the app
// including the background and whatnot.
void fullDrawAppState(AppState *state) {
    fillScreenDMA(WHITE);
    drawRectDMA(0, 0 + BOARD_OFFSET, BOARD_WIDTH * SPACE, BOARD_HEIGHT * SPACE, BLACK);
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