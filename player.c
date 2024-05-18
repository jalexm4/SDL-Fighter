//
//
//

#include <stdlib.h>
#include <stdio.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "game.h"
#include "player.h"

void setup_player(Player *player, Game *game)
{


    player->texture = IMG_LoadTexture(game->renderer, "assets/player.png");

    player->x = 100;
    player->y = 100;
    SDL_QueryTexture(player->texture, NULL, NULL, &player->w, &player->h);
    player->x_velocity = 0;
    player->y_velocity = 0;
    player->speed = 500;

    player->reload = 0;
    player->bullets = bullet_create_vector();
    player->bullets->texture = IMG_LoadTexture(game->renderer, "assets/player_bullet.png");
    SDL_QueryTexture(player->bullets->texture, NULL, NULL, &player->bullets->width, &player->bullets->height);
    player->bullets->speed = 16;

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

    // Allocate room for 10 particles (to start with)
    vector->data = malloc(10 * sizeof(BulletVector));
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

    return;
}
