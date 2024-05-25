//
//
//

#pragma once

#include <stdbool.h>

#include <SDL2/SDL.h>

#include "bullets.h"
#include "game.h"
// #include "player.h"


typedef struct
{
    int x;
    int y;
    int x_velocity;
    int health;
    int attack_timer;
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
    int default_health;

    // Enemy bullets
    SDL_Texture *bullet_texture;
    int bullet_width;
    int bullet_height;
    int bullet_speed;
} EnemyConfig;

typedef struct
{
    EnemyConfig config;

    EnemyVector *enemies;
    BulletVector *bullets;

    Mix_Chunk *sounds[2];
} EnemyContainer;

//TODO: ^ Forward declartion to avoid circular dependency. Find better solution.
#include "player.h"

typedef enum
{
    ENEMY_FIRE,
    ENEMY_DIE
} EnemySounds;

void setup_enemies(EnemyContainer *container, Game *game);
void update_enemies(EnemyContainer *container, Game *game, Player *player);
void render_enemies(EnemyContainer *container, Game *game);

EnemyVector *enemy_create_vector();
void enemy_free_vector(EnemyVector *vector);
void enemy_resize_vector(EnemyVector *vector);
void enemy_push_back(EnemyVector *vector, Enemy enemy);
Enemy *enemy_get(EnemyVector *vector, int index);
void enemy_remove(EnemyVector *vector, int index);
