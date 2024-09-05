// main.cpp changes
#include "raylib.h"
#include "raymath.h"
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <string>
#include "player.cpp"
#include "blocks.cpp"
#include <iostream>

const int screenWidth = 800;
const int screenHeight = 800;

Player p;
std::vector<Block> blocks;  // Vector to hold multiple blocks

int main() {
    InitWindow(screenWidth, screenHeight, "Arcade Game");
    SetTargetFPS(60);

    // Create some blocks
    blocks.push_back(Block{ {200, 750}, {200, 750, 100, 15} });
    blocks.push_back(Block{ {400, 700}, {400, 700, 100, 15} });
    blocks.push_back(Block{ {300, 600}, {300, 600, 100, 15} });
    

    while (!WindowShouldClose()) {
        // Gather all block rectangles for collision checking
        std::vector<Rectangle> blockRects;
        for (const auto& block : blocks) {
            blockRects.push_back(block.getRect());
        }

        // Draw everything
        BeginDrawing();
        ClearBackground(BLACK);

        // Update player and check for collisions with all blocks
        p.update(blockRects);

        // Draw all blocks
        for (auto& block : blocks) {
            block.draw();
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
