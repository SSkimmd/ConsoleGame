#pragma once
#include "level.hpp"

class Projectile {
    public:
        Projectile(Level* level, std::tuple<int, int> position, int SpawnTime, int LifeTime, int colour);
        ~Projectile() = default;
        void SetDirection(std::tuple<int, int> direction) {
            CurrentDirection = direction;
        }
        void Draw(Display* display);
        void FixedUpdate();
        bool CheckCollision();
        Sprite* GetSprite() {
            return &sprite;
        }
        int LifeTime = 0;
        int SpawnTime = 0;
    private:
        Level* level;
        Sprite sprite;
        std::tuple<int, int> CurrentDirection;
        int colour = 15;
};