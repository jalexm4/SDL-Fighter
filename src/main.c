//
//
//

#include <stdbool.h>
#include <stdio.h>
#include <time.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

#include "../include/audio.h"
#include "../include/background.h"
#include "../include/bullets.h"
#include "../include/collision.h"
#include "../include/enemies.h"
#include "../include/game.h"
#include "../include/init.h"
#include "../include/input.h"
#include "../include/player.h"


int main(void)
{
    // Seed PRNG
    srand(time(NULL));

    // Game Config
    Game game;

    game.window_width = 1280;
    game.window_height = 720;

    game.delta_time = 0.0;
    game.last_frame_time = 0;
    game.fps = 0;
    game.frame_counter = 0;
    game.frame_time = 0.0;

    game.bg_music = NULL;

    if (init_sdl(&game))
    {
        printf("[*] Exiting...\n");
        return 1;
    }

    // Game Entities Setup
    Keys keys = {false, false, false, false, false, false};

    Player player;
    setup_player(&player, &game);

    EnemyContainer enemy_container;
    setup_enemies(&enemy_container, &game);

    load_music(&game, "assets/audio/bg_music.ogg");

    Background background;
    background.texture = IMG_LoadTexture(game.renderer, "assets/background.png");
    background.x_shift = 0;

    setup_starfield(background.stars, &game);

    // Start background music
    Mix_PlayMusic(game.bg_music, -1);

    // --- Game Loop ---
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

        // --- Update Entities ---

        update_player(&player, &game, &enemy_container);
        update_enemies(&enemy_container, &game, &player);

        update_background(&background, &game);

        // --- Render ---

        // Clear previous frame
        SDL_RenderClear(game.renderer);

        render_background(&background, &game);

        render_player(&player, &game);
        render_enemies(&enemy_container, &game);

        // Flip front and back buffers
        SDL_RenderPresent(game.renderer);

        // --- FPS ---

        game.frame_counter++;
        game.frame_time += game.delta_time;

        // Second has passed
        if (game.frame_time > 1.0)
        {
            game.fps = game.frame_counter / game.frame_time;
            game.frame_counter = 0;
            game.frame_time = 0;

            printf("[*] %i FPS\n", game.fps);
        }
    }

    // --- Cleanup ---

    bullet_free_vector(player.bullets);
    bullet_free_vector(enemy_container.bullets);
    enemy_free_vector(enemy_container.enemies);

    SDL_DestroyTexture(background.texture);
    SDL_DestroyTexture(player.texture);
    SDL_DestroyTexture(enemy_container.config.texture);
    SDL_DestroyTexture(player.bullet_texture);
    SDL_DestroyTexture(enemy_container.config.bullet_texture);

    Mix_FreeMusic(game.bg_music);

    Mix_CloseAudio();

    SDL_DestroyWindow(game.window);
    SDL_DestroyRenderer(game.renderer);

    // Terminate SDL
    Mix_Quit();
    IMG_Quit();
    SDL_Quit();

    return 0;
}


