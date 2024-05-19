//
//
//

#include <stdbool.h>

#include "../include/collision.h"


// Axis-Aligned Bounding Box Collision Detection Algorithm
// https://developer.mozilla.org/en-US/docs/Games/Techniques/2D_collision_detection
//TODO: Refactor - Don't like the function arguments.
bool aabb_collision_detection(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2)
{
    return (x1 < x2 + w2) && (x1 + w1 > x2) && (y1 < y2 + h2) && (y1 + h1 > y2);
}
