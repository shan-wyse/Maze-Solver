// *************************************
// ** M A Z E   C O O R D   C L A S S **
// *************************************

#include <iostream>

enum COORDTYPE { FLOOR, WALL, BORDER };

class MazeCoord
{
    // private data members

    // [x-coordinate, y-coordinate, maximum value of x, maximum value of y,
    //  type of coordinate variable, total number of coordinates]
    int x, y, maxX, maxY, coordType, numCoord;

    // [verification of floor variable, verification of already used coordinates
    //  variable, verification of already travelled variable]
    bool isAvailable, isUsed, isTravelled;


public:

    // Constructors
    MazeCoord() { }
    MazeCoord(int xarg, int yarg)  { x = xarg; y = yarg; }
    MazeCoord(const MazeCoord &coordCopy) {
        x = coordCopy.x; y = coordCopy.y;
        maxX = coordCopy.x; maxY = coordCopy.y;
        coordType = coordCopy.coordType;
        numCoord = coordCopy.numCoord;
        isAvailable = coordCopy.isAvailable;
        isUsed = coordCopy.isUsed;
        isTravelled = coordCopy.isTravelled;
    }

    // Destructor
    ~MazeCoord() { }

    // Get functions
    // These function return a specified private data member.
    const int getCoordX() { return x; }
    const int getCoordY() { return y; }
    const int getMaxX() { return maxX; }
    const int getMaxY() { return maxY; }
    const int getCoordType() { return coordType; }
    const int getNumCoord() { return numCoord; }
    const bool getAvailability() { return isAvailable; }
    const bool getUsed() { return isUsed; }
    const bool getTravelled() { return isTravelled; }

    // Set functions
    // These functions assign a specified value to a data member and return
    // this value.
    int setMaxX(int maxXArg) { maxX = maxXArg; return maxX; }
    int setMaxY(int maxYArg) { maxY = maxYArg; return maxY; }
    int setFloor() { coordType = FLOOR; return FLOOR; }
    int setWall() { coordType = WALL; return WALL; }
    int setBorder() { coordType = BORDER; return BORDER; }
    int setNumCoord() { numCoord = (maxX + 1) * (maxY + 1); return numCoord; }
    int setUnavailable() { isAvailable = false; return isAvailable; }
    int setAvailable() { isAvailable = true; return isAvailable; }
    int setUsed() { isUsed = true; return isUsed; }
    int setUnused() { isUsed = false; return isUsed; }
    int setTravelled() { isTravelled = true; return isTravelled; }


    // Operator overloading functions

    // Relational operators
    friend bool operator==(const MazeCoord coordA, const MazeCoord coordB);
    friend bool operator!=(const MazeCoord coordA, const MazeCoord coordB);
    friend bool operator>=(const MazeCoord coordA, const MazeCoord coordB);
    friend bool operator<=(const MazeCoord coordA, const MazeCoord coordB);
    friend bool operator>(const MazeCoord coordA, const MazeCoord coordB);
    friend bool operator<(const MazeCoord coordA, const MazeCoord coordB);

    // Increment operator
    MazeCoord& operator++();

    // Assignment operator
    MazeCoord& operator= (const MazeCoord& coord);

    // Output operator
    friend std::ostream& operator<<(std::ostream& output, MazeCoord& coord);


    // Directional coordinate functions
    // These functions return a coordinate in the given direction by
    // incrementing or decrementing the x or y variables of the "this" argument.

    MazeCoord getNorth();
    MazeCoord getSouth();
    MazeCoord getEast();
    MazeCoord getWest();
    MazeCoord getTwoNorth();
    MazeCoord getTwoSouth();
    MazeCoord getTwoEast();
    MazeCoord getTwoWest();
};
