#include "free_tiles.h"

bool freeTilesAvailable(void) {
    for (int x = 0; x < 9; x++) {
        for (int y = 0; y < 9; y++) {
            if (grid[x][y] == CELL_HIDDEN_EMPTY || grid[x][y] == CELL_MINE) {
                return true;
            }
        }
    }
    return false;
}