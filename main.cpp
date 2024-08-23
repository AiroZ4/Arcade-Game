#include "raylib.h"
#include "raymath.h"
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <string>

const int screenWidth = 800;
const int screenHeight = 800;
const float gravity = 200.0f;

class Fruit {
public:
    Vector2 position;
    float radius;
    Color color;
    Vector2 velocity;
    bool isFalling;

    Fruit(Vector2 pos, float r, Color c) 
        : position(pos), radius(r), color(c), velocity({ 0, 0 }), isFalling(false) {}

    virtual ~Fruit() = default;

    void Update(float deltaTime) {
        if (isFalling) {
            velocity.y += gravity * deltaTime;
            position.y += velocity.y * deltaTime;

            // Boundary check for bottom
            if (position.y + radius > screenHeight) {
                position.y = screenHeight - radius;
                velocity.y = 0;
            }

            // Boundary check for sides
            if (position.x - radius < 0) position.x = radius;
            if (position.x + radius > screenWidth) position.x = screenWidth - radius;
        }
    }

    void Draw() const {
        DrawCircleV(position, radius, color);
    }

    bool CheckCollision(const Fruit& other) const {
        float dist = sqrt((position.x - other.position.x) * (position.x - other.position.x) +
                          (position.y - other.position.y) * (position.y - other.position.y));
        return dist <= (radius + other.radius);
    }
};

class Grape : public Fruit {
public:
    Grape(Vector2 pos) : Fruit(pos, 10.0f, PURPLE) {}
};

class Lemon : public Fruit {
public:
    Lemon(Vector2 pos) : Fruit(pos, 20.0f, YELLOW) {}
};

class Apple : public Fruit {
public:
    Apple(Vector2 pos) : Fruit(pos, 30.0f, RED) {}
};

class Watermelon : public Fruit {
public:
    Watermelon(Vector2 pos) : Fruit(pos, 40.0f, GREEN) {}
};

std::vector<Fruit*> fruits;
std::vector<bool> unlockedFruits = {true, true, false, false}; // Start with grapes and lemons unlocked
int score = 0;

Fruit* CreateRandomFruit(float x) {
    std::vector<int> availableFruits;
    for (int i = 0; i < unlockedFruits.size(); i++) {
        if (unlockedFruits[i]) {
            availableFruits.push_back(i);
        }
    }

    int fruitType = availableFruits[rand() % availableFruits.size()];
    Vector2 position = { x, 0 };

    switch (fruitType) {
        case 0: return new Grape(position);
        case 1: return new Lemon(position);
        case 2: return new Apple(position);
        case 3: return new Watermelon(position);
        default: return nullptr;
    }
}

Fruit* CombineFruits(Fruit* fruit1, Fruit* fruit2) {
    if (dynamic_cast<Grape*>(fruit1) && dynamic_cast<Grape*>(fruit2)) {
        unlockedFruits[1] = true; // Unlock Lemon
        score += 10;
        return new Lemon(fruit1->position);
    }
    if (dynamic_cast<Lemon*>(fruit1) && dynamic_cast<Lemon*>(fruit2)) {
        unlockedFruits[2] = true; // Unlock Apple
        score += 20;
        return new Apple(fruit1->position);
    }
    if (dynamic_cast<Apple*>(fruit1) && dynamic_cast<Apple*>(fruit2)) {
        unlockedFruits[3] = true; // Unlock Watermelon
        score += 50;
        return new Watermelon(fruit1->position);
    }
    return nullptr;
}

void CheckCollisions() {
    for (size_t i = 0; i < fruits.size(); ++i) {
        for (size_t j = i + 1; j < fruits.size(); ++j) {
            if (fruits[i]->CheckCollision(*fruits[j])) {
                Fruit* newFruit = CombineFruits(fruits[i], fruits[j]);
                if (newFruit) {
                    delete fruits[i];
                    delete fruits[j];
                    fruits.erase(fruits.begin() + j);
                    fruits.erase(fruits.begin() + i);
                    fruits.push_back(newFruit);
                    return;
                } else {
                    // Handle collision response if not combinable
                    Vector2 overlap = Vector2Subtract(fruits[i]->position, fruits[j]->position);
                    float dist = Vector2Length(overlap);
                    Vector2 moveDir = Vector2Scale(overlap, (fruits[i]->radius + fruits[j]->radius - dist) / dist);
                    fruits[i]->position = Vector2Add(fruits[i]->position, Vector2Scale(moveDir, 0.5f));
                    fruits[j]->position = Vector2Subtract(fruits[j]->position, Vector2Scale(moveDir, 0.5f));
                }
            }
        }
    }
}

int main() {
    InitWindow(screenWidth, screenHeight, "Fruit Game");
    SetTargetFPS(60);

    srand(time(0));

    Fruit* previewFruit = nullptr;

    while (!WindowShouldClose()) {
        float deltaTime = GetFrameTime();
        float mouseX = GetMouseX();

        if (previewFruit) {
            previewFruit->position.x = mouseX;
        }

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            if (previewFruit) {
                previewFruit->isFalling = true;
                fruits.push_back(previewFruit);
                previewFruit = nullptr;
            }

            previewFruit = CreateRandomFruit(mouseX);
        }

        // Update all fruits
        for (auto& fruit : fruits) {
            fruit->Update(deltaTime);
        }

        // Check for collisions
        CheckCollisions();

        // Draw everything
        BeginDrawing();
        ClearBackground(BLACK);

        for (const auto& fruit : fruits) {
            fruit->Draw();
        }

        if (previewFruit) {
            previewFruit->Draw();  // Draw the preview fruit
        }

        DrawText(TextFormat("Score: %i", score), 10, 10, 20, WHITE);  // Display score

        EndDrawing();
    }

    // Cleanup
    for (auto& fruit : fruits) {
        delete fruit;
    }
    if (previewFruit) delete previewFruit;

    CloseWindow();

    return 0;
}
