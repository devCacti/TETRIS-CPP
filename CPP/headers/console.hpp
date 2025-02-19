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

void flushConsole()
{
    // Clean the screen
    setConsoleColor(0, 0);
    system("cls");
    setConsoleColor(0, 7);
}

#endif // CONSOLE_HPP