#ifndef GROUND_H
#define GROUND_H

#include "raylib.h"

static inline void DrawGround()
{
    DrawPlane((Vector3){ 0.0f, 0.0f, 0.0f }, (Vector2){ 100.0f, 100.0f }, LIGHTGRAY);
}


#endif // GROUND_H