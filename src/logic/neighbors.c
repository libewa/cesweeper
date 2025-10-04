#include "neighbors.h"

int countNeighbors(int cellX, int cellY, CellState state) {
    int count = 0;
    for (int x = cellX - 1; x <= cellX + 1; x++) {
        for (int y = cellY - 1; y <= cellY + 1; y++) {
            if (x < 0 || x >= 9 || y < 0 || y >= 9) continue;
            if (x == cellX && y == cellY) continue;
            if (grid[x][y] == state) count++;
        }
    }
    return count;
}

int countNeighborsMine(int cellX, int cellY) {
    return countNeighbors(cellX, cellY, CELL_MINE) + countNeighbors(cellX, cellY, CELL_FLAGGED_MINE);
}

int countNeighborsFlagged(int cellX, int cellY) {
    return countNeighbors(cellX, cellY, CELL_FLAGGED_EMPTY) + countNeighbors(cellX, cellY, CELL_FLAGGED_MINE);
}