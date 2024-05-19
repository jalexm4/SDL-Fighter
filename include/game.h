//
//
//

#pragma once

#include <stdbool.h>


typedef struct
{
    // Game Config
    int window_width;
    int window_height;

    // Window
    SDL_Window *window;
    SDL_Renderer *renderer;

    // Delatime
    float delta_time;
    int last_frame_time;

    // FPS
    int fps;
    int frame_counter;
    float frame_time;
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
