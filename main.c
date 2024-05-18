//
//
//

#include <stdbool.h>
#include <stdio.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

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

typedef struct
{
    int x, y, w, h;
    int x_velocity;
    int y_velocity;
    int speed;

    SDL_Texture *texture;
} Player;


void process_input(Keys *keys, Player *player);
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
    Keys keys = {false, false, false, false, false, false};

    Player player;
    player.texture = IMG_LoadTexture(game.renderer, "assets/player.png");
    player.x = 100;
    player.y = 100;
    SDL_QueryTexture(player.texture, NULL, NULL, &player.w, &player.h);
    player.x_velocity = 0;
    player.y_velocity = 0;
    player.speed = 500;

    // Game Loop
    while (1)
    {
        // Deltatime for current frame
        game.delta_time = (SDL_GetTicks() - game.last_frame_time) / 1000.0f;
        game.last_frame_time = SDL_GetTicks();

        // Respond to users keyboard input
        handle_keyboard(&keys);

        if (keys.quit)
        {
            break;
        }

        process_input(&keys, &player);

        // --- Collision Detection ---

        // Stop player from leaving left or right side of the window
        int player_x_movement = player.x_velocity * game.delta_time;
        if (player.x + player_x_movement < 0 || (player.x + player.w) + player_x_movement > game.window_width)
        {
            player.x_velocity = 0;
        }

        // Stop player from leaving top or bottom side of the window
        int player_y_movement = player.y_velocity * game.delta_time;
        if (player.y + player_y_movement < 0 || (player.y + player.h) + player_y_movement > game.window_height)
        {
            player.y_velocity = 0;
        }

        // --- Update entities ---

        // Update Player POS
        player.x += player.x_velocity * game.delta_time;
        player.y += player.y_velocity * game.delta_time;

        // --- Render ---

        // Clear previous frame and set background colour
        SDL_SetRenderDrawColor(game.renderer, 96, 128, 255, 255);
        SDL_RenderClear(game.renderer);

        // Render Player
        SDL_Rect player_rect = {player.x, player.y, player.w, player.h};
        SDL_RenderCopy(game.renderer, player.texture, NULL, &player_rect);

        // Flip front and back buffers
        SDL_RenderPresent(game.renderer);
    }

    // --- Cleanup ---

    SDL_DestroyTexture(player.texture);

    SDL_DestroyWindow(game.window);
    SDL_DestroyRenderer(game.renderer);

    // Terminate SDL
    SDL_Quit();

    return 0;
}

void process_input(Keys *keys, Player *player)
{
    if (keys->up && !keys->down)
    {
        player->y_velocity = -player->speed;
    }
    else if (keys->down && !keys->up)
    {
        player->y_velocity = player->speed;
    }
    else
    {
        player->y_velocity = 0;
    }

    if (keys->left && !keys->right)
    {
        player->x_velocity = -player->speed;
    }
    else if (keys->right && !keys->left)
    {
        player->x_velocity = player->speed;
    }
    else
    {
        player->x_velocity = 0;
    }

    return;
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

            case SDL_KEYDOWN:
                if (event.key.repeat == 0)
                {
                    switch (event.key.keysym.scancode)
                    {
                        case SDL_SCANCODE_W:
                            keys->up = true;
                            break;
                        case SDL_SCANCODE_S:
                            keys->down = true;
                            break;
                        case SDL_SCANCODE_A:
                            keys->left = true;
                            break;
                        case SDL_SCANCODE_D:
                            keys->right = true;
                            break;
                        case SDL_SCANCODE_X:
                            keys->fire = true;
                            break;
                        case SDL_SCANCODE_ESCAPE:
                            keys->quit = true;
                            break;
                        default:
                            break;
                    }
                }
                break;

            case SDL_KEYUP:
                if (event.key.repeat == 0)
                {
                    switch (event.key.keysym.scancode)
                    {
                        case SDL_SCANCODE_W:
                            keys->up = false;
                            break;
                        case SDL_SCANCODE_S:
                            keys->down = false;
                            break;
                        case SDL_SCANCODE_A:
                            keys->left = false;
                            break;
                        case SDL_SCANCODE_D:
                            keys->right = false;
                            break;
                        case SDL_SCANCODE_X:
                            keys->fire = false;
                            break;
                        default:
                            break;
                    }
                }
                break;

            default:
                break;
        }
    }

    return;
}
