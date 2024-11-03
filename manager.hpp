#pragma once
#include "json.hpp"
#include "level.hpp"
#include "player.hpp"
#include <fstream>
using nlohmann::json;

enum LevelState {
    MENU,
    PLAYING,
    WON
};

class LevelManager {
    public:
        LevelManager(Display* display);
        LevelManager() { 

        }
        ~LevelManager();

        void Draw();
        void DrawMenu();
        void DrawWinMenu();
        void Update();
        void SpawnEnemy();
        bool LevelFinished() { return IsFinished; }

        Level LoadLevelData(std::string name);
        void StartLevel();
        Level* GetCurrentLevel() { return &CurrentLevel; };
    private:
        Display* display;
        Level CurrentLevel;
        Player player;
        std::vector<Projectile> projectiles;
        LevelState State = LevelState::MENU;

        long CurrentTime = 0;
        long LastUpdate = 0;
        long Fps = 24;
        long LastInput = 0;
        long LastSpawn = 0;

        bool SpawningEnemies = true;
        int MaxEnemies = 10;
        int SpawnRate = 1000;
        int EnemiesDestroyed = 0;

        bool IsFinished = false;
        int CurrentMenuOption = 0;
        std::vector<std::string> MenuOptions = {
        "Select Level 1", 
        "Select Level 2", 
        "Select Level 3",
        "Select Level 4",
        "Select Level 5",
        "Select Level 6",
        "Select Level 7"};
};