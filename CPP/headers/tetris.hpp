// tetris.hpp only because it's purely for C++ and not for C
// This file is the header file for the tetris game

#ifndef TETRIS_HPP
#define TETRIS_HPP

#include <iostream>
#include <locale>
#include <conio.h>
#include <windows.h>
#include <ctime>
#include <cstdlib>

#include "vector.hpp"
#include "piece.hpp"
#include "console.hpp"

using namespace std;

class Tetris
{
public:
    // Public variables
    Piece piece[1];

public:
    // Public functions
    Tetris() // Constructor (no arguments)
    {
        srand(time(0));             // Seed the random number generator
        std::setlocale(LC_ALL, ""); // Set the locale to UTF-8
        piece[0].newPiece();        // Create a new piece
        piece[0].setPos(10, 20);    // Set the position of the piece
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
        std::cout << std::endl;
        testColors();
        piece[0].draw(); // Draw the piece

        // Read ANY key from the user to close the console
        _getch();
    }

    void testColors()
    {
        std::cout << std::endl
                  << "Testing colors" << std::endl;
        for (int i = 0; i < 16; i++)
        {
            setConsoleColor(15, i);
            std::cout << "Color";
            setConsoleColor(15, 0);
            std::cout << " " << i << std::endl;
        }
    }

    void setConsoleColor(int textColor, int bgColor)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (textColor + (bgColor * 16)));
    }

    void setCursorPosition(int x, int y)
    {
        COORD coord;
        coord.X = x;
        coord.Y = y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
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
        char l3[] = "  X   XX    X   XXX     X     XXXX";
        char l4[] = "  X   X     X   X  X    X         X";
        char l5[] = "  X   XXX   X   X  X  XXXXX   XXXX";

        char *lines[] = {l1, l2, l3, l4, l5};

        // Clear the console
        system("cls");

        for (int j = 0; j < 5; j++)
        {
            for (int i = 0; i < strlen(lines[j]); i++)
            {
                if (lines[j][i] == 'X')
                {
                    // If there is an X print a white space
                    setConsoleColor(0, 15);
                    cout << " ";
                    Sleep(25);
                }
                else
                {
                    // If there is no X print a black space
                    setConsoleColor(0, 0);
                    cout << " ";
                    Sleep(5);
                }
            }
            Sleep(20);
            cout << endl;
        }

        resetColor();
    }

    void resetColor()
    {
        setConsoleColor(7, 0);
    }
};

#endif // TETRIS_HPP