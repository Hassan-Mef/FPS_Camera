#include "player.h"


Player InitPlayer()
{
    Player p = {0};

    // Player starting position
    p.position = {0.0f, 2.0f, 4.0f};

    // Camera setup
    p.camera.position = p.position;
    p.camera.target = {0.0f, 2.0f, 0.0f};
    p.camera.up = {0.0f, 1.0f, 0.0f};
    p.camera.fovy = 60;
    p.camera.projection = CAMERA_PERSPECTIVE;

    // Movement tuning
    p.moveSpeed = 9.0f;     // base movement strength
    p.jumpForce = 8.0f;    // upward velocity when jumping
    p.gravity = 18.0f;

    // Advanced movement tuning
    p.groundAccel = 50.0f;  // strong control on ground
    p.airAccel = 10.0f;     // weak control in air
    p.friction = 4.0f;      // slowing force on ground

    p.sprint = false;

    p.maxSpeed = 5.0f; // your walking speed target


    p.isGrounded = true;

    // Mouse look
    p.yaw = -90.0f;
    p.pitch = 0.0f;

    return p;
}


void UpdatePlayer(Player &player, float dt)
{
    
    // MOUSE LOOK (where player is looking)

    Vector2 mouseDelta = GetMouseDelta();
    float sensitivity = 0.1f;

    player.yaw   += mouseDelta.x * sensitivity;
    player.pitch -= mouseDelta.y * sensitivity;

    // Prevent flipping
    if (player.pitch > 89.0f) player.pitch = 89.0f;
    if (player.pitch < -89.0f) player.pitch = -89.0f;

    // Convert yaw/pitch -> direction vector
    Vector3 direction;
    direction.x = cosf(DEG2RAD * player.yaw) * cosf(DEG2RAD * player.pitch);
    direction.y = sinf(DEG2RAD * player.pitch);
    direction.z = sinf(DEG2RAD * player.yaw) * cosf(DEG2RAD * player.pitch);

    // Camera follows player
    player.camera.position = player.position;
    player.camera.target = Vector3Add(player.position, direction);


    //  CREATE MOVEMENT DIRECTIONS (forward/right)


    // Ignore Y so player doesn't fly when looking up
    Vector3 forward = { direction.x, 0.0f, direction.z };
    forward = Vector3Normalize(forward);

    Vector3 right = Vector3CrossProduct(forward, {0.0f, 1.0f, 0.0f});
    right = Vector3Normalize(right);

  
    //  INPUT -> "WISH DIRECTION"


    // This combines WASD into ONE direction
    Vector3 wishDir = {0};

    if (IsKeyDown(KEY_W)) wishDir = Vector3Add(wishDir, forward);
    if (IsKeyDown(KEY_S)) wishDir = Vector3Subtract(wishDir, forward);
    if (IsKeyDown(KEY_D)) wishDir = Vector3Add(wishDir, right);
    if (IsKeyDown(KEY_A)) wishDir = Vector3Subtract(wishDir, right);

    // Normalize so diagonal isn't faster
    if (Vector3Length(wishDir) > 0)
    {
        wishDir = Vector3Normalize(wishDir);
    }

    // Check for sprint (hold left shift to go faster)
    if(IsKeyDown(KEY_LEFT_SHIFT))
    {
        player.sprint = true;
    }
    else
    {
        player.sprint = false;
    }
    
    // check for sprinting and apply speed boost
    if(player.isGrounded){
        if (player.sprint)
        {
            player.maxSpeed = 8.0f; // increase max speed when sprinting
        }
        else 
        {
            player.maxSpeed = 5.0f; // reset to normal max speed when not sprinting
        }
    }
    // APPLY ACCELERATION (INPUT -> VELOCITY)

    // Choose ground or air control
    float accel = player.isGrounded ? player.groundAccel : player.airAccel;

    // Push velocity in input direction
    player.velocity = Vector3Add(player.velocity, Vector3Scale(wishDir, accel * dt));


    //  APPLY FRICTION (ONLY ON GROUND)

    if (player.isGrounded)
    {
        player.velocity.x -= player.velocity.x * player.friction * dt;
        player.velocity.z -= player.velocity.z * player.friction * dt;
    }



    //  APPLY GRAVITY

    player.velocity.y -= player.gravity * dt;


    // JUMP

    if (IsKeyPressed(KEY_SPACE) && player.isGrounded)
    {
        player.velocity.y = player.jumpForce; // instant upward speed
        player.isGrounded = false;
    }


    // LIMIT HORIZONTAL SPEED


    // Get horizontal velocity only
    Vector3 horizontalVel = { player.velocity.x, 0.0f, player.velocity.z };

    // Calculate speed
    float speed = Vector3Length(horizontalVel);

    // Clamp if too fast
    if (speed > player.maxSpeed)
    {
        horizontalVel = Vector3Scale(Vector3Normalize(horizontalVel), player.maxSpeed);

        player.velocity.x = horizontalVel.x;
        player.velocity.z = horizontalVel.z;
    }

    // APPLY VELOCITY → POSITION


    player.position.x += player.velocity.x * dt;
    player.position.y += player.velocity.y * dt;
    player.position.z += player.velocity.z * dt;

    // GROUND COLLISION


    if (player.position.y <= 2.0f)
    {
        player.position.y = 2.0f;
        player.velocity.y = 0;
        player.isGrounded = true;
    }
}