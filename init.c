//
//
//

#include <SDL2/SDL.h>

#include "game.h"


int init_sdl(Game *game)
{
    // Start SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        printf("[*] SDL Failed to start...\n");
        return 1;
    }

    game->window = SDL_CreateWindow(
        "SDL Fighter",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        game->window_width,
        game->window_height,
        0
    );

    if(!game->window)
    {
        printf("[*] Failed to create window...\n");
        return 1;
    }

    Uint32 render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
    game->renderer = SDL_CreateRenderer(game->window, -1, render_flags);

    if(!game->renderer)
    {
        printf("[*] Failed to create renderer...\n");
        return 1;
    }

    return 0;
}
