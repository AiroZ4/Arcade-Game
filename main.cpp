#include "raylib.h"
#include "raymath.h"
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <string>
#include <player.cpp>
#include <blocks.cpp>
#include <iostream>

const int screenWidth = 800;
const int screenHeight = 800;

player p;
block b1;

int main() {
    InitWindow(screenWidth, screenHeight, "Arcade Game");
    SetTargetFPS(60);
    //ToggleFullscreen();

    while (!WindowShouldClose()) {
        
        // Draw everything
        BeginDrawing();
        ClearBackground(BLACK);
        p.update();
        b1.draw();
        

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
