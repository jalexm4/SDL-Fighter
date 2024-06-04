//
//
//

#include <stdio.h>
#include <string.h>

#include <SDL2/SDL.h>

#include <game/game.h>
#include <game/hud.h>


void update_hud(Game *game, Hud *hud)
{
    // Only regenerate score string if the scoring as changed.
    if (game->score_changed)
    {
        game->score_changed = false;

        char score[4];

        // Update player score
        sprintf(score, "%03d", game->score);

        for (int i = 0; i < 3; i++)
        {
            hud->score[7 + i] = score[i];
        }

        // Update highscore
        sprintf(score, "%03d", game->highscore);

        for (int i = 0; i < 3; i++)
        {
            hud->highscore[12 + i] = score[i];
        }
    }


    return;
}

void update_hud_fps(Game *game, Hud *hud)
{
    char fps[4];
    sprintf(fps, "%d", game->fps);

    for (int i = 0; i < 3; i++)
    {
        hud->fps[5 + i] = fps[i];
    }

    return;
}

void render_text(Game *game, Hud *hud, int x, int y, int r, int g, int b, char *text)
{
    SDL_SetTextureColorMod(hud->texture, r, g, b);

    SDL_Rect src_rect = {0, 0, GLYPH_WIDTH, GLYPH_HEIGHT};

    int c;

    for (int i = 0, length = strlen(text); i < length; i++)
    {
        c = text[i];

        if (c >= ' ' && c <= 'Z')
        {
            src_rect.x = (c - ' ') * GLYPH_WIDTH;

            SDL_Rect dst_rect = {x, y, src_rect.w, src_rect.h};
            SDL_RenderCopy(game->renderer, hud->texture, &src_rect, &dst_rect);

            x += GLYPH_WIDTH;
        }
    }

    return;
}

void render_hud(Game *game, Hud *hud)
{
    // Render Current Score
    render_text(game, hud, 10, 10, 255, 255, 255, hud->score);

    // Render Top Highscore
    if (game->score > 0 && game->score == game->highscore)
    {
        render_text(game, hud, 960, 10, 0, 255, 0, hud->highscore);
    }
    else
    {
        render_text(game, hud, 960, 10, 255, 255, 255, hud->highscore);
    }


    // Render FPS Counter
    render_text(game, hud, game->window_width - 150, game->window_height - 50, 255, 0, 0, hud->fps);


    return;
}
