#pragma once

#include <game/game.h>


typedef struct {
    int x, y;
    int speed;
} Star;

typedef struct {
    SDL_Texture *texture;
    int x_shift;

    Star stars[500];
} Background;


void setup_starfield(Star *stars, Game *game);
void update_background(Background *background, Game *game);
void render_background(Background *background, Game *game);
