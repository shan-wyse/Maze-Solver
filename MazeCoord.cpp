// ***********************************************************************
// ** M A Z E   C O O R D   C L A S S   M E M B E R   F U N C T I O N S **
// ***********************************************************************

#include <iostream>
#include "MazeCoord.h"

// Implementation of operator overloading functions

// Relational operators
bool operator==(const MazeCoord coordA, const MazeCoord coordB) {
    return (coordA.x == coordB.x && coordA.y == coordB.y) ? true : false;
}
bool operator!=(const MazeCoord coordA, const MazeCoord coordB) {
    return (coordA.x != coordB.x || coordA.y != coordB.y) ? true : false;
}
bool operator>=(const MazeCoord coordA, const MazeCoord coordB) {
    return (coordA.x >= coordB.x || coordA.y >= coordB.y) ? true : false;
}
bool operator<=(const MazeCoord coordA, const MazeCoord coordB) {
    return (coordA.x <= coordB.x || coordA.y <= coordB.y) ? true : false;
}
bool operator>(const MazeCoord coordA, const MazeCoord coordB) {
    return (coordA.x > coordB.x || coordA.y > coordB.y) ? true : false;
}
bool operator<(const MazeCoord coordA, const MazeCoord coordB) {
    return (coordA.x < coordB.x || coordA.y < coordB.y) ? true : false;
}

// Increment operator
MazeCoord& MazeCoord::operator++() {
    if (x == maxX && y == maxY) return *this; // cannot increment anymore
    else if (x == maxX && y != maxY) { x = 0; y++; return *this; } // reset x
    else { x++; return *this; } // regular increment
}

// Assignment operator
MazeCoord& MazeCoord::operator= (const MazeCoord& coord) {
    x = coord.x;
    y = coord.y;
    maxX = coord.maxX;
    maxY = coord.maxY;
    coordType = coord.coordType;
    numCoord = coord.numCoord;
    return *this;
}

// Output operator
std::ostream& operator<<(std::ostream& output, MazeCoord& coord) {
    output << "(" << coord.x << "," << coord.y << ")"; // display as (x,y)
    return output;
}

// Implementation of directional coordinate functions

MazeCoord MazeCoord::getNorth()
{
    if (y != 0) y--;     // decrement would cause underflow if false
    MazeCoord coord(x, y);
    return coord;
}

MazeCoord MazeCoord::getSouth()
{
    if (y != maxY) y++;        // increment would cause overflow if false
    MazeCoord coord(x, y);
    return coord;
}

MazeCoord MazeCoord::getEast()
{
    if (x != maxX) x++;     // increment would cause overflow if false
    MazeCoord coord(x, y);
    return coord;
}

MazeCoord MazeCoord::getWest()
{
    if (x != 0) x--;        // decrement would cause underflow if false
    MazeCoord coord(x, y);
    return coord;
}

MazeCoord MazeCoord::getTwoNorth()
{
    if (y != 0 && y != 1) { y -= 2; }
    MazeCoord coord(x, y);
    return coord;
}

MazeCoord MazeCoord::getTwoSouth()
{
    if (y != maxY && y != maxY - 1 ) { y += 2; }
    MazeCoord coord(x, y);
    return coord;
}

MazeCoord MazeCoord::getTwoEast()
{
    if (x != maxX && x != maxX - 1) { x += 2; }
    MazeCoord coord(x, y);
    return coord;
}

MazeCoord MazeCoord::getTwoWest()
{
    if (x != 0 && x != 1) { x -= 2; }
    MazeCoord coord(x, y);
    return coord;
}
