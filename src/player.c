//
//
//

#include <stdlib.h>
#include <stdio.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../include/audio.h"
#include "../include/collision.h"
#include "../include/player.h"
#include "../include/enemies.h"
#include "../include/game.h"



static void detect_player_bounds_collision(Player *player, Game *game)
{
    // Stop player from leaving left or right side of the window
    int player_x_movement = player->x_velocity * game->delta_time;
    if (player->x + player_x_movement < 0 || (player->x + player->w) + player_x_movement > game->window_width)
    {
        player->x_velocity = 0;
    }

    // Stop player from leaving top or bottom side of the window
    int player_y_movement = player->y_velocity * game->delta_time;
    if (player->y + player_y_movement < 0 || (player->y + player->h) + player_y_movement > game->window_height)
    {
        player->y_velocity = 0;
    }

    return;
}

void setup_player(Player *player, Game *game)
{
    player->texture = IMG_LoadTexture(game->renderer, "assets/player.png");
    player->bullet_texture = IMG_LoadTexture(game->renderer, "assets/player_bullet.png");

    player->x = 100;
    player->y = 100;
    SDL_QueryTexture(player->texture, NULL, NULL, &player->w, &player->h);
    player->x_velocity = 0;
    player->y_velocity = 0;
    player->speed = 500;

    player->health = 1;

    player->bullets = bullet_create_vector();
    player->reload = 0;
    SDL_QueryTexture(player->bullet_texture, NULL, NULL, &player->bullet_width, &player->bullet_height);
    player->bullet_speed = 16;

    // Load Sounds
    player->sounds[PLAYER_FIRE] = Mix_LoadWAV("assets/audio/player_fire.ogg");
    player->sounds[PLAYER_DIE] = Mix_LoadWAV("assets/audio/player_die.ogg");

    return;
}

void update_player(Player *player, Game *game, EnemyContainer *enemy_container)
{
    // Reload timer
    if (player->reload > 0)
    {
        player->reload--;
    }

    // Prevent player from leaving window
    detect_player_bounds_collision(player, game);

    // Update Player POS
    player->x += player->x_velocity * game->delta_time;
    player->y += player->y_velocity * game->delta_time;

    // Update Player bullets
    for (int i = 0, n = player->bullets->size; i < n; i++)
    {
        Bullet *bullet = bullet_get(player->bullets, i);

        // Update player bullet positions
        bullet->x += player->bullet_speed;

        // Check if bullets leave screen
        if (bullet->x >= game->window_width)
        {
            bullet_remove(player->bullets, i);
            continue;
        }

        // Check AABB of bullet to each enemy
        for (int j = 0, enemy_size = enemy_container->enemies->size; j < enemy_size; j++)
        {
            Enemy *enemy = enemy_get(enemy_container->enemies, j);

            if (aabb_collision_detection(bullet->x, bullet->y, player->bullet_width, player->bullet_height, enemy->x, enemy->y, enemy_container->config.width, enemy_container->config.height))
            {
                bullet_remove(player->bullets, i);
                enemy->health--;

                if (enemy->health <= 0)
                {
                    enemy_remove(enemy_container->enemies, j);

                    play_sfx(enemy_container->sounds[ENEMY_DIE], CH_ENEMY_DIE);
                }

                break;
            }
        }
    }

    return;
}

void render_player(Player *player, Game *game)
{
    // Render Player Sprite
    SDL_Rect player_rect = {player->x, player->y, player->w, player->h};
    SDL_RenderCopy(game->renderer, player->texture, NULL, &player_rect);

    // Render Player Bullets
    for (int i = 0, n = player->bullets->size; i < n; i++)
    {
        Bullet *bullet = bullet_get(player->bullets, i);

        SDL_Rect bullet_rect = {bullet->x, bullet->y, player->bullet_width, player->bullet_height};
        SDL_RenderCopy(game->renderer, player->bullet_texture, NULL, &bullet_rect);
    }

    return;
}

