//
//
//

#include <stdio.h>
#include <stdlib.h>

#include <SDL2/SDL.h>

#include <game.h>
#include <vfx.h>


void update_explosions(Explosions *explosions)
{
    for (unsigned int i = 0, n = explosions->vector->size; i < n; i++)
    {
        Explosion *explosion = explosion_get(explosions->vector, i);

        explosion->x += explosion->x_velocity;
        explosion->y += explosion->y_velocity;

        explosion->a--;

        if (explosion->a <= 0)
        {
            explosion_remove(explosions->vector, i);
        }
    }

    return;
}

void reset_explosions(Explosions *explosions)
{
    explosion_free_vector(explosions->vector);
    explosions->vector = explosion_create_vector();

    return;
}

void render_explosions(Game *game, Explosions *explosions)
{
    SDL_SetRenderDrawBlendMode(game->renderer, SDL_BLENDMODE_ADD);
    SDL_SetTextureBlendMode(explosions->texture, SDL_BLENDMODE_ADD);

    for (unsigned int i = 0, n = explosions->vector->size; i < n; i++)
    {
        Explosion *explosion = explosion_get(explosions->vector, i);

        SDL_SetTextureColorMod(explosions->texture, explosion->r, explosion->g, explosion->b);
        SDL_SetTextureAlphaMod(explosions->texture, explosion->a);

        SDL_Rect rect = {explosion->x, explosion->y, explosions->width, explosions->height};
        SDL_RenderCopy(game->renderer, explosions->texture, NULL, &rect);
    }

    SDL_SetRenderDrawBlendMode(game->renderer, SDL_BLENDMODE_NONE);

    return;
}



ExplosionVector *explosion_create_vector(void)
{
    // Allocate data for a vector
    ExplosionVector *vector = malloc(sizeof(ExplosionVector));
    if (vector == NULL)
    {
        printf("[*] Unable to allocate memory\n");
        return NULL;
    }

    // Allocate room for 10 explosions
    vector->data = malloc(10 * sizeof(Explosion));
    if (vector->data == NULL)
    {
        printf("[*] Unable to allocate memory\n");
        return NULL;
    }

    vector->size = 0;        // No bullest to start with
    vector->capacity = 10;   // Can hold 10 bullets without resizing

    return vector;
}

void explosion_free_vector(ExplosionVector *vector)
{
    free(vector->data);
    free(vector);

    return;
}

void explosion_resize_vector(ExplosionVector *vector)
{
    // Double vector capacity
    vector->capacity *= 2;

    vector->data = realloc(vector->data, vector->capacity * sizeof(ExplosionVector));
    if (vector->data == NULL)
    {
        printf("[*] Unable to allocate memory\n");
    }

    return;
}

void explosion_push_back(ExplosionVector *vector, Explosion data)
{
    // Resize vector if needed
    if (vector->size == vector->capacity)
    {
        explosion_resize_vector(vector);
    }

    // Place data into the vector
    vector->data[vector->size++] = data;

    return;
}

Explosion *explosion_get(ExplosionVector *vector, int index)
{
    return &(vector->data[index]);
}


void explosion_remove(ExplosionVector *vector, int index)
{
    // Shift Vector
    for (unsigned int i = index; i < vector->size - 1; i++)
    {
        vector->data[i] = vector->data[i + 1];
    }

    vector->size--;

    return;
}
