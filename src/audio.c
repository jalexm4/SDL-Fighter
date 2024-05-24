//
//
//

#include <SDL2/SDL_mixer.h>

#include "../include/audio.h"
#include "../include/game.h"


void load_music(Game *game, char *filepath)
{
    // Pause and unallocate currently loaded music
    if (game->bg_music != NULL)
    {
        Mix_HaltMusic();
        Mix_FreeMusic(game->bg_music);

        game->bg_music = NULL;
    }

    // Load music from disk
    game->bg_music = Mix_LoadMUS(filepath);

    return;
}
