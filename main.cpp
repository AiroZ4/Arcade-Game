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
int current_level = 0;


Player p;
std::vector<Block> blocks;  // Vector to hold multiple blocks
std::vector<Block> level_1;
std::vector<Block> level_2;

int main() {
    InitWindow(screenWidth, screenHeight, "Arcade Game");
    SetTargetFPS(60);

    // Level 1 Data
    level_1.push_back(Block{ {155, 223}, {155, 223, 84, 42} });
    level_1.push_back(Block{ {306, 182}, {306, 182, 66, 24} });
    level_1.push_back(Block{ {307, 264}, {307, 264, 77, 28} });

    // Level 2 Data
    level_2.push_back(Block{ {107, 401}, {107, 401, 117, 24} });
    level_2.push_back(Block{ {291, 371}, {291, 371, 49, 10} });
    level_2.push_back(Block{ {239, 310}, {239, 310, 19, 31} });
    level_2.push_back(Block{ {338, 275}, {338, 275, 196, 17} });
    

    while (!WindowShouldClose()) {
        // Gather all block rectangles for collision checking
        std::vector<Rectangle> blockRects;
        if (current_level == 0){
            for (const auto& block : level_1) {
                blockRects.push_back(block.getRect());
            }
        }
        else if (current_level == 1){
            for (const auto& block : level_2) {
                blockRects.push_back(block.getRect());
            }
        }
        
        // Draw everything
        BeginDrawing();
        ClearBackground(BLACK);

        // Update player and check for collisions with all blocks
        p.update(blockRects);

        // Draw the level depending on the current_level
        if (current_level == 0){
            for (auto& block : level_1) {
                block.draw();
            }
        }
        else if (current_level == 1){
            for (auto& block : level_2) {
                block.draw();
            }
        }
        

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
