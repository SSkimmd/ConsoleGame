#pragma once
#include "json.hpp"
#include <string>
#include "sprite.hpp"
#include "enemy.hpp"

struct Level {
    std::string name;
    std::vector<Sprite> sprites = {};
    std::vector<Enemy> enemies = {};
    int MaxColours = 0;
};