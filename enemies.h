//
//
//

#pragma once

#include <stdbool.h>

#include <SDL2/SDL.h>

#include "game.h"

typedef struct
{
    int x;
    int y;
    int x_velocity;
} Enemy;

typedef struct
{
    Enemy *data;
    unsigned int size;
    unsigned int capacity;
} EnemyVector;

typedef struct
{
    SDL_Texture *texture;
    int width;
    int height;

    int respawn_timer;
    int alive;
    int max;

} EnemyConfig;

typedef struct
{
    EnemyVector *enemies;
    EnemyConfig config;
} EnemyContainer;


void setup_enemies(EnemyContainer *container, Game *game);
void render_enemies(EnemyContainer *container, Game *game);
void detect_enemy_bounds_collision(EnemyContainer *container);

EnemyVector *enemy_create_vector();
void enemy_free_vector(EnemyVector *vector);
void enemy_resize_vector(EnemyVector *vector);
void enemy_push_back(EnemyVector *vector, Enemy enemy);
Enemy *enemy_get(EnemyVector *vector, int index);
void enemy_remove(EnemyVector *vector, int index);
