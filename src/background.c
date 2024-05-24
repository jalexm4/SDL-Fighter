//
//
//

#include <SDL2/SDL.h>

#include "../include/background.h"
#include "../include/game.h"

static void update_starfield(Star *stars, Game *game)
{
    for (int i = 0; i < 500; i++)
    {
        stars[i].x -= stars[i].speed;

        if (stars[i].x < 0)
        {
            stars[i].x = game->window_width + stars[i].x;
        }
    }

    return;
}

static void render_starfield(Star *stars, Game *game)
{
    int colour = 0;

    for (int i = 0; i < 500; i++)
    {
        colour = 32 * stars[i].speed;

        SDL_SetRenderDrawColor(game->renderer, colour, colour, colour, 255);
        SDL_RenderDrawLine(game->renderer, stars[i].x, stars[i].y, stars[i].x + 3, stars[i].y);
    }

    return;
}

void setup_starfield(Star *stars, Game *game)
{
    for (int i = 0; i < 500; i++)
    {
        stars[i].x = rand() % game->window_width;
        stars[i].y = rand() % game->window_width;
        stars[i].speed = 1 + rand() % 8;
    }

    return;
}


void update_background(Background *background, Game *game)
{
    // Shift background to the left
    background->x_shift += -10;

    // Reset shift
    if (background->x_shift <= -game->window_width)
    {
        background->x_shift = 0;
    }

    //
    update_starfield(background->stars, game);

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

    render_starfield(background->stars, game);

    return;
}
