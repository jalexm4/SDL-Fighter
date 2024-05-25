#pragma once

#include <SDL2/SDL_mixer.h>

#include "game.h"


#define AUDIO_MAX_CHANNELS (4)

typedef enum {
    CH_ANY = -1,
    CH_PLAYER_FIRE,
    CH_ENEMY_FIRE,
    CH_PLAYER_DIE,
    CH_ENEMY_DIE
} AUDIO_CHANNELS;

void load_music(Game *game, char *filepath);
void play_sfx(Mix_Chunk *sfx, int channel);
