#ifndef PIECE_HPP
#define PIECE_HPP

#include "vector.hpp"
#include "console.hpp"

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
    // int color; // Redundant
    int type;
    int rotation; // 0 - 3
    bool isFalling;
    bool isMoving;

public:
    // Public functions
    Piece()
    {
        // Constructor (no arguments)
        type = -1;
        isFalling = true;
        isMoving = true;
        rotation = 0;
    }

    // Change the piece to a new random piece
    void NewPiece()
    {
        *this = Piece((rand() % 7) - 1);
    }

    void Draw(int e = 0)
    {
        if (e && isFalling)
        {
            // Errase before moving
            SetConsoleColor(0, 0);
            for (int i = 0; i < 4; i++)
            {
                SetCursorPosition(positions[i].X * 2, positions[i].Y);
                std::cout << "  ";
            }
            return;
        }
        // Draw the piece
        SetConsoleColor(GetBgColor(), 0);
        // SetConsoleColor(0, GetBgColor());

        for (int i = 0; i < 4; i++)
        {
            SetCursorPosition(positions[i].X * 2, positions[i].Y);
            std::cout << "  ";
        }
        SetConsoleColor(7, 0);
    }

    void Move(int x, int y)
    {
        if (!isFalling && y)
        {
            SetConsoleColor(1, 5);
            std::cout << "Disabled 3";
            return;
        }

        // If it's not allowed to move and the Function is called to move from side to side
        // Return, as the piece should not move anymore
        if (!isMoving && x)
        {
            SetConsoleColor(1, 5);
            std::cout << "Disabled 2";
            return;
        }

        for (int i = 0; i < 4; i++)
        {
            if (positions[i].Y >= 20 && y)
            {
                SetConsoleColor(1, 5);
                std::cout << "Disabled 1";

                isFalling = false;
                return;
            }
        }

        // Move the entire piece by x and y
        // Positive x moves right, negative x moves left
        // Positive y moves down, negative y moves up
        for (int i = 0; i < 4; i++)
        {
            positions[i] = Vector(positions[i].X + x, positions[i].Y + y);
        }
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
    }

private:
    Piece(int type)
    {
        // Constructor (with arguments)
        isFalling = true;
        isMoving = true;
        rotation = 0;
        this->type = type;
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
    }
};

#endif // PIECE_HPP