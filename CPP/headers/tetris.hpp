// tetris.hpp only because it's purely for C++ and not for C
// This file is the header file for the tetris game

#ifndef TETRIS_HPP
#define TETRIS_HPP

#include <iostream>
#include <locale>
#include <conio.h>
#include <windows.h>

#include "vector.hpp"

using namespace std;

class Tetris
{
public:
    // Public variables
    Vector position;

public:
    // Public functions
    Tetris() // Constructor (no arguments)
    {
        std::setlocale(LC_ALL, ""); // Set the locale to UTF-8
        position = Vector();
    };

    ~Tetris()
    {
        // Destructor
        // Set color back to normal
        setConsoleColor(7, 0);
    }

    void run()
    {
        renderTetris();

        // Read ANY key from the user to close the console
        _getch();
    }

private:
    void update()
    {
        // Update the game
    }

    void render()
    {
        // Render the game, it is a console game so it is printed to the console
    }

    // Render a text saying "Tetris" using blocks (white spaces)
    void renderTetris()
    {
        char l1[] = "XXXXX XXX XXXXX XXX   XXXXX   XXXX";
        char l2[] = "  X   X     X   X  X    X    X";
        char l3[] = "  X   XX    X   XXX     X     XXX";
        char l4[] = "  X   X     X   X  X    X        X";
        char l5[] = "  X   XXX   X   X  X  XXXXX  XXXX";

        char *lines[] = {l1, l2, l3, l4, l5};

        for (int j = 0; j < 5; j++)
        {
            for (int i = 0; i < strlen(lines[j]); i++)
            {
                if (lines[j][i] == 'X')
                {
                    setConsoleColor(0, 15);
                    cout << "  ";
                }
                else
                {
                    setConsoleColor(0, 0);
                    cout << "  ";
                }
                Sleep(10);
            }
            cout << endl;
        }

        resetColor();

        // X X X X X  X X X  X X X X X  X X X    X X X X X    X X X X
        //    X       X          X      X     X      X      X
        //    X       X X        X      X X X        X        X X X
        //    X	      X          X      X     X      X              X
        //    X	      X X X      X      X     X  X X X X X  X X X X
        //
        // X represents a white space and nothing means a black space
    }

    void resetColor()
    {
        setConsoleColor(7, 0);
    }

    // Set Console Color
    void setConsoleColor(int textColor, int bgColor)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (textColor + (bgColor * 16)));
    }

    // Set Cursor Position
    void setCursorPosition(int x, int y)
    {
        COORD coord;
        coord.X = x;
        coord.Y = y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    }
};

#endif // TETRIS_HPP