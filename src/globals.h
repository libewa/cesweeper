#pragma once

#include <ti/getkey.h>
#include <keypadc.h>
#include <sys/timers.h>
#include "gfx/tile_names.h"

#define SCALE 3

extern int tile_width;
extern int tile_height;

extern int cursorX;
extern int cursorY;

typedef enum {
    CELL_HIDDEN_EMPTY,
    CELL_MINE,
    CELL_REVEALED_EMPTY,
    CELL_FLAGGED_EMPTY,
    CELL_FLAGGED_MINE,
} CellState;

extern CellState grid[9][9];
extern CellState* currentCell;

extern bool isFirstMove;
extern bool gameIsOver;