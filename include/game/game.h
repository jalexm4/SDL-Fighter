//
//
//

#pragma once

#include <stdbool.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>


typedef struct
{
    // Game Config
    int window_width;
    int window_height;

    // Window
    SDL_Window *window;
    SDL_Renderer *renderer;

    // Scoring
    unsigned int score;
    bool score_changed;
    unsigned int highscore;

    // Delatime
    float delta_time;
    int last_frame_time;

    // FPS
    int fps;
    int frame_counter;
    float frame_time;

    // Audio
    Mix_Music *bg_music;

    // Reset if player dies
    bool reset;
} Game;

typedef struct
{
    bool quit;

    bool up;
    bool down;
    bool left;
    bool right;

    bool fire;
} Keys;
