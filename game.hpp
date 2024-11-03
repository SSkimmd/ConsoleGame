#include "display.hpp"
#include "manager.hpp"
#include <map>

class Game {
    public:
        Game();
        ~Game() = default;

        void Start();
        void Loop();
    private:
        Display display;
        LevelManager levelManager;
        bool running = false;
};