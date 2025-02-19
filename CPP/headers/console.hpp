#ifndef CONSOLE_HPP
#define CONSOLE_HPP

#include <iostream>
#include <windows.h>

void setCursorPosition(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void setConsoleColor(int bg, int fg)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), bg * 16 + fg);
}

#endif // CONSOLE_HPP