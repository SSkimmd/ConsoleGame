#pragma once
#include "display.hpp"
#include <tuple>


class Sprite {
    public:
        Sprite(int x, int y, int width, int height, short character, std::string name, int colour = 15) {
            this->x = x;
            this->y = y;
            this->width = width;
            this->height = height;
            this->character = character;    
            this->name = name;
            this->colour = colour;
        }
        Sprite() = default;
        ~Sprite() = default;

        void Draw(Display* display) {
            if(!IsHidden) {
                display->Fill(x, y, x + width, y + height, character, colour);
            }
        }

        void Hide(bool hidden) {
            IsHidden = hidden;
        }
        bool Hidden() { return IsHidden; }

        std::string GetName() { return name; }
        std::tuple<int, int> GetPosition() { return std::tuple(x, y); }
        std::tuple<int, int> SetPosition(int x, int y) { 
            this->x = x; 
            this->y = y; 
            return std::tuple(x, y); 
        }
        int GetWidth() {
            return width;
        }
        int GetHeight() {
            return height;
        }
        std::tuple<int, int> SetPosition(std::tuple<int, int> position) { 
            this->x = std::get<0>(position); 
            this->y = std::get<1>(position); 
            return std::tuple(x, y); 
        }
    private:
        int x = 0, y = 0;
        int width = 0, height = 0;
        short character = 0;
        std::string name = "";
        bool IsHidden = false;
        int colour;
};