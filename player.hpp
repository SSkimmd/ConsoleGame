#pragma once
#include "display.hpp"
#include "sprite.hpp"
#include "projectile.hpp"



class Player {
    public:
        Player(int x, int y, int width, int height, Level* level, Display* display);
        Player() = default;
        ~Player() = default;
        
        void Draw(Display* display);
        void Update(long CurrentTime);
        void FixedUpdate();
        void FireProjectile(std::tuple<int, int> direction, int LifeTime);
        void FireWeapon(std::tuple<int, int> direction);
        void Damaged(int amount) {
            if(PlayerHealth - amount <= 0) {
                Dead = true;
                return;
            }

            PlayerHealth -= amount;
        }


        bool IsDead() {
            return Dead;
        }
        Sprite* GetSprite() { return &sprite; }
        Level* GetLevel() { return level; }
    private:
        Level* level;
        Display* display;
        Sprite sprite = Sprite();
        std::tuple<int, int> velocity;
        std::vector<Projectile> projectiles = {};

        int LastColourChange = 0;
        
        int MaxColours = 0;
        int CurrentColour = 1;


        bool Dead = false;
        bool Sprinting = false;

        int PlayerHealth = 100;
        int FireRate = 600;
        int WeaponRange = 10;
        long LastShot = 0;
        long CurrentTime = 0;
};