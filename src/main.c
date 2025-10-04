#include <graphx.h>
#include <ti/getkey.h>
#include <keypadc.h>
#include <sys/timers.h>

#include "gfx/gfx.h"

#define SCALE 3

const int tile_width = sprite_tile_width * SCALE;
const int tile_height = sprite_tile_height * SCALE;

int cursorX = 4;
int cursorY = 4;

void drawGrid(void) {
    for (int x = 0; x < 9; x++) {
        for (int y = 0; y < 9   ; y++) {
            gfx_ScaledSprite_NoClip(sprite_tile, tile_width * x, tile_height * y, SCALE, SCALE);
        }
    }
}

void drawSpriteInGrid(const uint8_t* sprite, int gridX, int gridY) {
    gfx_ScaledSprite_NoClip(sprite, tile_width * gridX + 2 * SCALE, tile_height * gridY + 2 * SCALE, SCALE, SCALE);
}

void drawCursorInGrid(int gridX, int gridY) {
    gfx_TransparentSprite_NoClip(sprite_cursor, tile_width * gridX + tile_width / 2, tile_height * gridY + tile_height / 2);
}

void generateMines(void) {
    // TODO
}

int main(void) {
    kb_EnableOnLatch();
    kb_ClearOnLatch();
    gfx_Begin();
    gfx_SetPalette(global_palette, sizeof_global_palette, 0);
    
    gfx_SetTransparentColor(0);
    gfx_FillScreen(0);

    while (!kb_On) {
        kb_Scan();
        int key = kb_Data[7];

        if (key & kb_Left && cursorX > 0) {
            cursorX--;
        }
        if (key & kb_Right && cursorX < 8) {
            cursorX++;
        }
        if (key & kb_Up && cursorY > 0) {
            cursorY--;
        }
        if (key & kb_Down && cursorY < 8) {
            cursorY++;
        }

        delay(70);

        drawGrid();
        drawSpriteInGrid(sprite_mine, 0, 0);
        drawSpriteInGrid(sprite_flag, 1, 1);
        drawSpriteInGrid(sprite_1, 2, 2);
        drawSpriteInGrid(sprite_2, 3, 3);
        drawSpriteInGrid(sprite_3, 4, 4);
        drawSpriteInGrid(sprite_4, 5, 5);
        drawSpriteInGrid(sprite_5, 6, 6);
        drawSpriteInGrid(sprite_6, 7, 7);
        drawSpriteInGrid(sprite_7, 8, 8);
        drawSpriteInGrid(sprite_8, 0, 1);
        drawCursorInGrid(cursorX, cursorY);

        gfx_SwapDraw();
    }

    gfx_End();
    kb_ClearOnLatch();

    kb_DisableOnLatch();
}