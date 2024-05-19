//
//
//

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "enemies.h"
#include "game.h"


void setup_enemies(EnemyContainer *container, Game *game)
{
    container->config.texture = IMG_LoadTexture(game->renderer, "assets/enemy.png");
    SDL_QueryTexture(container->config.texture, NULL, NULL, &container->config.width, &container->config.height);

    container->config.respawn_timer = -1;
    container->config.alive = 0;
    container->config.max = 5;

    container->enemies = enemy_create_vector();

    return;
}

void render_enemies(EnemyContainer *container, Game *game)
{
    for (int i = 0, n = container->enemies->size; i < n; i++)
    {
        Enemy *enemy = enemy_get(container->enemies, i);

        SDL_Rect enemy_rect = {enemy->x, enemy->y, container->config.width, container->config.height};
        SDL_RenderCopy(game->renderer, container->config.texture, NULL, &enemy_rect);
    }

    return;
}

void detect_enemy_bounds_collision(EnemyContainer *container)
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
