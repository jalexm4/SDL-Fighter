//
//
//

#include <stdbool.h>
#include <stdio.h>
#include <time.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

#include <game/audio.h>
#include <game/background.h>
#include <game/bullets.h>
#include <game/collision.h>
#include <game/enemies.h>
#include <game/game.h>
#include <game/hud.h>
#include <game/init.h>
#include <game/input.h>
#include <game/player.h>
#include <game/scores.h>
#include <game/vfx.h>
#include <vector/vector.h>


Game *setup_game_config(void)
{
    Game *game = malloc(sizeof(Game));
    if (!game)
    {
        printf("[*] Failed to allocate %lu bytes\n", sizeof(Game));
        return game;
    }

    game->window_width = 1280;
    game->window_height = 720;

    game->score = 0;
    game->score_changed = false;
    game->highscore = 0;
    game->delta_time = 0.0f;
    game->last_frame_time = 0;
    game->fps = 0;
    game->frame_counter = 0;
    game->frame_time = 0.0f;

    game->bg_music = NULL;

    game->reset = false;

    return game;
}

int main(void)
{
    // Seed PRNG
    srand(time(NULL));

    // Game Config
    Game *game = setup_game_config();
    if (!game)
    {
        printf("[*] Exiting...\n");
        return 1;
    }

    if (init_sdl(game))
    {
        printf("[*] Exiting...\n");
        return 1;
    }

    // Game Entities Setup
    Keys keys = {false, false, false, false, false, false};

    Player player;
    setup_player(&player, game);

    EnemyContainer enemy_container;
    setup_enemies(&enemy_container, game);

    load_music(game, "assets/audio/bg_music.ogg");

    Background background;
    background.texture = IMG_LoadTexture(game->renderer, "assets/background.png");
    background.x_shift = 0;

    setup_starfield(background.stars, game);

    Explosions explosions;
    explosions.texture = IMG_LoadTexture(game->renderer, "assets/explosion.png");;
    SDL_QueryTexture(explosions.texture, NULL, NULL, &explosions.width, &explosions.height);
    explosions.vector = vector_create(10);

    Hud hud;
    hud.texture = IMG_LoadTexture(game->renderer, "assets/font.png");
    SDL_QueryTexture(hud.texture, NULL, NULL, &hud.width, &hud.height);
    sprintf(hud.score, "SCORE: 000");
    sprintf(hud.highscore, "HIGH SCORE: 000");
    sprintf(hud.fps, "FPS: 0");

    // Start background music
    Mix_PlayMusic(game->bg_music, -1);
    Mix_VolumeMusic(32);

    // --- Game Loop ---
    while (1)
    {
        // Deltatime for current frame
        game->delta_time = (SDL_GetTicks() - game->last_frame_time) / 1000.0f;
        game->last_frame_time = SDL_GetTicks();

        // Respond to users keyboard input
        handle_keyboard(&keys);

        if (keys.quit)
        {
            break;
        }

        process_input(&keys, &player);

        // --- Update Entities ---

        update_player(&player, game, &enemy_container, explosions.vector);
        update_enemies(&enemy_container, game, &player);

        // Check if game should reset
        if (game->reset)
        {
            game->reset = false;

            reset_player(game, &player);
            reset_enemies(&enemy_container);
            reset_explosions(&explosions);

            // Reset score
            game->score = 0;
            sprintf(hud.score, "SCORE: 000");

            // Present user with highscores
            trap_highscores_view(game, &keys, &background, &hud);

            continue;
        }

        update_background(&background, game);
        update_explosions(&explosions);

        update_hud(game, &hud);

        // --- Render ---

        // Clear previous frame
        SDL_RenderClear(game->renderer);

        render_background(&background, game);
        render_explosions(game, &explosions);

        render_player(&player, game);
        render_enemies(&enemy_container, game);

        render_hud(game, &hud);

        // Flip front and back buffers
        SDL_RenderPresent(game->renderer);

        // --- FPS ---

        game->frame_counter++;
        game->frame_time += game->delta_time;

        // Second has passed
        if (game->frame_time > 1.0)
        {
            game->fps = game->frame_counter / game->frame_time;
            game->frame_counter = 0;
            game->frame_time = 0;

            update_hud_fps(game, &hud);

            // printf("[*] %i FPS\n", game->fps);
        }
    }

    // --- Cleanup ---

    // Free datastructures
    vector_free(player.bullets);
    vector_free(enemy_container.bullets);
    vector_free(enemy_container.vector);
    vector_free(explosions.vector);

    // Free Textures
    SDL_DestroyTexture(background.texture);
    SDL_DestroyTexture(player.texture);
    SDL_DestroyTexture(enemy_container.config.texture);
    SDL_DestroyTexture(player.bullet_texture);
    SDL_DestroyTexture(enemy_container.config.bullet_texture);
    SDL_DestroyTexture(explosions.texture);
    SDL_DestroyTexture(hud.texture);

    // Free audio
    Mix_FreeMusic(game->bg_music);
    Mix_FreeChunk(player.sounds[PLAYER_FIRE]);
    Mix_FreeChunk(player.sounds[PLAYER_DIE]);
    Mix_FreeChunk(enemy_container.sounds[ENEMY_FIRE]);
    Mix_FreeChunk(enemy_container.sounds[ENEMY_DIE]);

    Mix_CloseAudio();

    // Free window
    SDL_DestroyWindow(game->window);
    SDL_DestroyRenderer(game->renderer);

    free(game);

    // Terminate SDL
    Mix_Quit();
    IMG_Quit();
    SDL_Quit();

    return 0;
}


