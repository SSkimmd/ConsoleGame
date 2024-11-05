#include "projectile.hpp"

Projectile::Projectile(Level* level, std::tuple<int, int> position, int SpawnTime, int LifeTime, int colour = 15) {
    int x = std::get<0>(position);
    int y = std::get<1>(position);
    
    sprite = Sprite(x, y, 1, 1, L'~', "projectile", colour);

    this->SpawnTime = SpawnTime;
    this->LifeTime = LifeTime;
    this->colour = colour;
    this->level = level;
}

void Projectile::Draw(Display* display) {
    CheckCollision();
    sprite.Draw(display);
}


void Projectile::FixedUpdate() {    
    std::tuple<int, int> position = GetSprite()->GetPosition();
    int x = std::get<0>(position) + std::get<0>(CurrentDirection);
    int y = std::get<1>(position) + std::get<1>(CurrentDirection);

    GetSprite()->SetPosition(x, y);
}

bool Projectile::CheckCollision() {
    for(auto& enemy : level->enemies) {
        int y = std::get<1>(GetSprite()->GetPosition());
        int x = std::get<0>(GetSprite()->GetPosition());

        int enemyX = std::get<0>(enemy.GetSprite()->GetPosition());
        int enemyY = std::get<1>(enemy.GetSprite()->GetPosition());

        if(x <= (enemyX + enemy.GetSprite()->GetWidth() - 1) && x >= enemyX) {
            if(y == (enemyY + enemy.GetSprite()->GetHeight() - 1)) {
                if(enemy.GetColour() == colour) {
                    enemy.Hit(100);
                }
                return true;
            }
        }
    }

    return false;
}