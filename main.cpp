#include "raylib.h"
#include "raymath.h"
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <string>

const int screenWidth = 800;
const int screenHeight = 800;

int main() {
    InitWindow(screenWidth, screenHeight, "Arcade Game");
    SetTargetFPS(60);
    ToggleFullscreen();

    while (!WindowShouldClose()) {
        
        // Draw everything
        BeginDrawing();
        ClearBackground(BLACK);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
