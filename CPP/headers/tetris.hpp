// tetris.hpp only because it's purely for C++ and not for C
// This file is the header file for the tetris game

#ifndef TETRIS_HPP
#define TETRIS_HPP

// Purely C++ includes
#include <iostream>
#include <locale>
#include <ctime>
#include <cstdlib>
#include <vector>

// C and C++ includes
#include <windows.h>
#include <malloc.h>
#include <conio.h>

// Custom includes (headers) (C++ only)
#include "vector.hpp"
#include "piece.hpp"
#include "console.hpp"

using namespace std;

class Tetris
{
public:
    // Public variables
    std::vector<Piece> pieces;

public:
    // Public functions
    Tetris() // Constructor (no arguments)
    {
        // Create a new piece
        // Allocate memory for a single piece
        for (int i = 0; i < 7; i++)
        {
            pieces.push_back(Piece());
            pieces[i].NewPiece();
        }

        srand(time(0));             // Seed the random number generator
        std::setlocale(LC_ALL, ""); // Set the locale to UTF-8
    };

    ~Tetris()
    {
        // Destructor
        // Set color back to normal
        SetConsoleColor(7, 0);
    }

    void Run()
    {
        RenderTetris();
        std::cout << std::endl;
        TestColors();

        int i = 0;
        for (auto &piece : pieces)
        {
            FlushConsole();
            for (int j = 0; j < i; j++)
            {
                pieces[j].Draw();
            }
            i++;
            piece.Move(i * 5, i * 2);
            Sleep(250);
            piece.Draw();
            piece.Rotate();
            Sleep(250);
            piece.Draw();
            Sleep(500);
        }

        // Read ANY key from the user to close the console
        _getch();
    }

    void TestColors()
    {
        std::cout << std::endl
                  << "Testing colors" << std::endl;
        Sleep(1000);
        for (int i = 0; i < 16; i++)
        {
            SetConsoleColor(i, i == 0 ? 15 : 0);
            std::cout << "Color";
            Sleep(10);

            SetConsoleColor(0, 15);
            std::cout << " " << i << std::endl;
            Sleep(20);
        }

        Sleep(1000);
        ResetColor();
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
    void RenderTetris()
    {
        char l1[] = "XXXXX XXXX XXXXX XXXX  XXXXX   XXXXX";
        char l2[] = "  X   X      X   X   X   X    X";
        char l3[] = "  X   XXX    X   XXXX    X     XXXX";
        char l4[] = "  X   X      X   X   X   X         X";
        char l5[] = "  X   XXXX   X   X   X XXXXX  XXXXX";

        char *lines[] = {l1, l2, l3, l4, l5};

        // Clear the console
        FlushConsole();

        for (int j = 0; j < 5; j++)
        {
            for (int i = 0; i < strlen(lines[j]); i++)
            {
                if (lines[j][i] == 'X')
                {
                    // If there is an X print a white space
                    SetConsoleColor(15, 0);
                    cout << " ";
                    Sleep(10);
                }
                else
                {
                    // If there is no X print a black space
                    SetConsoleColor(0, 0);
                    cout << " ";
                    Sleep(1);
                }
            }
            Sleep(10);
            cout << endl;
        }

        ResetColor();
    }

    void ResetColor()
    {
        SetConsoleColor(0, 7);
    }
};

#endif // TETRIS_HPP