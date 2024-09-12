#include "raylib.h"

class Block {
public:
    Vector2 pos = { 100, 600 };
    Rectangle rect = { pos.x, pos.y, 100, 10 };

    // Method to draw the block
    void draw() {
        DrawRectangleRec(rect, WHITE);
    }

    // Method to get the block's rectangle for collision checks (const member function)
    Rectangle getRect() const {
        return rect;
    }
};
class End_Level{
public:
    Vector2 pos = { 500,600 };
    Rectangle rect = { pos.x, pos.y, 10, 10 };

    // Method to draw the block
    void draw() {
        DrawRectangleRec(rect, GREEN);
    }
};

