//
//
//

#include <stdbool.h>
#include <stdio.h>

#include <SDL2/SDL.h>

typedef struct
{
    // Game Config
    unsigned int window_width;
    unsigned int window_height;

    // Window
    SDL_Window *window;
    SDL_Renderer *renderer;

    // Delatime
    float delta_time;
    int last_frame_time;
} Game;

typedef struct
{
    bool quit;
} Keys;


void handle_keyboard(Keys *keys);


int main(void)
{
    // Game Config
    Game game;

    game.window_width = 1280;
    game.window_height = 720;

    game.delta_time = 0.0;
    game.last_frame_time = 0;

    // Setup SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        printf("[*] SDL Failed to start...\n[*] Exiting...\n");
        return 1;
    }

    game.window = SDL_CreateWindow(
        "SDL Fighter",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        game.window_width,
        game.window_height,
        0
    );

    if(!game.window)
    {
        printf("[*] Failed to create window...\n[*] Exiting...\n");
        return 1;
    }


    Uint32 render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
    game.renderer = SDL_CreateRenderer(game.window, -1, render_flags);

    if(!game.renderer)
    {
        printf("[*] Failed to create renderer...\n[*] Exiting...\n");
        return 1;
    }

    // Game Init
    Keys keys = {false};

    // Game Loop
    while (1)
    {
        // Deltatime for current frame
        game.delta_time = (SDL_GetTicks() - game.last_frame_time) / 1000.0;
        game.last_frame_time = SDL_GetTicks();

        // Respond to users keyboard input
        handle_keyboard(&keys);

        if (keys.quit)
        {
            break;
        }

        // Clear previous frame and set background colour
        SDL_SetRenderDrawColor(game.renderer, 96, 128, 255, 255);
        SDL_RenderClear(game.renderer);

        // Flip front and back buffers
        SDL_RenderPresent(game.renderer);
    }

    // Cleanup
    SDL_DestroyWindow(game.window);
    SDL_DestroyRenderer(game.renderer);

    // Terminate SDL
    SDL_Quit();

    return 0;
}


void handle_keyboard(Keys *keys)
{
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_QUIT:
                keys->quit = true;
                break;

            default:
                break;
        }
    }

    return;
}
