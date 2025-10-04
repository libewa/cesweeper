#include "globals.h"
#include "logic/neighbors.h"
#include "logic/mines.h"
#include "logic/click.h"
#include "draw.h"
#include "gfx/gfx.h"
#include "saves.h"
#include "logic/free_tiles.h"
#include "keypad.h"
#include <time.h>
#include <ti/getcsc.h>
#include <graphx.h>

int main(void) {
    timer_Enable(2, TIMER_32K, TIMER_NOINT, TIMER_UP); // start timer to seed RNG on first click
    kb_EnableOnLatch();
    kb_ClearOnLatch();
    gfx_Begin();
    gfx_SetPalette(global_palette, sizeof_global_palette, 0);
    
    gfx_SetTransparentColor(0);
    gfx_FillScreen(0);

    loadScores(scores);

    clock_t gameTime = clock();
    int nameIndex = 0; /* index for non-blocking name entry */

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

        if (!freeTilesAvailable() && !gameIsWon) {
            gameIsWon = true;
            inTextEntry = true;
            playerScore.time = (clock() - gameTime) / CLOCKS_PER_SEC;
            /* reset name buffer and index for entry */
            for (int i = 0; i < 10; i++) playerScore.name[i] = '\0';
            nameIndex = 0;
        }

        if (!gameIsExplode && !gameIsWon) {
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
        }
        delay(70);

        drawGrid();
        drawCells();
        drawCursorInGrid(cursorX, cursorY);
        //TODO: draw time and mines left
        //TODO: draw high score list
        if (gameIsExplode) {
            drawPopup("Game Over!");
        } else if (gameIsWon) {
            drawPopup("You Win! Please enter name:");
            gfx_SetTextXY(20, 80);
            gfx_PrintUInt(playerScore.time, 3);
            gfx_PrintChar('s');
            /* ensure text colors for the popup are set before printing name */
            gfx_SetTextBGColor(3);
            gfx_SetTextFGColor(9);
            /* draw current name buffer every frame so it persists across redraws */
            gfx_PrintStringXY(playerScore.name, 20, 110);

            if (inTextEntry) {
                char input = getKeypadInput();

                if (input == '\n' || nameIndex >= 9) {
                    /* finish entry */
                    playerScore.name[nameIndex] = '\0';
                    inTextEntry = false;
                    saveCurrentScore();
                    saveScores(scores);
                    goto end;
                } else if (input == '\b') {
                    /* backspace */
                    if (nameIndex > 0) {
                        nameIndex--;
                        playerScore.name[nameIndex] = '\0';
                        gfx_SetTextXY(20 + (nameIndex) * 6, 110);
                        gfx_PrintChar(' ');
                    }
                } else if (input != '\0') {
                    /* append character and print it immediately */
                    playerScore.name[nameIndex++] = input;
                    playerScore.name[nameIndex] = '\0';
                    gfx_SetTextXY(20 + (nameIndex - 1) * 6, 110);
                    gfx_PrintChar(input);
                }
            }
        }


        gfx_SwapDraw();
    }

    end:

    gfx_End();

    kb_ClearOnLatch();

    kb_DisableOnLatch();
}