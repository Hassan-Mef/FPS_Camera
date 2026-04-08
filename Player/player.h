#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include "raylib.h"
#include "raymath.h"
#include <cmath>



enum PlayerState
{
    IDLE,
    WALKING,
    SPRINTING,
    JUMPING,
    SLIDING,
    CROUCHING,
    FALLING
};



struct Player
{
    Camera3D camera;

    Vector3 position;
    Vector3 velocity;

    bool isGrounded;

    float moveSpeed;
    float gravity;
    float jumpForce;

    float groundAccel;
    float airAccel;
    float friction;

    float maxSpeed; //  cap on speed

    bool sprint ;
    bool isSliding; 

    Vector3 slideDirection; // direction of slide when sliding

    float yaw ;  // left right movement 
    float pitch;  // Up and donw movement 

    // Camera effects 
    float cameraRoll ; // for tilting camera when sliding 

    float headBobTime;
    float headBobAmount;

    float baseFov;
    float cameraHeightOffset;

    PlayerState state ;

    // Crouch 

    bool isCrouching;

    float crouchHeight;      // how low camera goes
    float crouchSpeed;       // movement speed while crouched
};


Player InitPlayer();

void UpdatePlayer(Player &player ,float dt );

#endif