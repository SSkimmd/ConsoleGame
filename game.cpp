#include "game.hpp"

Game::Game() {

}

void Game::Start() {
    display = Display();
    display.Create(180, 60, 8, 12);

    levelManager = LevelManager(&display);

    running = true;
    Loop();
}

void Game::Loop() {
    while(running) {
        display.Update();
        levelManager.Update();
    }
}
