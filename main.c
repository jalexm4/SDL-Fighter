//
//
//

#include <stdbool.h>
#include <stdio.h>

#include <SDL2/SDL.h>

typedef struct
{
    bool quit;
} Keys;


void handle_keyboard(Keys *keys);


int main(void)
{
    // Game Config
    const unsigned int window_width = 1280;
    const unsigned int window_height = 720;

    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        printf("[*] SDL Failed to start...\n[*] Exiting...\n");
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow(
        "SDL Fighter",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        window_width,
        window_height,
        0
    );
    if(!window)
    {
        printf("[*] Failed to create window...\n[*] Exiting...\n");
        return 1;
    }


    Uint32 render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, render_flags);
    if(!renderer)
    {
        printf("[*] Failed to create renderer...\n[*] Exiting...\n");
        return 1;
    }

    // Game Init
    Keys keys = {false};

    // Game Loop
    while (1)
    {
        handle_keyboard(&keys);

        if (keys.quit)
        {
            break;
        }

        // Clear Background
        SDL_SetRenderDrawColor(renderer, 96, 128, 255, 255);
        SDL_RenderClear(renderer);

        // Flip front and back buffers
        SDL_RenderPresent(renderer);

        //
        SDL_Delay(16);
    }

    // Cleanup
    SDL_DestroyWindow(window);

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
        }
    }

    return;
}
