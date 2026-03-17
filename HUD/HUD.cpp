#include "HUD.h"

void DrawMovementSpeed(float speed)
{
    DrawText(TextFormat("Speed: %.2f", speed), 10, 10, 20, WHITE);
}