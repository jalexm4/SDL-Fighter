//
//
//

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../include/bullets.h"
#include "../include/collision.h"
#include "../include/enemies.h"
#include "../include/game.h"
#include "../include/player.h"


static void detect_enemy_bounds_collision(EnemyContainer *container)
{
    for (int i = 0, n = container->enemies->size; i < n; i++)
    {
        Enemy *enemy = enemy_get(container->enemies, i);
        if (enemy->x + container->config.width < 0)
        {
            enemy_remove(container->enemies, i);
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
    container->config.max = 5;
    container->config.default_health = 1;
    container->config.bullet_speed = -10;

    container->enemies = enemy_create_vector();
    container->bullets = bullet_create_vector();

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

        // New enemy preset
        Enemy new_enemy;
        new_enemy.x = game->window_width;
        new_enemy.y = rand() % game->window_height;
        new_enemy.x_velocity = -(2 + (rand() % 4));
        new_enemy.health = container->config.default_health;
        new_enemy.attack_timer = 100;

        enemy_push_back(container->enemies, new_enemy);
    }
    else
    {
        container->config.respawn_timer--;
    }

    // Update Enemy POS and attack
    for (int i = 0, n = container->enemies->size; i < n; i++)
    {
        Enemy *enemy = enemy_get(container->enemies, i);
        enemy->x += enemy->x_velocity;
        enemy->attack_timer--;

        // Enemy is attacking - Add a new bullet.
        if (enemy->attack_timer <= 0)
        {
            // Reset current enemies attack timer
            enemy->attack_timer = 100;

            //TODO: Calculate slope between enemy and player to fire bullet at player
            Bullet new_bullet;
            new_bullet.x = enemy->x;
            new_bullet.y = enemy->y + (container->config.height / 2) - (container->config.bullet_height / 2);

            bullet_push_back(container->bullets, new_bullet);
        }
    }

    // Update Enemy Bullets
    for (int i = 0, n = container->bullets->size; i < n; i++)
    {
        Bullet *bullet = bullet_get(container->bullets, i);
        bullet->x += container->config.bullet_speed;

        // Destroy any bullets that leave left side of the window
        if (bullet->x <= 0)
        {
            bullet_remove(container->bullets, i);
        }

        //
        if (aabb_collision_detection(player->x, player->y, player->w, player->h, bullet->x, bullet->y, container->config.bullet_width, container->config.bullet_height))
        {
            bullet_remove(container->bullets, i);

            //TODO: Player health
        }
    }

    return;
}

void render_enemies(EnemyContainer *container, Game *game)
{
    // Render enemies
    for (int i = 0, n = container->enemies->size; i < n; i++)
    {
        Enemy *enemy = enemy_get(container->enemies, i);

        SDL_Rect enemy_rect = {enemy->x, enemy->y, container->config.width, container->config.height};
        SDL_RenderCopy(game->renderer, container->config.texture, NULL, &enemy_rect);
    }

    // Render enemies bullets
    for (int i = 0, n = container->bullets->size; i < n; i++)
    {
        Bullet *bullet = bullet_get(container->bullets, i);

        SDL_Rect bullet_rect = {bullet->x, bullet->y, container->config.bullet_width, container->config.bullet_height};
        SDL_RenderCopy(game->renderer, container->config.bullet_texture, NULL, &bullet_rect);
    }

    return;
}


EnemyVector *enemy_create_vector()
{
    // Allocate data for a vector
    EnemyVector *vector = malloc(sizeof(EnemyVector));
    if (vector == NULL)
    {
        printf("[*] Unable to allocate memory\n");
        return NULL;
    }

    // Allocate room for 10 enemies
    vector->data = malloc(10 * sizeof(Enemy));
    if (vector->data == NULL)
    {
        printf("[*] Unable to allocate memory\n");
        return NULL;
    }

    vector->size = 0;        // No bullest to start with
    vector->capacity = 10;   // Can hold 10 bullets without resizing

    return vector;
}

void enemy_free_vector(EnemyVector *vector)
{
    free(vector->data);
    free(vector);

    return;
}

void enemy_resize_vector(EnemyVector *vector)
{
    // Double vector capacity
    vector->capacity *= 2;

    vector->data = realloc(vector->data, vector->capacity * sizeof(EnemyVector));
    if (vector->data == NULL)
    {
        printf("[*] Unable to allocate memory\n");
    }

    return;
}

void enemy_push_back(EnemyVector *vector, Enemy enemy)
{
    // Resize vector if needed
    if (vector->size == vector->capacity)
    {
        enemy_resize_vector(vector);
    }

    // Place data into the vector
    vector->data[vector->size++] = enemy;

    return;
}

Enemy *enemy_get(EnemyVector *vector, int index)
{
    return &(vector->data[index]);
}


void enemy_remove(EnemyVector *vector, int index)
{
    // Shift Vector
    for (unsigned int i = index; i < vector->size - 1; i++)
    {
        vector->data[i] = vector->data[i + 1];
    }

    vector->size--;

    return;
}
