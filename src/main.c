#include "globals.h"
#include "logic/neighbors.h"
#include "logic/mines.h"
#include "logic/click.h"
#include "draw.h"
#include "gfx/gfx.h"

int main(void) {
    timer_Enable(3, TIMER_32K, TIMER_NOINT, TIMER_UP); // start timer to seed RNG on first click
    kb_EnableOnLatch();
    kb_ClearOnLatch();
    gfx_Begin();
    gfx_SetPalette(global_palette, sizeof_global_palette, 0);
    
    gfx_SetTransparentColor(0);
    gfx_FillScreen(0);

    // mines are generated on first click so the first move is always safe

    while (!kb_On) {
        gfx_FillScreen(0);
        kb_Scan();
        int movementInput = kb_Data[7];

        if (movementInput & kb_Left && cursorX > 0) {
            cursorX--;
        }
        if (movementInput & kb_Right && cursorX < 8) {
            cursorX++;
        }
        if (movementInput & kb_Up && cursorY > 0) {
            cursorY--;
        }
        if (movementInput & kb_Down && cursorY < 8) {
            cursorY++;
        }
        currentCell = &grid[cursorX][cursorY];

        int actionInput = kb_Data[6];
        if (actionInput & kb_Enter) {
            clickCell(cursorX, cursorY);
        }

        if (actionInput & kb_Add) {
            if (*currentCell == CELL_HIDDEN_EMPTY) {
                *currentCell = CELL_FLAGGED_EMPTY;
            } else if (*currentCell == CELL_FLAGGED_EMPTY) {
                *currentCell = CELL_HIDDEN_EMPTY;
            } else if (*currentCell == CELL_MINE) {
                *currentCell = CELL_FLAGGED_MINE;
            } else if (*currentCell == CELL_FLAGGED_MINE) {
                *currentCell = CELL_MINE;
            }
        }

        delay(70);

        drawGrid();
        drawCells();
        drawCursorInGrid(cursorX, cursorY);

        gfx_SwapDraw();
    }

    end:

    gfx_End();
    kb_ClearOnLatch();

    kb_DisableOnLatch();
}