#include <iostream>
#include "raylib.h"
#include "Environment/ground.h"
#include "Player/player.h"
#include "HUD/HUD.h"

int main()
{
    const int screenWidth = 1280;
    const int screenHeight = 700;

    InitWindow(screenWidth, screenHeight, "FPS Camera");

    DisableCursor(); // Hide the cursor for FPS control

    // Camera
    // Camera3D camera = { 0 };
    // camera.position = { 0.0f, 2.0f, 6.0f };   // where camera is
    // camera.target = { 0.0f, 1.0f, 0.0f };     // where camera looks
    // camera.up = { 0.0f, 1.0f, 0.0f };         // up direction
    // camera.fovy = 60.0f;                      // field of view
    // camera.projection = CAMERA_PERSPECTIVE;

    Player player = InitPlayer();

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        //UpdateCamera(&camera, CAMERA_FREE);

        float dt = GetFrameTime();

        UpdatePlayer(player, dt);

        BeginDrawing();

        ClearBackground(SKYBLUE);

        float speed = sqrtf(player.velocity.x * player.velocity.x +
                    player.velocity.z * player.velocity.z);



        BeginMode3D(player.camera);

            //DrawGrid(20, 1.0f);  // temporary ground
            DrawGround();
            DrawCube({0,1,0}, 1,1,1, RED);

            DrawCube({5,1,0}, 1,1,1, BLUE);
            DrawCube({-5,1,0}, 1,1,1, GREEN);
            DrawCube({0,1,5}, 1,1,1, YELLOW);
            

            
        EndMode3D();

        DrawText("3D FPS Camera", 10, 10, 20, BLACK);

        DrawMovementSpeed(speed);

        // crosshair
        DrawLine(screenWidth/2 - 10, screenHeight/2, screenWidth/2 + 10, screenHeight/2, BLACK);
        DrawLine(screenWidth/2, screenHeight/2 - 10, screenWidth/2, screenHeight/2 + 10, BLACK);

        EndDrawing();
    }

    CloseWindow();
}