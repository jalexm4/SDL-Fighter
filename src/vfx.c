//
//
//

#include <stdio.h>
#include <stdlib.h>

#include <SDL2/SDL.h>

#include <game.h>
#include <vfx.h>
#include <vector/vector.h>


void update_explosions(Explosions *explosions)
{
    for (unsigned int i = 0, n = explosions->vector->size; i < n; i++)
    {
        // Explosion *explosion = explosion_get(explosions->vector, i);
        Explosion *explosion = vector_get(explosions->vector, i);

        explosion->x += explosion->x_velocity;
        explosion->y += explosion->y_velocity;

        explosion->a--;

        if (explosion->a <= 0)
        {
            vector_remove(explosions->vector, i);
        }
    }

    return;
}

void reset_explosions(Explosions *explosions)
{
    vector_free(explosions->vector);
    explosions->vector = vector_create(10);

    return;
}

void render_explosions(Game *game, Explosions *explosions)
{
    SDL_SetRenderDrawBlendMode(game->renderer, SDL_BLENDMODE_ADD);
    SDL_SetTextureBlendMode(explosions->texture, SDL_BLENDMODE_ADD);

    for (unsigned int i = 0, n = explosions->vector->size; i < n; i++)
    {
        Explosion *explosion = vector_get(explosions->vector, i);

        SDL_SetTextureColorMod(explosions->texture, explosion->r, explosion->g, explosion->b);
        SDL_SetTextureAlphaMod(explosions->texture, explosion->a);

        SDL_Rect rect = {explosion->x, explosion->y, explosions->width, explosions->height};
        SDL_RenderCopy(game->renderer, explosions->texture, NULL, &rect);
    }

    SDL_SetRenderDrawBlendMode(game->renderer, SDL_BLENDMODE_NONE);

    return;
}
