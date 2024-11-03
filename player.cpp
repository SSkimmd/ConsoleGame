#include "player.hpp"


Player::Player(int x, int y, int width, int height, Level* level, Display* display) {
    Sprite sprite = Sprite(x, y, width, height, L'P', "player");
    this->level = level;
    this->sprite = sprite;
    this->display = display;
    this->MaxColours = level->MaxColours;
}

void Player::Draw(Display* display) {
    if(Dead) {
        display->DrawString((display->GetWidth() / 2) - 7, 10, "Player Is Dead", 15);     
        display->DrawString((display->GetWidth() / 2) - 4, 11, "Game Over", 15);    
        display->DrawString((display->GetWidth() / 2) - 14, 12, "Press Enter To Return To Menu", 15);  
    } else {
        display->DrawString(display->GetWidth() - 15, 0, "Enemies: " + std::to_string(GetLevel()->enemies.size()), 15);
        display->DrawString(display->GetWidth() - 15, 2, "Colours: " + std::to_string(GetLevel()->MaxColours), 15); 
        display->DrawString(display->GetWidth() - 15, 3, "Colour: " + std::to_string(CurrentColour), CurrentColour); 
        display->DrawString(display->GetWidth() - 15, 4, "Health: " + std::to_string(PlayerHealth), 15); 

        if(!projectiles.empty()) {
            for(int i = 0; i < projectiles.size() - 1; i++) {
                if(projectiles.empty()) {
                    break;
                }

                if(CurrentTime < (projectiles[i].SpawnTime + projectiles[i].LifeTime)) {
                    projectiles[i].Draw(display);
                } else {
                    projectiles.erase(projectiles.begin() + i);
                }
            }            
        }

        sprite.Draw(display);
    }
}


void Player::FixedUpdate() {
    for(int i = 0; i < projectiles.size() - 1; i++) {
        if(projectiles.empty()) {
            break;
        }

        if(CurrentTime < (projectiles[i].SpawnTime + projectiles[i].LifeTime)) {
            projectiles[i].FixedUpdate();
        }
    }


    std::tuple<int, int> position = GetSprite()->GetPosition();
    int x = std::get<0>(position) + std::get<0>(velocity);
    int y = std::get<1>(position) + std::get<1>(velocity);

    GetSprite()->SetPosition(x, y);
}
void Player::FireWeapon(std::tuple<int, int> direction) {
    if(CurrentTime > (LastShot + 100)) {
        FireProjectile(direction, 2000);
        LastShot = CurrentTime;
    }
}

void Player::FireProjectile(std::tuple<int, int> direction, int LifeTime) {
    std::tuple<int, int> position = GetSprite()->GetPosition();

    Projectile newProjectile = Projectile(GetLevel(), position, CurrentTime, LifeTime, CurrentColour);
    newProjectile.SetDirection(direction);
    projectiles.push_back(newProjectile);
}


/*
    Do Input Stuff
*/
void Player::Update(long CurrentTime) {
    this->CurrentTime = CurrentTime;

    if((GetAsyncKeyState(VK_UP) & 0x8000)) {
        FireWeapon(std::tuple(0, -1));
    }
    if((GetAsyncKeyState(VK_RIGHT) & 0x8000)) {
        if(CurrentTime > LastColourChange + 100) {
            if(CurrentColour < MaxColours) {
                CurrentColour++;
            } else {
                CurrentColour = 1;
            }

            LastColourChange = CurrentTime;
        }
    }
    if((GetAsyncKeyState(VK_LEFT) & 0x8000)) {
        if(CurrentTime > LastColourChange + 100) {
            if(CurrentColour > 1) {
                CurrentColour--;
            } else {
                CurrentColour = MaxColours;
            }

            LastColourChange = CurrentTime;
        }
    }
    if(GetAsyncKeyState(VK_LSHIFT) & 0x8000) {
        Sprinting = true;
    }    
    if(!(GetAsyncKeyState(VK_LSHIFT) & 0x8000)) {
        Sprinting = false;
    }


    if(GetAsyncKeyState('A') & 0x8000) {
        if(!Sprinting) {
            std::get<0>(velocity) = -1;
        } else {
            std::get<0>(velocity) = -2;
        }
    }
    if(GetAsyncKeyState('D') & 0x8000) {
        if(!Sprinting) {
            std::get<0>(velocity) = 1;
        } else {
            std::get<0>(velocity) = 2;
        }
    }
    if(!(GetAsyncKeyState('A') & 0x8000) && !(GetAsyncKeyState('D') & 0x8000)) {
        std::get<0>(velocity) = 0;
    }
}
