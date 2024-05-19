//
//
//

#pragma once

#include <SDL2/SDL.h>

// Per Bullet Properties
typedef struct
{
    int x;
    int y;
} Bullet;

// Vector of Bullets
typedef struct
{
    Bullet *data;
    unsigned int size;
    unsigned int capacity;

    // General Bullet Properties
    SDL_Texture *texture;
    int width;
    int height;
    int speed;
} BulletVector;

typedef struct
{
    int x, y, w, h;
    int x_velocity;
    int y_velocity;
    int speed;

    int reload;
    BulletVector *bullets;

    SDL_Texture *texture;
} Player;

void setup_player(Player *player, Game *game);
void detect_player_bounds_collision(Player *player, Game *game);

BulletVector *bullet_create_vector();
void bullet_free_vector(BulletVector *vector);
void bullet_resize_vector(BulletVector *vector);
void bullet_push_back(BulletVector *vector, Bullet bullet);
Bullet *bullet_get(BulletVector *vector, int index);
void bullet_remove(BulletVector *vector, int index);
