#pragma once

#include <SDL2/SDL.h>

#include <game/game.h>
#include <vector/vector.h>

typedef struct {
    int x, y;
    int x_velocity, y_velocity;
    int r, g, b, a;
} Explosion;


typedef struct {
    SDL_Texture *texture;
    int width;
    int height;

    Vector *vector;
} Explosions;


void update_explosions(Explosions *explosions);
void reset_explosions(Explosions *explosions);
void render_explosions(Game *game, Explosions *explosions);
