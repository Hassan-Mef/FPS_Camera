#include "raylib.h"

// Screen size
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 450;

int main()
{
    // Initialization
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "My Raylib Game");
    SetTargetFPS(60);

    int x = 340;
    int y = 190;
    int speedY =3;
    int speedX =3;

    int x_tile = 100 ;
    int y_tile = 100 ;

    bool collision_tile = false ;

    // Game Loop
    while (!WindowShouldClose())   // Detect window close button or ESC
    {
        // --- Update ---
        // Put game logic here

         y += speedY;
         x += speedX;

        // Bottom wall
        if (y > SCREEN_HEIGHT - 60)
        {
            y = SCREEN_HEIGHT - 60;
            speedY = -speedY;
        }

        // Top wall
        if (y < 60)
        {
            y = 60;
            speedY = -speedY;
        }

        // Right wall
        if (x > SCREEN_WIDTH - 60)
        {
            x = SCREEN_WIDTH - 60;
            speedX = -speedX;
        }

        // Left wall
        if (x < 60)
        {
            x = 60;
            speedX = -speedX;
        }

        // check for collosion 

        if ( x + 60 > x_tile && x + 60 < x_tile + 100 && y + 60 > y_tile && y - 60 < y_tile + 50 )
        {
            collision_tile = true ;
        }


        // --- Draw ---
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Vector2 test_line_start ;
        // test_line_start.x = 30;
        // test_line_start.y = 100 ;
        
        // Vector2 test_line_end;
        // test_line_end.x = 300;
        // test_line_end.y= 15022;

        // DrawText("Hello, raylib + C++!", 220, 200, 20, DARKGRAY);
        // DrawLine(test_line_start.x , test_line_start.y , test_line_end.x , test_line_end.y , YELLOW);
        
        DrawCircle(x,y, 60, BLUE);

        if(collision_tile)
        {
            DrawText("Collision Detected!", 10, 10, 20, RED);
        }
        else
          DrawRectangle(x_tile, y_tile , 100 , 50 ,RED);

         

        EndDrawing();
    }

    // De-initialization
    CloseWindow();

    return 0;
}
