#include "enemy.hpp"

Enemy::Enemy(int x, int y, int width, int height, short character, std::string name, int colour, int speed) {
    sprite = Sprite(x, y, width, height, character, name, colour);
    this->MoveSpeed = speed;
    this->CurrentColour = colour;
}

void Enemy::Draw(Display* display) {
    GetSprite()->Draw(display);
}

void Enemy::Update() {
    
}

void Enemy::FixedUpdate(int CurrentTime) {
    if(HasCrashed) return;

    if(CurrentTime >= LastMove + MoveSpeed) {
        std::tuple<int, int> position = GetSprite()->GetPosition();
        int x = std::get<0>(position);
        int y = std::get<1>(position) + 1;

        GetSprite()->SetPosition(x, y);
        LastMove = CurrentTime;
    }
}
