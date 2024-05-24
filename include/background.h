#pragma once

#include "game.h"


typedef struct {
    SDL_Texture *texture;
    int x_shift;
} Background;

void update_background(Background *background, Game *game);
void render_background(Background *background, Game *game);
