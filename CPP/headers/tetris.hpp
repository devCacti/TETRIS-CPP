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

    static void Run();

public:
    // Public functions
    Tetris() // Constructor (no arguments)
    {
        srand(time(0)); // Seed the random number generator
        // Create a new piece
        // Allocate memory for a single piece
        for (int i = 0; i < 7; i++)
        {
            pieces.push_back(Piece());
            pieces[i].NewPiece();
        }

        std::setlocale(LC_ALL, ""); // Set the locale to UTF-8
    };

    ~Tetris()
    {
        // Destructor
        // Set color back to normal
        SetConsoleColor(7, 0);
    }

    void Game()
    {
        std::cout << std::endl;

        // Render the tetris text
        RenderTetris();

        // Test colors
        //! TestColors();

        // Clear the console
        FlushConsole();

        char key;
        start = GetTickCount();
        while (1)
        {
            key = 0;
            Render(); // Clean the piece

            if (_kbhit()) // Keyboard hit
            {
                key = _getch();

                // Only using WASD keys
                switch (key)
                {
                case 'w':
                    // Rotate the piece
                    pieces[0].Rotate();
                    break;
                case 'a':
                    // Move the piece left
                    pieces[0].Move(-1, 0);
                    break;
                case 's':
                    // Move the piece down
                    pieces[0].Move(0, 1);
                    break;
                case 'd':
                    // Move the piece right
                    pieces[0].Move(1, 0);
                    break;
                case 'q':
                    // Quit the Run
                    return;
                }
            }
            Update();
            Sleep(10); // To avoid 100% CPU usage
        }
        // Read ANY key from the user to close the console
        _getch();
    }

    void TestColors()
    {
        std::cout << std::endl
                  << "Testing colors" << std::endl;
        Sleep(250);
        for (int i = 0; i < 16; i++)
        {
            SetConsoleColor(i, i == 0 ? 15 : 0);
            std::cout << "Color";
            Sleep(10);

            SetConsoleColor(0, 15);
            std::cout << " " << i << std::endl;
            Sleep(20);
        }

        Sleep(250);
        ResetColor();
    }

private:
    int start = 0;
    const int delay = 500; // Delay in milliseconds

    void Update()
    {
        // Update the game
        // FlushConsole();
        if (GetTickCount() - start >= delay)
        {
            start = GetTickCount();
            pieces[0].Move(0, 1);
            std::cout << pieces[0].positions[0].Y << std::endl;
        }
        Render();
    }

    void Render(int type = 0)
    {
        // Render the game, it is a console game so it is printed to the console
        pieces[0].Draw(0);
    }

    // Render a text saying "Tetris" using blocks (white spaces)
    void RenderTetris()
    {
        char l1[] = "XXXXX XXXX XXXXX XXXX  XXXXX  XXXXX";
        char l2[] = "  X   X      X   X   X   X   X";
        char l3[] = "  X   XXX    X   XXXX    X    XXXX";
        char l4[] = "  X   X      X   X   X   X        X";
        char l5[] = "  X   XXXX   X   X   X XXXXX XXXXX";

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
                    Sleep(1);
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

void Tetris::Run()
{
    // Code for hiding the cursor
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;

    GetConsoleCursorInfo(hOut, &cursorInfo);
    cursorInfo.bVisible = false; // esconder
    SetConsoleCursorInfo(hOut, &cursorInfo);

    // Create a new Tetris game
    Tetris tetris;

    // Run the game
    tetris.Game();
}

#endif // TETRIS_HPP