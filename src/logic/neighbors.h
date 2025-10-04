#pragma once
#include "../globals.h"

int countNeighbors(int cellX, int cellY, CellState state);
int countNeighborsMine(int cellX, int cellY);
int countNeighborsFlagged(int cellX, int cellY);
