#include "free_tiles.h"

bool freeTilesAvailable(void) {
    if (isFirstMove) return true;
    for (int x = 0; x < 9; x++) {
        for (int y = 0; y < 9; y++) {
            //TODO: when the num_mines are shown on screen, use that instead.
            // also, allow doing flagless.
            if (grid[x][y] == CELL_MINE) {
                return true;
            }
        }
    }
    return false;
}
