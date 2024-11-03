#include "display.hpp"


Display::Display() {
    m_hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    m_hConsoleIn = GetStdHandle(STD_INPUT_HANDLE);
}

int Display::Create(int width, int height, int fontw, int fonth) {
    if (m_hConsole == INVALID_HANDLE_VALUE)
        return 0;

    ScreenWidth = width;
    ScreenHeight = height;

    m_rectWindow = { 0, 0, 1, 1 };
    SetConsoleWindowInfo(m_hConsole, TRUE, &m_rectWindow);

    COORD coord = { (short)ScreenWidth, (short)ScreenHeight };
    if (!SetConsoleScreenBufferSize(m_hConsole, coord))
        return 0;

    if (!SetConsoleActiveScreenBuffer(m_hConsole))
        return 0;

    CONSOLE_FONT_INFOEX cfi;
    cfi.cbSize = sizeof(cfi);
    cfi.nFont = 0;
    cfi.dwFontSize.X = fontw;
    cfi.dwFontSize.Y = fonth;
    cfi.FontFamily = FF_DONTCARE;
    cfi.FontWeight = FW_NORMAL;

    wcscpy_s(cfi.FaceName, L"Consolas");
    if (!SetCurrentConsoleFontEx(m_hConsole, false, &cfi))
        return 0;

    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if(!GetConsoleScreenBufferInfo(m_hConsole, &csbi))
        return 0;

    // Set Physical Console Window Size
    m_rectWindow = { 0, 0, (short)(ScreenWidth - 1), (short)(ScreenHeight - 1) };
    if(!SetConsoleWindowInfo(m_hConsole, TRUE, &m_rectWindow))
        return 0;

    // Set flags to allow mouse input		
    if(!SetConsoleMode(m_hConsoleIn, ENABLE_EXTENDED_FLAGS | ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT))
        return 0;

    // Allocate memory for screen buffer
    ScreenBuffer = new CHAR_INFO[ScreenWidth * ScreenHeight];
    memset(ScreenBuffer, 0, sizeof(CHAR_INFO) * ScreenWidth * ScreenHeight);
    return 1;
}
