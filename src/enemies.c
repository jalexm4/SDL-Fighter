//
//
//

#include <stdio.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <game/audio.h>
#include <game/collision.h>
#include <game/enemies.h>
#include <game/game.h>
#include <game/player.h>
#include <vector/vector.h>


static void detect_enemy_bounds_collision(EnemyContainer *container)
{
    for (size_t i = 0, n = container->vector->size; i < n; i++)
    {
        // Enemy *enemy = enemy_get(container->enemies, i);
        Enemy *enemy = vector_get(container->vector, i);
        if (enemy->x + container->config.width < 0)
        {
            // enemy_remove(container->enemies, i);
            vector_remove(container->vector, i);
            container->config.alive--;
        }
    }

    return;
}

void setup_enemies(EnemyContainer *container, Game *game)
{
    container->config.texture = IMG_LoadTexture(game->renderer, "assets/enemy.png");
    SDL_QueryTexture(container->config.texture, NULL, NULL, &container->config.width, &container->config.height);

    container->config.bullet_texture = IMG_LoadTexture(game->renderer, "assets/enemy_bullet.png");
    SDL_QueryTexture(container->config.bullet_texture, NULL, NULL, &container->config.bullet_width, &container->config.bullet_height);

    container->config.respawn_timer = -1;
    container->config.alive = 0;
    container->config.max = 3;
    container->config.default_health = 1;
    container->config.bullet_speed = -10;

    // container->enemies = enemy_create_vector();
    container->vector = vector_create(10);
    container->bullets = vector_create(10);
    // container->bullets = bullet_create_vector();

    container->sounds[ENEMY_FIRE] = Mix_LoadWAV("assets/audio/alien_fire.ogg");
    container->sounds[ENEMY_DIE] = Mix_LoadWAV("assets/audio/alien_die.ogg");

    return;
}

void update_enemies(EnemyContainer *container, Game *game, Player *player)
{
    // Kill any enemy that has left the window
    detect_enemy_bounds_collision(container);

    // Spawn new enemies
    if (container->config.respawn_timer <= 0 && container->config.alive < container->config.max)
    {
        // Reset respawn timer
        container->config.respawn_timer = 30 + (rand() % 60);

        // Number of enemies currently active
        container->config.alive++;

        Enemy *new_enemy = malloc(sizeof(Enemy));
        new_enemy->x = game->window_width;
        new_enemy->y = rand() % game->window_height;
        new_enemy->x_velocity = -(2 + (rand() % 4));
        new_enemy->health = container->config.default_health;
        new_enemy->attack_timer = 100;

        vector_push_back(container->vector, new_enemy);
    }
    else
    {
        container->config.respawn_timer--;
    }

    // Update Enemy POS and attack
    for (size_t i = 0, n = container->vector->size; i < n; i++)
    {
        Enemy *enemy = vector_get(container->vector, i);

        enemy->x += enemy->x_velocity;
        enemy->attack_timer--;

        // Enemy is attacking - Add a new bullet.
        if (enemy->attack_timer <= 0)
        {
            // Reset current enemies attack timer
            enemy->attack_timer = 100;

            //TODO: Calculate slope between enemy and player to fire bullet at player
            // Bullet new_bullet;
            // new_bullet.x = enemy->x;
            // new_bullet.y = enemy->y + (container->config.height / 2) - (container->config.bullet_height / 2);

            Bullet *new_bullet = malloc(sizeof(Bullet));
            new_bullet->x = enemy->x;
            new_bullet->y = enemy->y + (container->config.height / 2) - (container->config.bullet_height / 2);

            // bullet_push_back(container->bullets, new_bullet);
            vector_push_back(container->bullets, new_bullet);

            play_sfx(container->sounds[ENEMY_FIRE], CH_ENEMY_FIRE);
        }
    }

    // Update Enemy Bullets
    for (int i = 0, n = container->bullets->size; i < n; i++)
    {
        // Bullet *bullet = bullet_get(container->bullets, i);

        Bullet *bullet = vector_get(container->bullets, i);

        bullet->x += container->config.bullet_speed;

        // Destroy any bullets that leave left side of the window
        if (bullet->x <= 0)
        {
            // bullet_remove(container->bullets, i);
            vector_remove(container->bullets, i);
        }

        // Player hit
        if (aabb_collision_detection(player->x, player->y, player->w, player->h, bullet->x, bullet->y, container->config.bullet_width, container->config.bullet_height))
        {
            // bullet_remove(container->bullets, i);
            vector_remove(container->bullets, i);

            player->health--;

            // Player died
            if (player->health <= 0)
            {
                //TODO: Show player death effect then reset
                game->reset = true;

                play_sfx(player->sounds[PLAYER_DIE], CH_PLAYER_DIE);
            }
        }
    }

    return;
}

void reset_enemies(EnemyContainer *container)
{
    // bullet_free_vector(container->bullets);
    vector_free(container->bullets);
    vector_free(container->vector);

    // container->bullets = bullet_create_vector();
    container->bullets = vector_create(10);
    container->vector = vector_create(10);

    container->config.alive = 0;

    return;
}

void render_enemies(EnemyContainer *container, Game *game)
{
    // Render enemies
    for (size_t i = 0, n = container->vector->size; i < n; i++)
    {
        Enemy *enemy = vector_get(container->vector, i);

        SDL_Rect enemy_rect = {enemy->x, enemy->y, container->config.width, container->config.height};
        SDL_RenderCopy(game->renderer, container->config.texture, NULL, &enemy_rect);
    }

    // Render enemies bullets
    for (int i = 0, n = container->bullets->size; i < n; i++)
    {
        // Bullet *bullet = bullet_get(container->bullets, i);
        Bullet *bullet = vector_get(container->bullets, i);

        SDL_Rect bullet_rect = {bullet->x, bullet->y, container->config.bullet_width, container->config.bullet_height};
        SDL_RenderCopy(game->renderer, container->config.bullet_texture, NULL, &bullet_rect);
    }

    return;
}
