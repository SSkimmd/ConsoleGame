#pragma once
#include "sprite.hpp"


class Enemy {
    public:
        Enemy(int x, int y, int width, int height, short character, std::string name, int colour, int speed);
        ~Enemy() = default;
        void Draw(Display* display);
        void Update();
        void FixedUpdate(int CurrentTime);
        void Hit(int damage) {
            health -= damage;
        }
        int GetColour() {
            return CurrentColour;
        }
        int GetHealth() {
            return health;
        };
        void SetCrashed(bool crashed) {
            HasCrashed = crashed;
        }
        bool Crashed() {
            return HasCrashed;
        }
        Sprite* GetSprite() { return &sprite; }
    private:
        Sprite sprite = Sprite();
        int health = 100;
        int CurrentColour = 15;
        int LastMove = 0;
        int MoveSpeed = 0;
        bool HasCrashed = false;
};