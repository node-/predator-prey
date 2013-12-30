/* coordinate.cpp
 *
 *
 * -- Jake Kosberg
 * -- CS 3A
 */

#include "coordinate.h"

Coordinate::Coordinate()
{
    x = 0;
    y = 0;
}

Coordinate::Coordinate(int X, int Y)
{
    x = X;
    y = Y;
}

Coordinate::Coordinate(Coordinate const &copy)
{
    x = copy.x;
    y = copy.y;
}

Coordinate& Coordinate::operator=(Coordinate const &copy)
{
    x = copy.x;
    y = copy.y;
    return *this;
}

void Coordinate::add(int X, int Y)
{
    x += X;
    y += Y;
}

bool operator==(Coordinate const &lhs, Coordinate const &rhs)
{
    return lhs.x == rhs.x && lhs.y == rhs.y;
}

std::ostream& operator<<(std::ostream& out, Coordinate coord)
{
    out << "(" << coord.x << ", " << coord.y << ")";
    return out;
}