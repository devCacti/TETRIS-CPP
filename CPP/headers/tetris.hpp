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
        setCColor(7, 0);
    }

    void run()
    {
        std::cout << "Hello, World!" << std::endl;

        // Draw some cubes to test the best cube character
        // Set color to white
        setCColor(0, 15);
        std::cout << "  " << std::endl;
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

    // Set Console Color
    void setCColor(int textColor, int bgColor)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (textColor + (bgColor * 16)));
    }
};

#endif // TETRIS_HPP