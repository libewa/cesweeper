#include "globals.h"

int tile_width = 9 * SCALE;
int tile_height = 9 * SCALE;

int cursorX = 4;
int cursorY = 4;

CellState grid[9][9];
CellState* currentCell = &grid[4][4];

bool isFirstMove = true;
bool gameIsOver = false;