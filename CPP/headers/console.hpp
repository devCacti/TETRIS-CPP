#ifndef CONSOLE_HPP
#define CONSOLE_HPP

#include <iostream>
#include <windows.h>

void SetCursorPosition(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void SetConsoleColor(int bg, int fg)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), bg * 16 + fg);
}

void FlushConsole()
{
    // Clean the screen
    SetConsoleColor(0, 0);
    system("cls");
    SetConsoleColor(0, 7);
}

#endif // CONSOLE_HPP