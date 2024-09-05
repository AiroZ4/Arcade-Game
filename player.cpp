#include "raylib.h"
#include <stdio.h>

class player {
public:
    Vector2 pos{ 100, 100 };
    Rectangle rect = { pos.x, pos.y, 20, 30 };
    Vector2 vel{ 0, 0 };

    float speed = 5.0f;
    float jumpforce = 5.0f;
    float gravity = 0.5f;

    void move() {
        // Update velocity based on input
        if (IsKeyDown(KEY_A)) {
            vel.x = -speed; // Moving left
        } 
        else if (IsKeyDown(KEY_D)) {
            vel.x = speed; // Moving right
        } 
        else {
            vel.x = 0; // Stop when no key is pressed
        }

        // Update position based on velocity
        pos.x += vel.x;

        // Keep player within screen bounds
        if (pos.x < 0) pos.x = 0;
        if (pos.x > GetScreenWidth() - rect.width) pos.x = GetScreenWidth() - rect.width;
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