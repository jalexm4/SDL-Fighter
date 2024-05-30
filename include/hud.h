#pragma once

#include <SDL2/SDL.h>

#define GLYPH_WIDTH (18)
#define GLYPH_HEIGHT (28)


typedef struct {
    SDL_Texture *texture;
    int width;
    int height;

    char score[11];
    char highscore[16];
    char fps[9];
} Hud;

void update_hud(Game *game, Hud *hud);
void update_hud_fps(Game *game, Hud *hud);
void render_text(Game *game, Hud *hud, int x, int y, int r, int g, int b, char *text);
void render_hud(Game *game, Hud *hud);
