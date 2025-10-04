#include <graphx.h>
#include <ti/getcsc.h>

#include "gfx/gfx.h"

#define SCALE 3

void drawGrid(void) {
    for (int x = 0; x < 9; x++) {
        for (int y = 0; y < 9; y++) {
            gfx_ScaledSprite_NoClip(sprite_tile, sprite_tile_width * SCALE * x, sprite_tile_height * SCALE * y, SCALE, SCALE);
        }
    }
}

void drawSpriteInGrid(const uint8_t* sprite, int gridX, int gridY) {
    gfx_ScaledSprite_NoClip(sprite, sprite_tile_width * SCALE * gridX + 2 * SCALE, sprite_tile_height * SCALE * gridY + 2 * SCALE, SCALE, SCALE);
}

void generateMines(void) {
    // TODO
}

int main(void) {
    gfx_Begin();
    gfx_SetPalette(global_palette, sizeof_global_palette, 0);
    
    gfx_SetTransparentColor(0);
    gfx_FillScreen(0);

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
    drawSpriteInGrid(sprite_8, 9, 9);

    while (!os_GetCSC());
    gfx_End();
    return 0;
}