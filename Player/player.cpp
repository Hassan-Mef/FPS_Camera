#include "player.h"

Player InitPlayer()
{
    Player p = {0};

    p.position = {0.0f, 2.0f, 4.0f};

    p.camera.position = p.position;
    p.camera.target = {0.0f, 2.0f, 0.0f};
    p.camera.up = {0.0f, 1.0f, 0.0f};
    p.camera.fovy = 60;
    p.camera.projection = CAMERA_PERSPECTIVE;

    p.moveSpeed = 8.0f;
    p.jumpForce = 28.0f;
    p.gravity = 20.0f;

    p.isGrounded = true;

    p.yaw = -90.0f;
    p.pitch = 0.0f;

    return p;
}

void UpdatePlayer(Player &player, float dt)
{

    // Mouse look 

    Vector2 mouseDelta = GetMouseDelta();

    // testing
    // std::cout << mouseDelta.x << " " << mouseDelta.y << std::endl;

    float sensitivity = 0.1f;

    player.yaw += mouseDelta.x * sensitivity;
    player.pitch -= mouseDelta.y * sensitivity;  // -Y because the mouse is inverted


    // prevent camera flip

    if (player.pitch > 89.0f) player.pitch = 89.0f;
    if (player.pitch < -89.0f) player.pitch = -89.0f;

    // converting angle into vector 

    Vector3 direction;

    direction.x = cosf(DEG2RAD * player.yaw) * cosf(DEG2RAD * player.pitch);
    direction.y = sinf(DEG2RAD * player.pitch);
    direction.z = sinf(DEG2RAD * player.yaw) * cosf(DEG2RAD * player.pitch);

    

    // update camera target
    player.camera.target = Vector3Add(player.position, direction);

    

    // Sync camera with player position
    player.camera.position = player.position;

    // Movement input
    Vector3 forward = { direction.x, 0.0f, direction.z };
    forward = Vector3Normalize(forward);

    Vector3 right = Vector3CrossProduct(forward, {0.0f,1.0f,0.0f});
    right = Vector3Normalize(right);

    float speed = player.moveSpeed * dt;

    if (IsKeyDown(KEY_W))
    {
        player.position = Vector3Add(player.position, Vector3Scale(forward, speed));
    }

    if (IsKeyDown(KEY_S))
    {
        player.position = Vector3Subtract(player.position, Vector3Scale(forward, speed));
    }

    if (IsKeyDown(KEY_D))
    {
        player.position = Vector3Add(player.position, Vector3Scale(right, speed));
    }

    if (IsKeyDown(KEY_A))
    {
        player.position = Vector3Subtract(player.position, Vector3Scale(right, speed));
    }


    // Apply gravity
    if (!player.isGrounded)
    {
        player.position.y -= player.gravity * dt;
    }

    // Jump input
    if (IsKeyPressed(KEY_SPACE) && player.isGrounded)
    {
        player.position.y += player.jumpForce * dt;
        player.isGrounded = false;
    }

    // Simple ground collision
    if (player.position.y <= 2.0f)
    {
        player.position.y = 2.0f;
        player.isGrounded = true;
    }

    // // Sync camera with player position
    // player.camera.position = player.position;
}