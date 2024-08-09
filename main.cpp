#include "raylib.h"


int main() {

    // Initialization
    InitWindow(800, 800, "Raylib Window");
    SetTargetFPS(60);

	
    // main loop
    while (!WindowShouldClose()) {

        // Update input/physics
	
	

        // Draw to the screen
        BeginDrawing();
        ClearBackground(BLACK);



        EndDrawing();
    }

    // De-Initialization
    CloseWindow();
    return 0;
}