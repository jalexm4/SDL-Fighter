#pragma once


typedef struct
{
    int x;
    int y;
} Bullet;

// Vector of Bullets
typedef struct
{
    Bullet *data;
    unsigned int size;
    unsigned int capacity;
} BulletVector;


BulletVector *bullet_create_vector();
void bullet_free_vector(BulletVector *vector);
void bullet_resize_vector(BulletVector *vector);
void bullet_push_back(BulletVector *vector, Bullet bullet);
Bullet *bullet_get(BulletVector *vector, int index);
void bullet_remove(BulletVector *vector, int index);
