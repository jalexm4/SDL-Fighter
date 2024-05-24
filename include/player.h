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
} BulletVector;

typedef struct
{
    SDL_Texture *texture;
    SDL_Texture *bullet_texture;

    int x, y, w, h;
    int x_velocity;
    int y_velocity;
    int speed;

    BulletVector *bullets;
    int reload;
    int bullet_width;
    int bullet_height;
    int bullet_speed;
} Player;

void setup_player(Player *player, Game *game);
void render_player(Player *player, Game *game);
void detect_player_bounds_collision(Player *player, Game *game);

BulletVector *bullet_create_vector();
void bullet_free_vector(BulletVector *vector);
void bullet_resize_vector(BulletVector *vector);
void bullet_push_back(BulletVector *vector, Bullet bullet);
Bullet *bullet_get(BulletVector *vector, int index);
void bullet_remove(BulletVector *vector, int index);
