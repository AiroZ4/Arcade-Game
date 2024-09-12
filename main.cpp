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
bool reset_level = true;


Player p;
Rectangle el1 = {170, 510, 20, 20};
std::vector<Block> Level_3;
std::vector<Block> level_1;
std::vector<Block> level_2;

void check_end_level(){
    bool collision = CheckCollisionRecs(el1, p.rect);
    if (collision){
        p.vel = {0,0};
        current_level += 1;
        reset_level = true;
    }
}

int main() {
    InitWindow(screenWidth, screenHeight, "Arcade Game");
    SetTargetFPS(60);

    // Level 1 Data
    level_1.push_back(Block{ {16, 157}, {16, 157, 38, 541} });
    level_1.push_back(Block{ {21, 659}, {21, 659, 616, 39} });
    level_1.push_back(Block{ {99, 166}, {99, 166, 30, 418} });
    level_1.push_back(Block{ {101, 547}, {101, 547, 415, 38} });
    level_1.push_back(Block{ {595, 487}, {595, 487, 40, 210} });
    level_1.push_back(Block{ {580, 599}, {580, 599, 18, 12} });
    level_1.push_back(Block{ {511, 562}, {511, 562, 18, 11} });
    level_1.push_back(Block{ {240, 400}, {240, 400, 394, 97} });

    


    // Level 2 Data
    level_2.push_back(Block{ {107, 401}, {107, 401, 117, 24} });
    level_2.push_back(Block{ {291, 371}, {291, 371, 49, 10} });
    level_2.push_back(Block{ {239, 310}, {239, 310, 19, 31} });
    level_2.push_back(Block{ {338, 275}, {338, 275, 196, 17} });

    // Level 3 Data
    

    while (!WindowShouldClose()) {
        // Gather all block rectangles for collision checking
        std::vector<Rectangle> blockRects;
        if (current_level == 0){
            for (const auto& block : level_1) {
                blockRects.push_back(block.getRect());
            }
            
            DrawRectangleRec(el1, DARKBLUE);
        }
        else if (current_level == 1){
            for (const auto& block : level_2) {
                blockRects.push_back(block.getRect());
            }
        }
        if (reset_level == true){
            if (current_level == 0){
                p.pos = {65,200};
                reset_level = false;
            }
            else if (current_level == 1){
                p.pos = {200,100};
                reset_level = false;
            }
        }
        
        // Draw everything
        BeginDrawing();
        ClearBackground(BLACK);

        // Update player and check for collisions with all blocks
        p.update(blockRects);
        check_end_level();

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

