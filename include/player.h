//
//
//

#pragma once

#include <SDL2/SDL.h>

#include "bullets.h"


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

//TODO: ^ Forward declartion to avoid circular dependency. Find better solution.
#include "enemies.h"

void setup_player(Player *player, Game *game);
void update_player(Player *player, Game *game, EnemyContainer *enemy_container);
void render_player(Player *player, Game *game);
