#include "raylib.h"
#include <vector>
#include <iostream>

class Player {
public:
    Vector2 pos{ 100, 100 };
    Rectangle rect = { pos.x, pos.y, 20, 30 };
    Vector2 vel{ 0, 0 };

    float speed = 7.0f;              
    float accel = 1.0f;              
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

    // Modify the update method in player.cpp to handle collisions from all sides
    void update(const std::vector<Rectangle>& obstacles) {
        move();

        // Update rectangle position to match the player's position
        rect.x = pos.x;
        rect.y = pos.y;

        // Check collision with each obstacle in the list
        for (const auto& obstacle : obstacles) {
            if (CheckCollisionRecs(rect, obstacle)) {
                // Handle collision on the top side
                if (vel.y > 0 && rect.y + rect.height <= obstacle.y + vel.y) {
                    pos.y = obstacle.y - rect.height;
                    vel.y = 0;
                    grounded = true;
                }
                // Handle collision on the bottom side
                else if (vel.y < 0 && rect.y >= obstacle.y + obstacle.height + vel.y) {
                    pos.y = obstacle.y + obstacle.height;
                    vel.y = 0;
                }
                // Handle collision on the right side
                else if (vel.x < 0 && rect.x >= obstacle.x + obstacle.width + vel.x) {
                    pos.x = obstacle.x + obstacle.width;
                    vel.x = 0;
                }
                // Handle collision on the left side
                else if (vel.x > 0 && rect.x + rect.width <= obstacle.x + vel.x) {
                    pos.x = obstacle.x - rect.width;
                    vel.x = 0;
                }
            }
        }

        // Draw the player
        DrawRectangleRec(rect, WHITE);
    }

};
