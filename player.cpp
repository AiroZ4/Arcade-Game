#include "raylib.h"

class player{
    public:
        Vector2 pos{ 100,100 };
        Rectangle rect = { pos.x, pos.y, 20, 30 };
        Vector2 vel{};

        int speed;
        float jumpforce;
        float gravity;

        void move(){
            if (IsKeyDown(KEY_A)){

            }
        }
        void update(){
            DrawRectangleRec(rect, WHITE);
        }
}; 