#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include "raylib.h"
#include "raymath.h"
#include <cmath>

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

    float yaw ;  // left right movement 
    float pitch;  // Up and donw movement 
};

Player InitPlayer();

void UpdatePlayer(Player &player ,float dt );

#endif