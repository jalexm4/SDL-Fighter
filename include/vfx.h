#pragma once


typedef struct {
    int x, y;
    int x_velocity, y_velocity;
    int r, g, b, a;
} Explosion;

typedef struct {
    Explosion *data;
    unsigned int size;
    unsigned int capacity;
} ExplosionVector;

typedef struct {
    SDL_Texture *texture;
    int width;
    int height;

    ExplosionVector *vector;
} Explosions;


void update_explosions(Explosions *explosions);
void render_explosions(Game *game, Explosions *explosions);

ExplosionVector *explosion_create_vector(void);
void explosion_free_vector(ExplosionVector *vector);
void explosion_resize_vector(ExplosionVector *vector);
void explosion_push_back(ExplosionVector *vector, Explosion data);
Explosion *explosion_get(ExplosionVector *vector, int index);
void explosion_remove(ExplosionVector *vector, int index);
