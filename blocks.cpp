#include "raylib.h"

class block{
    public:
        Vector2 pos = { 100, 600 };
        Rectangle rect = { pos.x, pos.y, 100, 10};

        void draw(){
            DrawRectangleRec(rect, WHITE);
        }
    
};