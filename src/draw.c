#include "draw.h"
#include "logic/neighbors.h"
#include "globals.h"
#include "gfx/gfx.h"

void drawGrid(void) {
    for (int x = 0; x < 9; x++) {
        for (int y = 0; y < 9; y++) {
            if (countNeighborsMine(x, y) != 0 || grid[x][y] != CELL_REVEALED_EMPTY) {
                gfx_ScaledSprite_NoClip(sprite_tile, tile_width * x, tile_height * y, SCALE, SCALE);
            } else {
                gfx_ScaledSprite_NoClip(sprite_blank, tile_width * x, tile_height * y, SCALE, SCALE);
            }
        }
    }
}

void drawSpriteInGrid(const gfx_sprite_t* sprite, int gridX, int gridY) {
    gfx_ScaledTransparentSprite_NoClip(sprite, tile_width * gridX, tile_height * gridY, SCALE, SCALE);
}

void drawCursorInGrid(int gridX, int gridY) {
    gfx_TransparentSprite_NoClip(sprite_cursor, tile_width * gridX + tile_width / 2, tile_height * gridY + tile_height / 2);
}

void drawCells(void) {
    for (int x = 0; x < 9; x++) {
            for (int y = 0; y < 9; y++) {
                switch (grid[x][y]) {
                    case CELL_HIDDEN_EMPTY:
                        // do nothing
                        break;
                    case CELL_MINE:
                        if (gameIsOver) {
                            drawSpriteInGrid(sprite_mine, x, y);
                        }
                        break;
                    case CELL_REVEALED_EMPTY:
                        switch (countNeighborsMine(x, y)) {
                            case 0:
                                // do nothing
                                break;
                            case 1:
                                drawSpriteInGrid(sprite_1, x, y);
                                break;
                            case 2:
                                drawSpriteInGrid(sprite_2, x, y);
                                break;
                            case 3:
                                drawSpriteInGrid(sprite_3, x, y);
                                break;
                            case 4:
                                drawSpriteInGrid(sprite_4, x, y);
                                break;
                            case 5:
                                drawSpriteInGrid(sprite_5, x, y);
                                break;
                            case 6:
                                drawSpriteInGrid(sprite_6, x, y);
                                break;
                            case 7:
                                drawSpriteInGrid(sprite_7, x, y);
                                break;
                            case 8:
                                drawSpriteInGrid(sprite_8, x, y);
                                break;
                        }
                        break;
                    case CELL_FLAGGED_EMPTY:
                    case CELL_FLAGGED_MINE:
                        drawSpriteInGrid(sprite_flag, x, y);
                        break;
                }
            }
        }
}
