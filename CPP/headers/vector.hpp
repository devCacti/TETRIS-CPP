#ifndef VECTOR_HPP
#define VECTOR_HPP

class Vector
{
public:
    int X;
    int Y;

    Vector(int x, int y)
    {
        X = x;
        Y = y;
    }

    Vector()
    {
        X = 0;
        Y = 0;
    }

    // Overload the + operator
    Vector operator+(const Vector &other) const
    {
        // Return a new vector that is the sum of this vector and the other vector
        return Vector(X + other.X, Y + other.Y);
    }
};

#endif // VECTOR_HPP