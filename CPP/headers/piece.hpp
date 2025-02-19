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

public:
    // Public functions
    Piece()
    {
        // Constructor (no arguments)
        type = -1;
        isFalling = true;
        rotation = 0;
    }

    void newPiece()
    {
        *this = Piece((rand() % 7) - 1);
        // return *this;
    }

    void draw()
    {
        system("cls");
        // Print all the positions of the piece
        for (int i = 0; i < 4; i++)
        {
            std::cout << positions[i].X << " " << positions[i].Y << std::endl;
        }
        // Draw the piece
        setConsoleColor(getBgColor(), 0);
        for (int i = 0; i < 4; i++)
        {
            setCursorPosition(positions[i].X * 2, positions[i].Y);
            std::cout << "  ";
        }
        setConsoleColor(0, 7);
    }

    void setPos(int x, int y)
    {
        // Print x and y
        std::cout << "Setting position" << std::endl;
        std::cout << x << " " << y << std::endl
                  << std::endl;
        // Set the position of all the pieces based on the rotation point and current rotation
        switch (type)
        {
        case 0:
            // Line piece
            if ((rotation + 1) % 2)
            {
                this->positions[0] = Vector(x, y - 1);
                this->positions[1] = Vector(x, y);
                this->positions[2] = Vector(x, y + 1);
                this->positions[3] = Vector(x, y + 2);
            }
            else
            {
                this->positions[0] = Vector(x - 1, y);
                this->positions[1] = Vector(x, y);
                this->positions[2] = Vector(x + 1, y);
                this->positions[3] = Vector(x + 2, y);
            }
            break;
        case 1:
            // L piece
            this->positions[0] = Vector(x, y - 1);
            this->positions[1] = Vector(x, y);
            this->positions[2] = Vector(x, y + 1);
            this->positions[3] = Vector(x + 1, y + 1);

            if (rotation == 1)
            {
                this->positions[0] = Vector(x - 1, y);
                this->positions[1] = Vector(x, y);
                this->positions[2] = Vector(x + 1, y);
                this->positions[3] = Vector(x + 1, y - 1);
            }
            else if (rotation == 2)
            {
                this->positions[0] = Vector(x, y + 1);
                this->positions[1] = Vector(x, y);
                this->positions[2] = Vector(x, y - 1);
                this->positions[3] = Vector(x - 1, y - 1);
            }
            else if (rotation == 3)
            {
                this->positions[0] = Vector(x + 1, y);
                this->positions[1] = Vector(x, y);
                this->positions[2] = Vector(x - 1, y);
                this->positions[3] = Vector(x - 1, y + 1);
            }
            break;
        case 2:
            // J piece
            this->positions[0] = Vector(x + 1, y - 1);
            this->positions[1] = Vector(x + 1, y);
            this->positions[2] = Vector(x + 1, y + 1);
            this->positions[3] = Vector(x, y + 1);

            if (rotation == 1)
            {
                this->positions[0] = Vector(x - 1, y - 1);
                this->positions[1] = Vector(x, y - 1);
                this->positions[2] = Vector(x + 1, y - 1);
                this->positions[3] = Vector(x + 1, y);
            }
            else if (rotation == 2)
            {
                this->positions[0] = Vector(x - 1, y + 1);
                this->positions[1] = Vector(x - 1, y);
                this->positions[2] = Vector(x - 1, y - 1);
                this->positions[3] = Vector(x, y - 1);
            }
            else if (rotation == 3)
            {
                this->positions[0] = Vector(x + 1, y + 1);
                this->positions[1] = Vector(x, y + 1);
                this->positions[2] = Vector(x - 1, y + 1);
                this->positions[3] = Vector(x - 1, y);
            }
            break;
        case 3:
            // Square piece
            this->positions[0] = Vector(x, y);
            this->positions[1] = Vector(x, y + 1);
            this->positions[2] = Vector(x + 1, y);
            this->positions[3] = Vector(x + 1, y + 1);
            break;
        case 4:
            // Z piece

            this->positions[0] = Vector(x, y - 1);
            this->positions[1] = Vector(x + 1, y - 1);
            this->positions[2] = Vector(x + 1, y);
            this->positions[3] = Vector(x + 2, y);

            if (rotation == 1)
            {
                this->positions[0] = Vector(x + 1, y);
                this->positions[1] = Vector(x + 1, y + 1);
                this->positions[2] = Vector(x, y + 1);
                this->positions[3] = Vector(x, y + 2);
            }
            else if (rotation == 2)
            {
                this->positions[0] = Vector(x, y + 1);
                this->positions[1] = Vector(x - 1, y + 1);
                this->positions[2] = Vector(x - 1, y);
                this->positions[3] = Vector(x - 2, y);
            }
            else if (rotation == 3)
            {
                this->positions[0] = Vector(x - 1, y);
                this->positions[1] = Vector(x - 1, y - 1);
                this->positions[2] = Vector(x, y - 1);
                this->positions[3] = Vector(x, y - 2);
            }
            break;
        case 5:
            // S piece

            this->positions[0] = Vector(x, y + 1);
            this->positions[1] = Vector(x + 1, y + 1);
            this->positions[2] = Vector(x + 1, y);
            this->positions[3] = Vector(x + 2, y);

            if (rotation == 1)
            {
                this->positions[0] = Vector(x + 1, y);
                this->positions[1] = Vector(x + 1, y - 1);
                this->positions[2] = Vector(x, y - 1);
                this->positions[3] = Vector(x, y - 2);
            }
            else if (rotation == 2)
            {
                this->positions[0] = Vector(x, y - 1);
                this->positions[1] = Vector(x - 1, y - 1);
                this->positions[2] = Vector(x - 1, y);
                this->positions[3] = Vector(x - 2, y);
            }
            else if (rotation == 3)
            {
                this->positions[0] = Vector(x - 1, y);
                this->positions[1] = Vector(x - 1, y + 1);
                this->positions[2] = Vector(x, y + 1);
                this->positions[3] = Vector(x, y + 2);
            }
            break;
        case 6:
            // T piece

            this->positions[0] = Vector(x, y + 1);
            this->positions[1] = Vector(x + 1, y + 1);
            this->positions[2] = Vector(x + 1, y);
            this->positions[3] = Vector(x + 2, y + 1);
            if (rotation == 1)
            {
                this->positions[0] = Vector(x + 1, y);
                this->positions[1] = Vector(x + 1, y - 1);
                this->positions[2] = Vector(x, y - 1);
                this->positions[3] = Vector(x + 1, y - 2);
            }
            else if (rotation == 2)
            {
                this->positions[0] = Vector(x, y - 1);
                this->positions[1] = Vector(x - 1, y - 1);
                this->positions[2] = Vector(x - 1, y);
                this->positions[3] = Vector(x - 2, y - 1);
            }
            else if (rotation == 3)
            {
                this->positions[0] = Vector(x - 1, y);
                this->positions[1] = Vector(x - 1, y + 1);
                this->positions[2] = Vector(x, y + 1);
                this->positions[3] = Vector(x - 1, y + 2);
            }
            break;
        default:
            break;
        }

        // Print all the positions of the piece
        std::cout
            << "Positions:" << std::endl;
        for (int i = 0; i < 4; i++)
        {
            std::cout << positions[i].X << " " << positions[i].Y << std::endl;
        }
        Sleep(1000);
    }

    int
    getBgColor()
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

    void move(Vector direction)
    {
        // Move the piece in a direction
        for (int i = 0; i < 4; i++)
        {
            positions[i] = positions[i] + direction;
        }
    }

    // The rotate function is complex and needs to be well executed
    void rotate()
    {
    }

private:
    Piece(int type)
    {
        // Constructor (with arguments)
        isFalling = true;
        this->type = type;
        switch (type)
        {
        case 0:
            // Line piece
            positions[0] = Vector(0, 0);
            positions[1] = Vector(0, 1);
            positions[2] = Vector(0, 2);
            positions[3] = Vector(0, 3);
            break;
        case 1:
            // L piece
            positions[0] = Vector(0, 0);
            positions[1] = Vector(0, 1);
            positions[2] = Vector(0, 2);
            positions[3] = Vector(1, 2);
            break;
        case 2:
            // J piece
            positions[0] = Vector(1, 0);
            positions[1] = Vector(1, 1);
            positions[2] = Vector(1, 2);
            positions[3] = Vector(0, 2);
            break;
        case 3:
            // Square piece
            positions[0] = Vector(0, 0);
            positions[1] = Vector(0, 1);
            positions[2] = Vector(1, 0);
            positions[3] = Vector(1, 1);
            break;
        case 4:
            // Z piece
            positions[0] = Vector(0, 0);
            positions[1] = Vector(1, 0);
            positions[2] = Vector(1, 1);
            positions[3] = Vector(2, 1);
            break;
        case 5:
            // S piece
            positions[0] = Vector(0, 1);
            positions[1] = Vector(1, 1);
            positions[2] = Vector(1, 0);
            positions[3] = Vector(2, 0);
            break;
        case 6:
            // T piece
            positions[0] = Vector(0, 1);
            positions[1] = Vector(1, 1);
            positions[2] = Vector(1, 0);
            positions[3] = Vector(2, 1);
            break;
        default:
            break;
        }
    }
};

#endif // PIECE_HPP