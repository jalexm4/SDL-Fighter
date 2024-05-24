#pragma once

#include <SDL2/SDL_mixer.h>

#include "game.h"


#define AUDIO_MAX_CHANNELS (1)

void load_music(Game *game, char *filepath);
