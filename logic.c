#include "logic.h"

const int BLOCKS[7][4][4][4] = {
    { // I
        {
            {0, 0, 0, 0},
            {1, 1, 1, 1},
            {0, 0, 0, 0},
            {0, 0, 0, 0}
        },
        {
            {0, 0, 1, 0},
            {0, 0, 1, 0},
            {0, 0, 1, 0},
            {0, 0, 1, 0}
        },
        {
            {0, 0, 0, 0},
            {0, 0, 0, 0},
            {1, 1, 1, 1},
            {0, 0, 0, 0}
        },
        {
            {0, 1, 0, 0},
            {0, 1, 0, 0},
            {0, 1, 0, 0},
            {0, 1, 0, 0}
        }
    },
    { // J
        {
            {1, 0, 0, 0},
            {1, 1, 1, 0},
            {0, 0, 0, 0},
            {0, 0, 0, 0}
        },
        {
            {0, 1, 1, 0},
            {0, 1, 0, 0},
            {0, 1, 0, 0},
            {0, 0, 0, 0}
        },
        {
            {0, 0, 0, 0},
            {1, 1, 1, 0},
            {0, 0, 1, 0},
            {0, 0, 0, 0}
        },
        {
            {0, 1, 0, 0},
            {0, 1, 0, 0},
            {1, 1, 0, 0},
            {0, 0, 0, 0}
        }
    },
    { // L
        {
            {0, 0, 1, 0},
            {1, 1, 1, 0},
            {0, 0, 0, 0},
            {0, 0, 0, 0}
        },
        {
            {0, 1, 0, 0},
            {0, 1, 0, 0},
            {0, 1, 1, 0},
            {0, 0, 0, 0}
        },
        {
            {0, 0, 0, 0},
            {1, 1, 1, 0},
            {1, 0, 0, 0},
            {0, 0, 0, 0}
        },
        {
            {1, 1, 0, 0},
            {0, 1, 0, 0},
            {0, 1, 0, 0},
            {0, 0, 0, 0}
        }
    },
    { // O
        {
            {0, 1, 1, 0},
            {0, 1, 1, 0},
            {0, 0, 0, 0},
            {0, 0, 0, 0}
        },
        {
            {0, 1, 1, 0},
            {0, 1, 1, 0},
            {0, 0, 0, 0},
            {0, 0, 0, 0}
        },
        {
            {0, 1, 1, 0},
            {0, 1, 1, 0},
            {0, 0, 0, 0},
            {0, 0, 0, 0}
        },
        {
            {0, 1, 1, 0},
            {0, 1, 1, 0},
            {0, 0, 0, 0},
            {0, 0, 0, 0}
        }
    },
    { // S
        {
            {0, 1, 1, 0},
            {1, 1, 0, 0},
            {0, 0, 0, 0},
            {0, 0, 0, 0}
        },
        {
            {0, 1, 0, 0},
            {0, 1, 1, 0},
            {0, 0, 1, 0},
            {0, 0, 0, 0}
        },
        {
            {0, 0, 0, 0},
            {0, 1, 1, 0},
            {1, 1, 0, 0},
            {0, 0, 0, 0}
        },
        {
            {1, 0, 0, 0},
            {1, 1, 0, 0},
            {0, 1, 0, 0},
            {0, 0, 0, 0}
        }
    },
    { // T
        {
            {0, 1, 0, 0},
            {1, 1, 1, 0},
            {0, 0, 0, 0},
            {0, 0, 0, 0}
        },
        {
            {0, 1, 0, 0},
            {0, 1, 1, 0},
            {0, 1, 0, 0},
            {0, 0, 0, 0}
        },
        {
            {0, 0, 0, 0},
            {1, 1, 1, 0},
            {0, 1, 0, 0},
            {0, 0, 0, 0}
        },
        {
            {0, 1, 0, 0},
            {1, 1, 0, 0},
            {0, 1, 0, 0},
            {0, 0, 0, 0}
        }
    },
    { // Z
        {
            {1, 1, 0, 0},
            {0, 1, 1, 0},
            {0, 0, 0, 0},
            {0, 0, 0, 0}
        },
        {
            {0, 0, 1, 0},
            {0, 1, 1, 0},
            {0, 1, 0, 0},
            {0, 0, 0, 0}
        },
        {
            {0, 0, 0, 0},
            {1, 1, 0, 0},
            {0, 1, 1, 0},
            {0, 0, 0, 0}
        },
        {
            {0, 1, 0, 0},
            {1, 1, 0, 0},
            {1, 0, 0, 0},
            {0, 0, 0, 0}
        }
    }
};

int drop_piece(Block *block, int board[BOARD_HEIGHT][BOARD_WIDTH]) {
    //UNUSED(board);
    for (int r = 0; r < 4; r++) {
        for (int c = 0; c < 4; c++) {
            if ((BLOCKS[block->type][block->rotation][r][c] == 1) && 
                    ((block->y + r >= 0 && 
                    board[r + block->y + 1][c + block->x] == 1)
                    || block->y + r + 1 >= BOARD_HEIGHT)) {
                return 1;
            }
        }
    }
    block->y++;
    return 0;
}

void set_board(int x, int y, int board[BOARD_HEIGHT][BOARD_WIDTH], int *widths) {
    board[y][x] = 1;
    widths[y]++;
}

void place_piece(Block *block, int board[BOARD_HEIGHT][BOARD_WIDTH], int *widths) {
    int x = block->x;
    int y = block->y;

    for (int r = 0; r < 4; r++) {
        for (int c = 0; c < 4; c++) {
            if (BLOCKS[block->type][block->rotation][r][c] == 1) {
                board[y + r][x + c] = 1;
                widths[y + r]++;
            }
        }
    }

    /*set_board(x, y, board, widths);
    set_board(x + 1, y, board, widths);
    set_board(x, y + 1, board, widths);
    set_board(x + 1, y + 1, board, widths);*/
}

void move_block_right(Block *block, int board[BOARD_HEIGHT][BOARD_WIDTH]) {
    if (block->x + 2 < BOARD_WIDTH && 
            !board[block->y][block->x + 2] && 
            !board[block->y + 1][block->x + 2]) {
        block->x++;
    }
}
void move_block_left(Block *block, int board[BOARD_HEIGHT][BOARD_WIDTH]) {
    if (block->x > 0 && 
            !board[block->y][block->x - 1] && 
            !board[block->y + 1][block->x - 1]) {
        block->x--;
    }
}
void shift_right(Block *block, int board[BOARD_HEIGHT][BOARD_WIDTH]) {
    for (int r = 0; r < 4; r++) {
        for (int c = 0; c < 4; c++) {
            if (BLOCKS[block->type][block->rotation][r][c] == 1 && 
                    (block->x + c + 1 >= BOARD_WIDTH || 
                    board[block->y + r][block->x + c + 1] == 1))
                return;
        }
    }
    block->x++;
}
void shift_left(Block *block, int board[BOARD_HEIGHT][BOARD_WIDTH]) {
    for (int r = 0; r < 4; r++) {
        for (int c = 0; c < 4; c++) {
            if (BLOCKS[block->type][block->rotation][r][c] == 1 && 
                    (block->x + c < 1 || 
                    board[block->y + r][block->x + c - 1] == 1))
                return;
        }
    }
    block->x--;
}

void rotate_piece(Block *block, int board[BOARD_HEIGHT][BOARD_WIDTH]) {
    int rotation = (block->rotation + 1) % 7;
    for (int r = 0; r < 4; r++) {
        for (int c = 0; c < 4; c++) {
            if (BLOCKS[block->type][rotation][r][c] == 1 && (block->y + r >= BOARD_HEIGHT || block->y + r < 0 || block->x + c >= BOARD_WIDTH || block->x + c < 0 || board[block->y + r][block->x + c] == 1)) return;
        }
    }
    block->rotation = rotation;
}

void initializeAppState(AppState* appState) {
    appState->gameOver = 0;
    appState->points = 0;
    appState->dropped = 0;

    Block *block = &appState->current;
    block->x = BOARD_WIDTH / 2 - 1;
    block->y = 0;
    block->type = randint(0, 6);
    block->rotation = 0;

    for (int i = 0; i < BOARD_HEIGHT; i++) {
        appState->widths[i] = 0;
    }
    for (int r = 0; r < BOARD_HEIGHT; r++) {
        for (int c = 0; c < BOARD_WIDTH; c++) {
            appState->board[r][c] = 0;
        }
    }
}

AppState processAppState(AppState *currentAppState, u32 keysPressedBefore, u32 keysPressedNow) {
    AppState nextAppState = *currentAppState;
    Block *block = &(&nextAppState)->current;

    if (!currentAppState->dropped && KEY_JUST_PRESSED(BUTTON_LEFT, keysPressedNow, keysPressedBefore)) {
        shift_left(block, (&nextAppState)->board);
    } else if (!currentAppState->dropped && KEY_JUST_PRESSED(BUTTON_RIGHT, keysPressedNow, keysPressedBefore)) {
        shift_right(block, (&nextAppState)->board);
    } else if (!currentAppState->dropped && KEY_JUST_PRESSED(BUTTON_UP, keysPressedNow, keysPressedBefore)) {
        rotate_piece(block, (&nextAppState)->board);
    }
    if (!(vBlankCounter % 20)) {
        if (currentAppState->dropped == 1) {
            if (block->y == 0) {
                (&nextAppState)->gameOver = 1;
            }
            (&nextAppState)->dropped = 0;
            block->x = BOARD_WIDTH / 2 - 1;
            block->y = 0;
            block->type = randint(0, 6);
            block->rotation = 0;
        } else if (drop_piece(block, (&nextAppState)->board)) {
            place_piece(block, (&nextAppState)->board, 
                (&nextAppState)->widths);
            (&nextAppState)->dropped = 1;
        }
    }
    return nextAppState;
}