//
//
//

#include <SDL2/SDL.h>

#include "../include/game.h"
#include "../include/player.h"


void process_input(Keys *keys, Player *player)
{
    // --- Player Movement ---
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

    // --- Player Attacks ---
    if (keys->fire && player->reload == 0)
    {
        Bullet bullet = {player->x, player->y + (player->h / 2) - (player->bullet_height / 2)};
        bullet_push_back(player->bullets, bullet);

        player->reload = 16;
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
