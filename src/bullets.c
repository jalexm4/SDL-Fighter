//
//
//

#include <stdio.h>
#include <stdlib.h>

#include "../include/bullets.h"


BulletVector *bullet_create_vector()
{
    // Allocate data for a vector
    BulletVector *vector = malloc(sizeof(BulletVector));
    if (vector == NULL)
    {
        printf("[*] Unable to allocate memory\n");
        return NULL;
    }

    // Allocate room for 10 bullets
    vector->data = malloc(10 * sizeof(Bullet));
    if (vector->data == NULL)
    {
        printf("[*] Unable to allocate memory\n");
        return NULL;
    }

    vector->size = 0;        // No bullest to start with
    vector->capacity = 10;   // Can hold 10 bullets without resizing

    return vector;
}

void bullet_free_vector(BulletVector *vector)
{
    free(vector->data);
    free(vector);

    return;
}

void bullet_resize_vector(BulletVector *vector)
{
    // Double vector capacity
    vector->capacity *= 2;

    vector->data = realloc(vector->data, vector->capacity * sizeof(BulletVector));
    if (vector->data == NULL)
    {
        printf("[*] Unable to allocate memory\n");
    }

    return;
}

void bullet_push_back(BulletVector *vector, Bullet bullet)
{
    // Resize vector if needed
    if (vector->size == vector->capacity)
    {
        bullet_resize_vector(vector);
    }

    // Place data into the vector
    vector->data[vector->size++] = bullet;

    return;
}

Bullet *bullet_get(BulletVector *vector, int index)
{
    return &(vector->data[index]);
}

void bullet_remove(BulletVector *vector, int index)
{
    // Shift Vector
    for (unsigned int i = index; i < vector->size - 1; i++)
    {
        vector->data[i] = vector->data[i + 1];
    }

    vector->size--;

    return;
}
