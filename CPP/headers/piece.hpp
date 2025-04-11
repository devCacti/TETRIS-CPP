#ifndef PIECE_HPP
#define PIECE_HPP

#include "vector.hpp"
#include "console.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;

/// <summary>
/// These are the pieces that exist in the game
/// X R X X (Line piece)    0 - Light blue
///
/// X R X   (L piece)       1 - Orange
/// X
///
/// X R X   (J piece)       2 - Blue
///     X
///
/// R R     (Square piece)  3 - Yellow
/// R R
///
/// X R     (Z piece)       4 - Red
///   X X
///
///   R X   (S piece)       5 - Green
/// X X
///
/// X R X   (T piece)       6 - Purple
///   X
///
/// R = Rotation point + Block
/// X = Block
/// </summary>

class Piece
{
public:
    // Public variables
    Vector positions[4];
    int type;
    int rotation; //* 0 - 3
    bool isMoving;
    //// int color; // Redundant

private:
    // Private variables
    int fallSpeed;   //* Speed of falling
    int fieldStartX; //* X position of the field
    int fieldStartY; //* Y position of the field
    int fieldWidth;  //* Width of the field
    int fieldHeight; //* Height of the field

    // Private variables (used for the game)
    int score; //! Unused
    int level; //! Unused
    int lines; //! Unused

    Vector pastPositions[4];

public:
    // Public functions
    Piece()
    {
        // Constructor (no arguments)
        type = -1;
        isMoving = true;
        rotation = 0;

        // Set the default settings of the game
        SetDefaultSettings();
    }

    // Change the piece to a new random piece
    void NewPiece()
    {
        *this = Piece((rand() % 7) - 1);
    }

    void Draw(int e = 0)
    {
        // Draw the piece
        if (e == 0)
        {

            SetConsoleColor(GetBgColor(), 0);
            // SetConsoleColor(0, GetBgColor());

            for (int i = 0; i < 4; i++)
            {
                SetCursorPosition(positions[i].X * 2, positions[i].Y);
                std::cout << "  ";
            }
        }

        if (e == 0 || e == 1)
        {
            // Errase after moving (So that the piece doesn't leave a trail)
            SetConsoleColor(0, 0);
            for (int i = 0; i < 4; i++)
            {
                bool skip = false;
                for (int j = 0; j < 4; j++)
                {
                    if (pastPositions[i].X == positions[j].X && pastPositions[i].Y == positions[j].Y)
                    {
                        // Continue skips the rest of the loop
                        skip = true; // Don't erase the piece if it is not moving
                        break;       // Break the loop
                    }
                }
                if (skip)
                {
                    // If the piece is not moving, skip the rest of the loop
                    continue;
                }
                ////if (pastPositions[i].X == positions[i].X && pastPositions[i].Y == positions[i].Y)
                ////{
                ////    // Continue skips the rest of the loop
                ////    continue; // Don't erase the piece if it is not moving
                ////}

                // Erase the piece
                SetCursorPosition(pastPositions[i].X * 2, pastPositions[i].Y);
                std::cout << "  ";
            }
            return;
        }

        // Set to the default color (Black background white white text)
        SetConsoleColor(7, 0);
    }

    void Move(int x, int y)
    {

        // If it's not allowed to move and the Function is called to move from side to side
        // Return, as the piece should not move anymore
        if (!isMoving && x)
        {
            SetConsoleColor(1, 5);
            std::cout << "Disabled 1";
            return;
        }

        // If the piece is trying to move outside the field
        for (int i = 0; i < 4; i++)
        {
            if (positions[i].X + x < fieldStartX || positions[i].X + x > fieldStartX + fieldWidth && x)
            {
                SetConsoleColor(1, 5);
                std::cout << "Disabled 2";
                return;
            }

            if (positions[i].Y + y < fieldStartY || positions[i].Y + y > fieldStartY + fieldHeight && y)
            {
                SetConsoleColor(1, 5);
                std::cout << "Disabled 3";
                return;
            }
        }

        // Move the entire piece by x and y
        // Positive x moves right, negative x moves left
        // Positive y moves down, negative y moves up

        // Set the past positions
        SetPastPositions();

        for (int i = 0; i < 4; i++)
        {
            positions[i] = Vector(positions[i].X + x, positions[i].Y + y);
        }
        Draw(); // For a cleaner update, to avoid leaving trails
    }

    int GetBgColor()
    {
        switch (type)
        {
        case 0:
            return 11; // Light blue
            break;
        case 1:
            return 12; // Orange (Not really orange)
            break;
        case 2:
            return 1; // Blue
            break;
        case 3:
            return 14; // Yellow
            break;
        case 4:
            return 4; // Red
            break;
        case 5:
            return 10; // Green
            break;
        case 6:
            return 5; // Purple
            break;

        default:
            return 15;
            break;
        }
    }

    // The rotate function is complex and needs to be well executed
    void Rotate(int direction = 1)
    {
        SetPastPositions();

        // Rotate the piece based on the input direction
        // direction = 1 -> Rotate clockwise
        // direction = 0 -> Rotate counter-clockwise

        // The rotation point is the second block of the piece
        Vector rotationPoint = positions[1];
        rotation += 1 * direction;
        if (rotation > 3)
        {
            rotation = 0;
        }
        else if (rotation < 0)
        {
            rotation = 3;
        }

        // Rotating the piece
        switch (type)
        {
            // Rotate pieces in 90 degrees
        case 0:
            // Line piece (Light blue)
            switch (rotation)
            {
            case 0:
            case 2:
                positions[0] = rotationPoint + Vector(0, -1);
                positions[2] = rotationPoint + Vector(0, 1);
                positions[3] = rotationPoint + Vector(0, 2);
                break;
            case 1:
            case 3:
                positions[0] = rotationPoint + Vector(-1, 0);
                positions[2] = rotationPoint + Vector(1, 0);
                positions[3] = rotationPoint + Vector(2, 0);
                break;
            default:
                break;
            }
            break;
        case 1:
            // L piece (Orange)
            switch (rotation)
            {
            case 0:
                // L is upright
                positions[0] = rotationPoint + Vector(0, -1);
                positions[2] = rotationPoint + Vector(0, 1);
                positions[3] = rotationPoint + Vector(1, 1);
                break;
            case 1:
                // L tilted to the right
                positions[0] = rotationPoint + Vector(1, 0);
                positions[2] = rotationPoint + Vector(-1, 0);
                positions[3] = rotationPoint + Vector(-1, 1);
                break;
            case 2:
                // L is upside down
                positions[0] = rotationPoint + Vector(0, 1);
                positions[2] = rotationPoint + Vector(0, -1);
                positions[3] = rotationPoint + Vector(-1, -1);
                break;
            case 3:
                // L tilted to the left
                positions[0] = rotationPoint + Vector(-1, 0);
                positions[2] = rotationPoint + Vector(1, 0);
                positions[3] = rotationPoint + Vector(1, -1);
                break;
            default:
                break;
            }
            break;
        case 2:
            // J piece (Blue) (Inverted L)
            switch (rotation)
            {
            case 0:
                // J is upright
                positions[0] = rotationPoint + Vector(0, -1);
                positions[2] = rotationPoint + Vector(0, 1);
                positions[3] = rotationPoint + Vector(-1, 1);
                break;
            case 1:
                // J tilted to the right
                positions[0] = rotationPoint + Vector(1, 0);
                positions[2] = rotationPoint + Vector(-1, 0);
                positions[3] = rotationPoint + Vector(-1, -1);
                break;
            case 2:
                // J is upside down
                positions[0] = rotationPoint + Vector(0, 1);
                positions[2] = rotationPoint + Vector(0, -1);
                positions[3] = rotationPoint + Vector(1, -1);
                break;
            case 3:
                // J tilted to the left
                positions[0] = rotationPoint + Vector(-1, 0);
                positions[2] = rotationPoint + Vector(1, 0);
                positions[3] = rotationPoint + Vector(1, 1);
                break;
            default:
                break;
            }
            break;
        case 3:
            // Square piece (Yellow)
            break;
        case 4:
            // Z piece (Red)
            switch (rotation)
            {
            case 0:
            case 2:
                // Z is upright
                positions[0] = rotationPoint + Vector(-1, 0);
                positions[2] = rotationPoint + Vector(0, 1);
                positions[3] = rotationPoint + Vector(1, 1);
                break;
            case 1:
            case 3:
                // Z is tilted
                positions[0] = rotationPoint + Vector(0, -1);
                positions[2] = rotationPoint + Vector(-1, 0);
                positions[3] = rotationPoint + Vector(-1, 1);
                break;
            default:
                break;
            }
            break;
        case 5:
            // S piece (Green)
            switch (rotation)
            {
            case 0:
            case 2:
                // S is upright
                positions[0] = rotationPoint + Vector(-1, 0);
                positions[2] = rotationPoint + Vector(0, -1);
                positions[3] = rotationPoint + Vector(1, -1);
                break;
            case 1:
            case 3:
                // S is tilted
                positions[0] = rotationPoint + Vector(0, -1);
                positions[2] = rotationPoint + Vector(1, 0);
                positions[3] = rotationPoint + Vector(1, 1);
                break;
            default:
                break;
            }
            break;
        case 6:
            // T piece (Purple)
            switch (rotation)
            {
            case 0:
                // T is upright
                positions[0] = rotationPoint + Vector(-1, 0);
                positions[2] = rotationPoint + Vector(1, 0);
                positions[3] = rotationPoint + Vector(0, -1);
                break;
            case 1:
                // T is tilted to the right
                positions[0] = rotationPoint + Vector(0, -1);
                positions[2] = rotationPoint + Vector(0, 1);
                positions[3] = rotationPoint + Vector(1, 0);
                break;
            case 2:
                // T is upside down
                positions[0] = rotationPoint + Vector(1, 0);
                positions[2] = rotationPoint + Vector(-1, 0);
                positions[3] = rotationPoint + Vector(0, 1);
                break;
            case 3:
                // T is tilted to the left
                positions[0] = rotationPoint + Vector(0, 1);
                positions[2] = rotationPoint + Vector(0, -1);
                positions[3] = rotationPoint + Vector(-1, 0);
                break;
            }

        default:
            break;
        }

        // Check if the piece is out of bounds after rotation
        for (int i = 0; i < 4; i++)
        {
            //? Horizontal Check
            if (positions[i].X < fieldStartX)
            {
                // If it's possible to pull it inside the field, do it
                for (int j = 0; j < 4; j++)
                {
                    positions[j].X++;
                }
                break;
            }
            if (positions[i].X > fieldStartX + fieldWidth)
            {
                // If it's possible to pull it inside the field, do it
                for (int j = 0; j < 4; j++)
                {
                    positions[j].X--;
                }
                break;
            }

            //? Vertical Check
            if (positions[i].Y < fieldStartY)
            {
                // If it's possible to pull it inside the field, do it
                for (int j = 0; j < 4; j++)
                {
                    positions[j].Y++;
                }
                break;
            }
            if (positions[i].Y > fieldStartY + fieldHeight)
            {
                // If it's possible to pull it inside the field, do it
                for (int j = 0; j < 4; j++)
                {
                    positions[j].Y--;
                }
                break;
            }
        }
    }

private:
    Piece(int type)
    {
        // Constructor (with arguments)
        isMoving = true;
        rotation = 0;
        this->type = type;

        // Set the default settings of the game
        SetDefaultSettings();

        switch (type)
        {
        case 0:
            // Line piece
            positions[0] = Vector(0, 0);
            positions[1] = Vector(0, 1); // Rotation point
            positions[2] = Vector(0, 2);
            positions[3] = Vector(0, 3);
            break;
        case 1:
            // L piece
            positions[0] = Vector(0, 0);
            positions[1] = Vector(0, 1); // Rotation point
            positions[2] = Vector(0, 2);
            positions[3] = Vector(1, 2);
            break;
        case 2:
            // J piece
            positions[0] = Vector(1, 0);
            positions[1] = Vector(1, 1); // Rotation point
            positions[2] = Vector(1, 2);
            positions[3] = Vector(0, 2);
            break;
        case 3:
            // Square piece
            positions[0] = Vector(0, 0);
            positions[1] = Vector(0, 1); // Rotation point
            positions[2] = Vector(1, 0);
            positions[3] = Vector(1, 1);
            break;
        case 4:
            // Z piece
            positions[0] = Vector(0, 0);
            positions[1] = Vector(1, 0); // Rotation point
            positions[2] = Vector(1, 1);
            positions[3] = Vector(2, 1);
            break;
        case 5:
            // S piece
            positions[0] = Vector(0, 1);
            positions[1] = Vector(1, 1); // Rotation point
            positions[2] = Vector(1, 0);
            positions[3] = Vector(2, 0);
            break;
        case 6:
            // T piece
            positions[0] = Vector(0, 1);
            positions[1] = Vector(1, 1); // Rotation point
            positions[2] = Vector(1, 0);
            positions[3] = Vector(2, 1);
            break;
        default:
            break;
        }

        // Set the proper place of the pieces, making sure they are in the middle of the field and not at the top left
        for (int i = 0; i < 4; i++)
        {
            positions[i].X += fieldStartX + (fieldWidth / 2);
            positions[i].Y += fieldStartY;
        }
    }

    void SetPastPositions()
    {
        // Set the past positions of the piece
        for (int i = 0; i < 4; i++)
        {
            pastPositions[i] = positions[i];
        }
    }

    void SetDefaultSettings()
    {
        // Get the settings of the game
        fieldStartX = 0;
        fieldStartY = 0;
        fieldWidth = 10;
        fieldHeight = 20;
        fallSpeed = 1;

        // Read the settings from the settings.json file, if it exists in the same directory as the program
        // If the file doesn't exist, leave the hardcoded values

        // Open the file
        try
        {

            std::ifstream file("settings.json");
            if (file.is_open())
            {
                // As we don't have access to a json library, we will read the file line by line and parse it manually
                std::string line;
                while (std::getline(file, line))
                {
                    // If the line contains "fieldStartX", set the fieldStartX variable to the value in the file
                    if (line.find("fieldStartX") != std::string::npos)
                    {
                        fieldStartX = std::stoi(line.substr(line.find(":") + 1));
                    }
                    // If the line contains "fieldStartY", set the fieldStartY variable to the value in the file
                    else if (line.find("fieldStartY") != std::string::npos)
                    {
                        fieldStartY = std::stoi(line.substr(line.find(":") + 1));
                    }
                    // If the line contains "fieldWidth", set the fieldWidth variable to the value in the file
                    else if (line.find("fieldWidth") != std::string::npos)
                    {
                        fieldWidth = std::stoi(line.substr(line.find(":") + 1));
                    }
                    // If the line contains "fieldHeight", set the fieldHeight variable to the value in the file
                    else if (line.find("fieldHeight") != std::string::npos)
                    {
                        fieldHeight = std::stoi(line.substr(line.find(":") + 1));
                    }
                }
            }
        }
        catch (std::ifstream::failure &e)
        {
            // If the file doesn't exist, leave the hardcoded values
            std::cout << "Error opening file: " << e.what() << std::endl;
        }
    }
};

#endif // PIECE_HPP