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

        const int delay = 500;
        int start = GetTickCount();

        FlushConsole();

        char key;
        while (1)
        {
            key = 0;

            if (_kbhit())
            {
                key = _getch();

                // Only using WASD keys
                switch (key)
                {
                case 'w':
                    // Rotate the piece
                    pieces[0].Rotate();
                    update();
                    break;
                case 'a':
                    // Move the piece left
                    pieces[0].Move(-1, 0);
                    update();
                    break;
                case 's':
                    // Move the piece down
                    pieces[0].Move(0, 1);
                    update();
                    break;
                case 'd':
                    // Move the piece right
                    pieces[0].Move(1, 0);
                    update();
                    break;
                case 'q':
                    // Quit the game
                    return;

                    // default:
                    //     return;
                }
            }

            if (GetTickCount() - start >= delay)
            {
                start = GetTickCount();
                pieces[0].Move(0, 1);
                update();
            }
            Sleep(10); // To avoid 100% CPU usage
        }

        int i = 0;
        for (auto &piece : pieces)
        {
            i++;
            piece.Move(i * 5, i * 2);
            piece.rotation = 0;
            // Show All pieces
            FlushConsole();
            for (int j = 0; j < i; j++)
            {
                pieces[j].Draw();
            }
            Sleep(500);
            piece.Rotate();
            // Show All pieces
            FlushConsole();
            for (int j = 0; j < i; j++)
            {
                pieces[j].Draw();
            }
            piece.Rotate();
            Sleep(500);
            // Show All pieces
            FlushConsole();
            for (int j = 0; j < i; j++)
            {
                pieces[j].Draw();
            }
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
        // FlushConsole();
        pieces[0].Draw(1);
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