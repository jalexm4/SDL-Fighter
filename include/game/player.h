//
//
//

#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

#include <game/vfx.h>
#include <vector/vector.h>


typedef struct
{
    SDL_Texture *texture;
    SDL_Texture *bullet_texture;

    int x, y, w, h;
    int x_velocity;
    int y_velocity;
    int speed;

    int health;

    // BulletVector *bullets;
    Vector *bullets;
    int reload;
    int bullet_width;
    int bullet_height;
    int bullet_speed;

    // Audio
    Mix_Chunk *sounds[2];
} Player;

//TODO: ^ Forward declartion to avoid circular dependency. Find better solution.
#include <game/enemies.h>

typedef enum {
    PLAYER_FIRE,
    PLAYER_DIE
} PlayerSounds;

void setup_player(Player *player, Game *game);
void update_player(Player *player, Game *game, EnemyContainer *enemy_container, Vector *explosions);
void reset_player(Game *game, Player *player);
void render_player(Player *player, Game *game);
