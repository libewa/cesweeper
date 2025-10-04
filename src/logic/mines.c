#include "mines.h"
#include "../globals.h"

/* Place 10 mines randomly but never on (excludeX,excludeY) or its 8 neighbors.
   This guarantees the first click is always safe. */
void generateMinesExcluding(int excludeX, int excludeY) {
    const int width = 9;
    const int height = 9;
    const int totalMines = 10;

    int minesPlaced = 0;
    while (minesPlaced < totalMines) {
        int rx = randInt(0, width - 1);
        int ry = randInt(0, height - 1);

        // skip excluded cell and neighbors
        if (rx >= excludeX - 1 && rx <= excludeX + 1 && ry >= excludeY - 1 && ry <= excludeY + 1) continue;

        if (grid[rx][ry] == CELL_HIDDEN_EMPTY) {
            grid[rx][ry] = CELL_MINE;
            minesPlaced++;
        }
    }
}