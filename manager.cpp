#include "manager.hpp"

LevelManager::LevelManager(Display* display) {
    this->display = display;
}

LevelManager::~LevelManager() {

}


/*


*/
Sprite LoadSprite(json sprite) {
    int x = sprite["position"]["x"];
    int y = sprite["position"]["y"];
    int width = sprite["scale"]["width"];
    int height = sprite["scale"]["height"];   
    std::string name = sprite["name"];
    std::string c = sprite["character"];
    char ch = c[0];
    

    Sprite s = Sprite(x, y, width, height, ch, name);
    return s;
}

/*


*/

/*


*/
Level LevelManager::LoadLevelData(std::string name) {
    std::ifstream file(name);
    json data;
    file >> data;

    Level level = Level();
    for(auto object : data["level"]["objects"]) {
        if(object.contains("character")) {
            level.sprites.push_back(LoadSprite(object));
        }
    }

    std::string levelName = data["name"].dump();
    level.name = levelName;
    level.MaxColours = data["level"]["max_colours"];
    level.WinRequirement = data["level"]["win_requirement"];
    CurrentLevel = level;


    StartLevel();
    return level;
}


/*


*/
void LevelManager::StartLevel() {
    EnemiesDestroyed = 0;
    player = Player(0, display->GetHeight() - 2, 2, 2, GetCurrentLevel(), display);
    State = LevelState::PLAYING;
}

/*


*/
void LevelManager::Draw() {
    display->Fill(0, 0, display->GetWidth(), display->GetHeight(), L' ', 0);
    display->DrawString(display->GetWidth() - 17, 1, "Destroyed: " + std::to_string(EnemiesDestroyed) + "/" + std::to_string(GetCurrentLevel()->WinRequirement), 15); 
    player.Draw(display);

    if(!player.IsDead()) {
        for(auto& sprite : GetCurrentLevel()->sprites) {
            sprite.Draw(display);
        }

        for(auto& enemy : GetCurrentLevel()->enemies) {
            enemy.Draw(display);
        }
    }
}

void LevelManager::DrawMenu() {
    display->Fill(0, 0, display->GetWidth(), display->GetHeight(), L' ', 0);
    display->DrawString((display->GetWidth() / 2) - 4, 10, "Main Menu", 15);
    display->DrawString((display->GetWidth() / 2) - 60, 10, "Controls", 15);
    display->DrawString((display->GetWidth() / 2) - 60, 12, "In-Menu", 15);
    display->DrawString((display->GetWidth() / 2) - 60, 13, "[Up] And [Down] Arrows - Next/Previous Option", 15);
    display->DrawString((display->GetWidth() / 2) - 60, 14, "[Spacebar] - Select Option", 15);

    display->DrawString((display->GetWidth() / 2) - 60, 16, "In-Game", 15);
    display->DrawString((display->GetWidth() / 2) - 60, 17, "[Up] Arrow - Fire Weapon", 15);
    display->DrawString((display->GetWidth() / 2) - 60, 18, "[Left] And [Right] Arrows - Next/Previous Colour", 15);
    display->DrawString((display->GetWidth() / 2) - 60, 19, "[D] And [A] - Move Left And Right", 15);
    display->DrawString((display->GetWidth() / 2) - 60, 20, "[Hold][LShift] - Speed Boost", 15);
    
    int pos = 1;
    for(int i = 0; i < MenuOptions.size(); i++) {
        pos++;
        if(CurrentMenuOption == i) {
            display->DrawString((display->GetWidth() / 2) - 7, 11 + pos, "[" + MenuOptions[i] + "]", 15); 
        } else {
            display->DrawString((display->GetWidth() / 2) - 6, 11 + pos, MenuOptions[i], 15); 
        }
    } 

    if((GetAsyncKeyState(VK_UP) & 0x8000)) {
        if(CurrentTime >= LastInput + 100) {
            if(CurrentMenuOption - 1 >= 0) {
                CurrentMenuOption--;
            }
            LastInput = CurrentTime;
        }
    }
    if((GetAsyncKeyState(VK_DOWN) & 0x8000)) {
        if(CurrentTime >= LastInput + 100) {
            if(CurrentMenuOption + 1 < MenuOptions.size()) {
                CurrentMenuOption++;
            }
            LastInput = CurrentTime;
        }
    }
    if((GetAsyncKeyState(VK_SPACE) & 0x8000)) {
        LoadLevelData("levels/level" + std::to_string(CurrentMenuOption + 1) + ".json");
    }
}

void LevelManager::DrawWinMenu() {
    display->Fill(0, 0, display->GetWidth(), display->GetHeight(), L' ', 0);
    display->DrawString((display->GetWidth() / 2) - 24, 10, "Congrats You've Successfully Completed This Level", 15);
    display->DrawString((display->GetWidth() / 2) - 15, 11, "Press [Enter] To Return To Menu", 15);

    if((GetAsyncKeyState(VK_RETURN) & 0x8000)) {
        State = LevelState::MENU;
    }
}

void LevelManager::SpawnEnemy() {
    int xspawnpos = rand() % (display->GetWidth() - 25);
    int colour = rand() % GetCurrentLevel()->MaxColours + 1;

    Enemy enemy = Enemy(xspawnpos, 0, 4, 2, L'#', "enemy", colour, 350);
    GetCurrentLevel()->enemies.push_back(enemy);
    LastSpawn = CurrentTime;
}

/*


*/
void LevelManager::Update() {
    if(State == LevelState::PLAYING) {
        Draw();
        if(!player.IsDead()) {
            //this really shouldn't be hard coded
            //nothing more permanent than temporary code
            if(EnemiesDestroyed >= GetCurrentLevel()->WinRequirement) {
                State = LevelState::WON;
                return;
            }

            player.Update(CurrentTime);

            //only call update at fixed rate
            if(LastUpdate == 0) {
                LastUpdate = CurrentTime;
                player.FixedUpdate();
            } else if((CurrentTime - LastUpdate) >= Fps) {
                LastUpdate = CurrentTime;
                player.FixedUpdate();       
            }

            if(!GetCurrentLevel()->enemies.empty()) {
                for(int i = 0; i < GetCurrentLevel()->enemies.size(); i++) {
                    auto& enemy = GetCurrentLevel()->enemies[i];
                    //only update if the enemy is alive
                    if(enemy.GetHealth() > 0) {
                        if(enemy.Crashed()) {
                            GetCurrentLevel()->enemies.erase(GetCurrentLevel()->enemies.begin() + i);
                            continue;
                        }

                        enemy.Update();  
                        enemy.FixedUpdate(CurrentTime); 
                    } else {      
                        //remove if the enemy is dead
                        if(!enemy.Crashed()) {
                            EnemiesDestroyed++;
                            GetCurrentLevel()->enemies.erase(GetCurrentLevel()->enemies.begin() + i);
                            continue;
                        }
                    }

                    int y = std::get<1>(enemy.GetSprite()->GetPosition());

                    //check if Y position is at the bottom of the screen
                    if(y + enemy.GetSprite()->GetHeight() == display->GetHeight()) {
                        //cause damage to player
                        if(!enemy.Crashed()) {
                            player.Damaged(10);
                            enemy.SetCrashed(true);
                        }
                    } 
                }
            }

            //if level allows for continuous spawning
            if(SpawningEnemies) {
                //check if time since last spawn is equal to spawn rate
                if(CurrentTime > LastSpawn + SpawnRate) {
                    if(GetCurrentLevel()->enemies.size() < MaxEnemies) {
                        SpawnEnemy();
                    }
                }
            }
            if((GetAsyncKeyState(VK_ESCAPE) & 0x8000)) {
                State = LevelState::MENU;
                return;
            }

            CurrentTime++;
        } else {
            if((GetAsyncKeyState(VK_RETURN) & 0x8000)) {
                State = LevelState::MENU;
                return;
            }            
        }
    }
    if(State == LevelState::MENU) {
        DrawMenu();
        CurrentTime++;
    }
    if(State == LevelState::WON) {
        display->Fill(0, 0, display->GetWidth(), display->GetHeight(), L' ', 0);
        DrawWinMenu();
        CurrentTime++;
    }
}