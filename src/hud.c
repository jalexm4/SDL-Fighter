//
//
//

#include <SDL2/SDL.h>

#include "../include/game.h"
#include "../include/hud.h"


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
    render_text(game, hud, 10, 10, 255, 255, 255, hud->score);

    if (game->score > 0 && game->score == game->highscore)
    {
        render_text(game, hud, 960, 10, 0, 255, 0, hud->highscore);
    }
    else
    {
        render_text(game, hud, 960, 10, 255, 255, 255, hud->highscore);
    }


    return;
}
