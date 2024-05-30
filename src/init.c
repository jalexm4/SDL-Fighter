//
//
//

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

#include <audio.h>
#include <game.h>


int init_sdl(Game *game)
{
    // Start SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
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

    // Start SDL Image
    if (IMG_Init(IMG_INIT_PNG) == 0)
    {
        printf("[*] SDL_image failed to start...\n");
        return 1;
    }

    // Start SDL Mixer
    if (Mix_Init(MIX_INIT_OGG) == 0)
    {
        printf("[*] SDL_mixer failed to start...\n");
        return 1;
    }

    // Open Audio Device
    if (Mix_OpenAudio(48000, MIX_DEFAULT_FORMAT, 2, 2048) == -1)
    {
        printf("[*] Failed to open audio device...\n");
        return 1;
    }

    // Number of different sounds being played concurrently
    Mix_AllocateChannels(AUDIO_MAX_CHANNELS);

    // Disable Mouse Cursor
    SDL_ShowCursor(0);

    return 0;
}
