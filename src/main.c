//
//
//

#include <stdbool.h>
#include <stdio.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../include/collision.h"
#include "../include/enemies.h"
#include "../include/game.h"
#include "../include/init.h"
#include "../include/input.h"
#include "../include/player.h"


int main(void)
{
    // Game Config
    Game game;

    game.window_width = 1280;
    game.window_height = 720;

    game.delta_time = 0.0;
    game.last_frame_time = 0;
    game.fps = 60;
    game.frame_counter = 0;
    game.frame_time = 0.0;

    if (init_sdl(&game))
    {
        printf("[*] Exiting...\n");
        return 1;
    }

    // Game Init
    Keys keys = {false, false, false, false, false, false};

    Player player;
    setup_player(&player, &game);

    EnemyContainer enemy_container;
    setup_enemies(&enemy_container, &game);

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

        // Stop player from leaving window
        detect_player_bounds_collision(&player, &game);

        // Remove enemies that have left window
        detect_enemy_bounds_collision(&enemy_container);

        // Reload timer
        if (player.reload > 0)
        {
            player.reload--;
        }

        // Update Player POS
        player.x += player.x_velocity * game.delta_time;
        player.y += player.y_velocity * game.delta_time;

        // Add new enemies to screen
        if (enemy_container.config.respawn_timer <= 0 && enemy_container.config.alive < enemy_container.config.max)
        {
            enemy_container.config.respawn_timer = 30 + (rand() % 60);
            enemy_container.config.alive++;

            Enemy new_enemy;
            new_enemy.x = game.window_width;
            new_enemy.y = rand() % game.window_height;
            new_enemy.x_velocity = -(2 + (rand() % 4));

            enemy_push_back(enemy_container.enemies, new_enemy);
        }
        else
        {
            enemy_container.config.respawn_timer--;
        }

        // Update Enemy POS
        for (int i = 0, n = enemy_container.enemies->size; i < n; i++)
        {
            Enemy *enemy = enemy_get(enemy_container.enemies, i);
            enemy->x += enemy->x_velocity;
        }

        // Update Player bullets
        for (int i = 0, n = player.bullets->size; i < n; i++)
        {
            Bullet *bullet = bullet_get(player.bullets, i);

            // Update player bullet positions
            bullet->x += player.bullets->speed;

            // Check if bullets leave screen
            if (bullet->x >= game.window_width)
            {
                bullet_remove(player.bullets, i);
                continue;
            }

            // Check AABB of bullet to each enemy
            for (int j = 0, enemy_size = enemy_container.enemies->size; j < enemy_size; j++)
            {
                Enemy *enemy = enemy_get(enemy_container.enemies, j);

                //TODO: Refactor - Don't like the function arguments.
                if (aabb_collision_detection(bullet->x, bullet->y, player.bullets->width, player.bullets->height, enemy->x, enemy->y, enemy_container.config.width, enemy_container.config.height))
                {
                    // Remove collided enemy and bullet
                    bullet_remove(player.bullets, i);
                    enemy_remove(enemy_container.enemies, j);

                    break;
                }
            }
        }

        // --- Render ---

        // Clear previous frame and set background colour
        SDL_SetRenderDrawColor(game.renderer, 96, 128, 255, 255);
        SDL_RenderClear(game.renderer);

        render_enemies(&enemy_container, &game);
        render_player(&player, &game);

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

    printf("[*] Freeing %i bullets from player\n", player.bullets->size);
    printf("[*] Freeing %i enemies\n", enemy_container.enemies->size);
    bullet_free_vector(player.bullets);
    enemy_free_vector(enemy_container.enemies);

    SDL_DestroyTexture(player.texture);
    SDL_DestroyTexture(enemy_container.config.texture);

    SDL_DestroyWindow(game.window);
    SDL_DestroyRenderer(game.renderer);

    // Terminate SDL
    SDL_Quit();

    return 0;
}


