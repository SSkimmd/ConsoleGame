#pragma once

#include "windows.h"
#include <vector>
#include <iostream>
#include <chrono>
#include <list>
#include <thread>
#include <atomic>
#include <condition_variable>

class Display {
    public:
        Display();
        ~Display() = default;

        int Create(int width, int height, int fontw, int fonth);

        void Draw(int x, int y, short c = 0x2588, short col = 0x000F) {
            if (x >= 0 && x < ScreenWidth && y >= 0 && y < ScreenHeight) {
                ScreenBuffer[y * ScreenWidth + x].Char.UnicodeChar = c;
                ScreenBuffer[y * ScreenWidth + x].Attributes = col;
            }
        }
        void DrawString(int x, int y, std::wstring c, short col = 0x000F) {
            for (size_t i = 0; i < c.size(); i++) {
                ScreenBuffer[y * ScreenWidth + x + i].Char.UnicodeChar = c[i];
                ScreenBuffer[y * ScreenWidth + x + i].Attributes = col;
            }
        }
        void DrawString(int x, int y, std::string c, short col = 0x000F) {
            for (size_t i = 0; i < c.size(); i++) {
                ScreenBuffer[y * ScreenWidth + x + i].Char.UnicodeChar = c[i];
                ScreenBuffer[y * ScreenWidth + x + i].Attributes = col;
            }
        }

        void Fill(int x1, int y1, int x2, int y2, short c = 0x2588, short col = 0x000F)
        {
            Bound(x1, y1);
            Bound(x2, y2);
            for (int x = x1; x < x2; x++)
                for (int y = y1; y < y2; y++)
                    Draw(x, y, c, col);
        }

        void Bound(int &x, int &y) {
            if (x < 0) x = 0;
            if (x >= ScreenWidth) x = ScreenWidth;
            if (y < 0) y = 0;
            if (y >= ScreenHeight) y = ScreenHeight;
        }

        void Update() {
            WriteConsoleOutput(m_hConsole, ScreenBuffer, { (short)ScreenWidth, (short)ScreenHeight }, { 0,0 }, &m_rectWindow);
        }

        int GetHeight() {
            return ScreenHeight;
        }

        int GetWidth() {
            return ScreenWidth;
        }
    private:
        int width, height;
    protected:
        int ScreenWidth;
        int ScreenHeight;
        CHAR_INFO *ScreenBuffer;
        HANDLE OriginalConsole;
        CONSOLE_SCREEN_BUFFER_INFO OriginalConsoleInfo;
        HANDLE m_hConsole;
        HANDLE m_hConsoleIn;
        SMALL_RECT m_rectWindow;
};