//
//
//

#include <background.h>
#include <game.h>
#include <hud.h>
#include <input.h>
#include <scores.h>

void trap_highscores_view(Game *game, Keys *keys, Background *background, Hud *hud)
{
    clear_input(keys);

    char highscore_entry[21];

    while (1)
    {
        handle_keyboard(keys);

        //
        if (keys->quit || keys->fire)
        {
            clear_input(keys);
            break;
        }

        SDL_RenderClear(game->renderer);

        render_background(background, game);

        // Render Highscores
        render_text(game, hud, 425, 70, 255, 255, 255, "HIGHSCORES");

        //TODO: Track a highscore table
        int y = 150;
        for (int i = 0; i < 8; i++)
        {
            sprintf(highscore_entry, "#%d ............. %03d", i + 1, 0);
            render_text(game, hud, 425, y, 255, 255, 255, highscore_entry);

            y += 50;
        }

        SDL_RenderPresent(game->renderer);
    }

    return;
}
