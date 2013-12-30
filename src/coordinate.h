/* Coordinate data type holds an X and a Y coordinate for Cartesian planes.
 *
 *
 * -- Jake Kosberg
 * -- CS 3A
 */

#ifndef _COORDINATE_H_
#define _COORDINATE_H_

#include <iostream>

class Coordinate
{
public:
    int x;
    int y;
    
    Coordinate();
    Coordinate(int X, int Y);
    Coordinate(Coordinate const &copy);
    void add(int X, int Y);
    
    Coordinate& operator=(Coordinate const &copy);
    friend bool operator==(Coordinate const &lhs, Coordinate const &rhs);
    friend std::ostream& operator<<(std::ostream &out, Coordinate coord);
};

#endif // _COORDINATE_H_
