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
    p.isSliding = false;


    p.slideDirection = {0.0f, 0.0f, 0.0f};

    // Mouse look
    p.yaw = -90.0f;
    p.pitch = 0.0f;

    // Camera effects
    p.cameraRoll = 0.0f;
    p.baseFov = 60.0f;

    return p;
}


void UpdatePlayer(Player &player, float dt)
{
    // ================= VARIABLES  =================

    Vector2 mouseDelta = GetMouseDelta();
    float sensitivity = 0.1f;

    Vector3 direction;
    Vector3 forward;
    Vector3 right;
    Vector3 wishDir = {0};

    float strafeAmount;
    float targetRoll;
    float accel;

    Vector3 horizontalVel;
    float speed;

    float targetFov;
    float bobSpeed;
    float bobX, bobY;
    float bobIntensity;
    float targetBobSpeed;

    float slideStartSpeed = 6.0f;

    // ================= MOUSE LOOK =================

    // MOUSE LOOK (where player is looking)

    player.yaw   += mouseDelta.x * sensitivity;
    player.pitch -= mouseDelta.y * sensitivity;

    // Prevent flipping
    if (player.pitch > 89.0f) player.pitch = 89.0f;
    if (player.pitch < -89.0f) player.pitch = -89.0f;

    // Convert yaw/pitch -> direction vector
    direction.x = cosf(DEG2RAD * player.yaw) * cosf(DEG2RAD * player.pitch);
    direction.y = sinf(DEG2RAD * player.pitch);
    direction.z = sinf(DEG2RAD * player.yaw) * cosf(DEG2RAD * player.pitch);

    // Camera follows player
    player.camera.target = Vector3Add(player.position, direction);


    // ================= MOVEMENT DIRECTIONS =================

    //  CREATE MOVEMENT DIRECTIONS (forward/right)

    // Ignore Y so player doesn't fly when looking up
    forward = { direction.x, 0.0f, direction.z };
    forward = Vector3Normalize(forward);

    right = Vector3CrossProduct(forward, {0.0f, 1.0f, 0.0f});
    right = Vector3Normalize(right);


    // ================= INPUT =================

    //  INPUT -> "WISH DIRECTION"

    if (!player.isSliding)
    {
        if (IsKeyDown(KEY_W)) wishDir = Vector3Add(wishDir, forward);
        if (IsKeyDown(KEY_S)) wishDir = Vector3Subtract(wishDir, forward);
        if (IsKeyDown(KEY_D)) wishDir = Vector3Add(wishDir, right);
        if (IsKeyDown(KEY_A)) wishDir = Vector3Subtract(wishDir, right);
    }
    else
    {
        wishDir = player.slideDirection;
    }

    if (Vector3Length(wishDir) > 0)
    {
        wishDir = Vector3Normalize(wishDir);
    }

    // Calculate Strafe Angle (for animation or later use)
    strafeAmount = Vector3DotProduct(wishDir, right);

    // Check for sprint (hold left shift to go faster)
    player.sprint = IsKeyDown(KEY_LEFT_SHIFT);

    if(player.isGrounded){
        if (player.sprint)
            player.maxSpeed = 8.0f;
        else 
            player.maxSpeed = 5.0f;
    }

    // Calculate player Tilt (for sliding animation)
    targetRoll = -strafeAmount * 1.5f;


    // ================= MOVEMENT =================

    // APPLY ACCELERATION (INPUT -> VELOCITY)

    if(!player.isSliding)
    {
        accel = player.isGrounded ? player.groundAccel : player.airAccel;

        if (player.isGrounded)
        {
            player.velocity = Vector3Add(player.velocity, Vector3Scale(wishDir, accel * dt));
        }
        else
        {
            // AIR STRAFING LOGIC

            horizontalVel = { player.velocity.x, 0.0f, player.velocity.z };

            float currentSpeed = Vector3DotProduct(horizontalVel, wishDir);
            float alignment = currentSpeed / (Vector3Length(horizontalVel) + 0.0001f);

            float maxInfluence = 0.7f;

            if (alignment < -maxInfluence)
                alignment = -maxInfluence;

            float airControlLimit = 6.5f;
            float addSpeed = airControlLimit * (1.0f - alignment) - currentSpeed;

            if (addSpeed > 0)
            {
                float airMaxSpeed = 7.0f;
                float accelSpeed = accel * dt * airMaxSpeed;

                if (accelSpeed > addSpeed)
                    accelSpeed = addSpeed;

                player.velocity = Vector3Add(player.velocity, Vector3Scale(wishDir, accelSpeed));
            }
        }
    }


    // ================= FRICTION =================

    //  APPLY FRICTION (ONLY ON GROUND)

    if (player.isGrounded )
    {
        if(!player.isSliding)
        {
            player.velocity.x -= player.velocity.x * player.friction * dt;
            player.velocity.z -= player.velocity.z * player.friction * dt;
        }
        else
        {
            float slideFriction = player.friction * 0.2f;

            Vector3 horizontal = {player.velocity.x, 0.0f, player.velocity.z};
            horizontal = Vector3Scale(horizontal, 1.0f - slideFriction * dt);

            player.velocity.x = horizontal.x;
            player.velocity.z = horizontal.z;
        }
    }


    // ================= GRAVITY & JUMP =================

    //  APPLY GRAVITY

    player.velocity.y -= player.gravity * dt;

    // JUMP

    if (IsKeyPressed(KEY_SPACE) && player.isGrounded)
    {
        player.velocity.y = player.jumpForce;
        player.isGrounded = false;
    }


    // ================= SPEED =================

    // LIMIT HORIZONTAL SPEED

    horizontalVel = { player.velocity.x, 0.0f, player.velocity.z };
    speed = Vector3Length(horizontalVel);

    if(player.isGrounded){
        if (speed > player.maxSpeed)
        {
            horizontalVel = Vector3Scale(Vector3Normalize(horizontalVel), player.maxSpeed);

            player.velocity.x = horizontalVel.x;
            player.velocity.z = horizontalVel.z;
        }
    }


    // ================= CAMERA EFFECTS =================

    // FOV based on speed
    targetFov = player.baseFov + speed * 0.5f;


    // ================= HEAD BOB =================

    // Step-based rhythm (NOT speed-driven anymore)
    targetBobSpeed = player.sprint ? 1.5f : 1.0f;

    if (player.isGrounded && speed > 2.0f)
    {
        player.headBobTime += dt * targetBobSpeed;
    }

    // Subtle and stable bob
    bobY = sinf(player.headBobTime * 6.0f) * 0.012f;   // slightly reduced
    bobX = cosf(player.headBobTime * 3.0f) * 0.006f;   // even smaller


    // Intensity scaling (clamped HARD)
    bobIntensity = speed / player.maxSpeed;
    if (bobIntensity > 0.4f) bobIntensity = 0.4f;


    // ================= SLIDE =================

    // Calculate target roll based on sliding
    if (player.isSliding)
    {
        targetRoll *= 1.5f;
        targetFov += 10.0f;
    }

    if(IsKeyPressed(KEY_C) && player.isGrounded && speed > slideStartSpeed)
    {
        player.slideDirection = Vector3Normalize(horizontalVel);

        float slideBoost = 1.15f;
        float boostedSpeed = speed * slideBoost;

        player.velocity.x = player.slideDirection.x * boostedSpeed;
        player.velocity.z = player.slideDirection.z * boostedSpeed;

        player.isSliding = true;
    }

    if(player.isSliding)
    {
        if(!IsKeyDown(KEY_C) || speed < 2.0f || !player.isGrounded)
        {
            player.isSliding = false;
        }
    }


    // ================= POSITION =================

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


    // ================= FINAL CAMERA =================

    // Smoothly apply camera roll
    player.cameraRoll += (targetRoll - player.cameraRoll) * 5.0f * dt;

    player.camera.up.x = sinf(DEG2RAD * player.cameraRoll);
    player.camera.up.y = cosf(DEG2RAD * player.cameraRoll);
    player.camera.up.z = 0;

    // // Apply head bob and FOV changes
    //player.camera.position.x = player.position.x + bobX * bobIntensity;

    // player.camera.position.x = player.position.x;
    // player.camera.position.y = player.position.y + bobY * bobIntensity;
    // player.camera.position.z = player.position.z;

    //player.camera.fovy += (targetFov - player.camera.fovy) * 1.0f * dt;


    // Stable camera follow
    player.camera.position.x = player.position.x;
    player.camera.position.z = player.position.z;

    // Only vertical bob (clean feel)
    player.camera.position.y = player.position.y + bobY * bobIntensity;


    // Smooth FOV (IMPORTANT — re-enabled)
    player.camera.fovy += (targetFov - player.camera.fovy) * 5.0f * dt;
}