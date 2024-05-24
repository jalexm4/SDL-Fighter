//
//
//

#include <stdlib.h>
#include <stdio.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../include/game.h"
#include "../include/player.h"

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

    player->bullets = bullet_create_vector();
    player->reload = 0;
    SDL_QueryTexture(player->bullet_texture, NULL, NULL, &player->bullet_width, &player->bullet_height);
    player->bullet_speed = 16;

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

void detect_player_bounds_collision(Player *player, Game *game)
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


BulletVector *bullet_create_vector()
{
    // Allocate data for a vector
    BulletVector *vector = malloc(sizeof(BulletVector));
    if (vector == NULL)
    {
        printf("[*] Unable to allocate memory\n");
        return NULL;
    }

    // Allocate room for 10 bullets
    vector->data = malloc(10 * sizeof(Bullet));
    if (vector->data == NULL)
    {
        printf("[*] Unable to allocate memory\n");
        return NULL;
    }

    vector->size = 0;        // No bullest to start with
    vector->capacity = 10;   // Can hold 10 bullets without resizing

    return vector;
}

void bullet_free_vector(BulletVector *vector)
{
    free(vector->data);
    free(vector);

    return;
}

void bullet_resize_vector(BulletVector *vector)
{
    // Double vector capacity
    vector->capacity *= 2;

    vector->data = realloc(vector->data, vector->capacity * sizeof(BulletVector));
    if (vector->data == NULL)
    {
        printf("[*] Unable to allocate memory\n");
    }

    return;
}

void bullet_push_back(BulletVector *vector, Bullet bullet)
{
    // Resize vector if needed
    if (vector->size == vector->capacity)
    {
        bullet_resize_vector(vector);
    }

    // Place data into the vector
    vector->data[vector->size++] = bullet;

    return;
}

Bullet *bullet_get(BulletVector *vector, int index)
{
    return &(vector->data[index]);
}

void bullet_remove(BulletVector *vector, int index)
{
    // Shift Vector
    for (unsigned int i = index; i < vector->size - 1; i++)
    {
        vector->data[i] = vector->data[i + 1];
    }

    vector->size--;

    return;
}
