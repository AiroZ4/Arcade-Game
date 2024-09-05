#include "raylib.h"
#include <iostream>

class player {
public:
    Vector2 pos{ 100, 100 };
    Rectangle rect = { pos.x, pos.y, 20, 30 };
    Vector2 vel{ 0, 0 };

    float speed = 7.0f;              
    float accel = 0.75f;              
    float decelGrounded = 0.8f;      
    float decelAir = 0.3f;           
    float jumpforce = 10.0f;
    float gravity = 0.5f;
    bool grounded = false;

    void move() {
        // Update velocity based on input
        if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) {
            vel.x -= accel;           // Accelerate left
            if (vel.x < -speed) vel.x = -speed; // Cap at max speed
        } 
        else if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) {
            vel.x += accel;           // Accelerate right
            if (vel.x > speed) vel.x = speed;  // Cap at max speed
        } 
        else {
            // Apply deceleration when no movement key is pressed
            float decelRate = grounded ? decelGrounded : decelAir;
            if (vel.x > 0) {
                vel.x -= decelRate;
                if (vel.x < 0) vel.x = 0; // Stop completely if below zero
            } 
            else if (vel.x < 0) {
                vel.x += decelRate;
                if (vel.x > 0) vel.x = 0; // Stop completely if above zero
            }
        }

        // Jump/Gravity
        if (IsKeyDown(KEY_C) && grounded) {
            vel.y = -jumpforce; // Apply jump when you press C
            grounded = false;
        } 
        else {
            vel.y += gravity; // Apply Gravity
        }

        // Update position based on velocity
        pos.x += vel.x;
        pos.y += vel.y;

        // Keep player within screen bounds
        if (pos.x < 0) pos.x = 0;
        if (pos.x > GetScreenWidth() - rect.width) pos.x = GetScreenWidth() - rect.width;

        if (pos.y < 0) pos.y = 0;
        if (pos.y > GetScreenHeight() - rect.height) {
            pos.y = GetScreenHeight() - rect.height;
            grounded = true;
        }
    }

    void update() {
        // Handle input and movement
        move();

        // Update rectangle position to match the player's position
        rect.x = pos.x;
        rect.y = pos.y;

        // Draw the player rectangle
        DrawRectangleRec(rect, WHITE);
    }
};
