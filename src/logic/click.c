#include "click.h"
#include "neighbors.h"
#include "../globals.h"
#include "mines.h"

void clickNeighbors(int cellX, int cellY) {
    for (int x = cellX - 1; x <= cellX + 1; x++) {
        for (int y = cellY - 1; y <= cellY + 1; y++) {
            if (x < 0 || x >= 9 || y < 0 || y >= 9) continue;
            // don't call on the center cell
            if (x == cellX && y == cellY) continue;
            // only reveal hidden cells (or mines which are hidden as CELL_MINE)
            if (grid[x][y] == CELL_HIDDEN_EMPTY || grid[x][y] == CELL_MINE) {
                clickCell(x, y);
            }
        }
    }
}

void clickCell(int cellX, int cellY) {
    CellState* cell = &grid[cellX][cellY];
    // If this is the first move, generate mines avoiding this cell and neighbors.
    if (isFirstMove) {
        generateMinesExcluding(cellX, cellY);
        isFirstMove = false;
    }

    // If clicked on a flagged cell, ignore
    if (*cell == CELL_FLAGGED_EMPTY || *cell == CELL_FLAGGED_MINE) return;

    // If clicked on a revealed cell, reveal neighbors if flags match
    if (*cell == CELL_REVEALED_EMPTY) {
        if (countNeighborsFlagged(cellX, cellY) == countNeighborsMine(cellX, cellY)) {
            clickNeighbors(cellX, cellY);
        }
        return;
    }
    // Reveal logic
    if (*cell == CELL_HIDDEN_EMPTY) {
        if (countNeighborsMine(cellX, cellY) == 0 && *cell != CELL_REVEALED_EMPTY) {
            // If no neighboring mines, recursively reveal neighbors
            *cell = CELL_REVEALED_EMPTY;
            clickNeighbors(cellX, cellY);
        } else {
            // Just reveal this cell
            *cell = CELL_REVEALED_EMPTY;
        }
    } else if (*cell == CELL_MINE) {
        // Revealed a mine after first move -> game over
        gameIsOver = true;
    }
}