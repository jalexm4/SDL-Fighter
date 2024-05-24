//
//
//

#include <SDL2/SDL.h>

#include "../include/background.h"
#include "../include/game.h"


void update_background(Background *background, Game *game)
{
    // Shift background to the left
    background->x_shift += -10;

    // Reset shift
    if (background->x_shift <= -game->window_width)
    {
        background->x_shift = 0;
    }

    return;
}

void render_background(Background *background, Game *game)
{
    SDL_Rect bg_rect;

    // Render background until full window is covered
    for (int x = background->x_shift; x < game->window_width; x += game->window_width)
    {
        bg_rect.x = x;
        bg_rect.y = 0;
        bg_rect.w = game->window_width;
        bg_rect.h = game->window_height;

        SDL_RenderCopy(game->renderer, background->texture, NULL, &bg_rect);
    }

    return;
}
