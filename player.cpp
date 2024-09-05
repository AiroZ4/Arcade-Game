#include "raylib.h"
#include <iostream>

class player {
public:
    Vector2 pos{ 100, 100 };
    Rectangle rect = { pos.x, pos.y, 20, 30 };
    Vector2 vel{ 0, 0 };


    float speed = 7.0f;
    float jumpforce = 7.0f;
    float dashforce = 100.0f;
    int dashcounter = 0;
    float gravity = 0.5f;

    void move() {
        // Update velocity based on input
        if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) {
            vel.x = -speed; // Moving left
        } 
        else if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) {
            vel.x = speed; // Moving right
        } 
        else {
            vel.x = 0; // Stop when no key is pressed
        }

        // Dash 
        if (IsKeyDown(KEY_SPACE) && dashcounter == 1){
            if (vel.x <= -0.1f){
                vel.x = -dashforce;
                vel.y = 0;
                dashcounter = 0;
            }
            else if (vel.x >= 0.1f){
                vel.x = dashforce;
                vel.y = 0;
                dashcounter = 0;
            }
        }

        // Jump/Gravity
        if (IsKeyDown(KEY_C)){
            vel.y = -jumpforce; // Apply jump when you press C
        }
        else{
            vel.y += gravity; // Apply Gravity

        }

        // Update position based on velocity
        pos.x += vel.x;
        pos.y += vel.y;


        // Keep player within screen bounds
        if (pos.x < 0) pos.x = 0;
        if (pos.x > GetScreenWidth() - rect.width) pos.x = GetScreenWidth() - rect.width;

        if (pos.y < 0) pos.y = 0;
        if (pos.y > GetScreenHeight() - rect.height){
            pos.y = GetScreenHeight() - rect.height;
            
        }

    }

    void update() {
        // Handle input and movement
        move();

        // Update rectangle position to match the player's position
        rect.x = pos.x;
        rect.y = pos.y;
        std::cout << dashcounter;

        // Draw the player rectangle
        DrawRectangleRec(rect, WHITE);
    }
};