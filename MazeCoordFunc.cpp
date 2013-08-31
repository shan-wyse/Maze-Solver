// *************************************
// ** G L O B A L   F U N C T I O N S **
// *************************************

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <stack>
#include <vector>
#include <string>

#include "MazeCoord.h"

#define MAXVALX 19              // Maximum possible x dimension - 1
#define MAXVALY 19              // Maximum possible y dimension - 1

// Function prototypes

void menu();
void traverseMaze(std::vector<MazeCoord> &maze, MazeCoord &startCoord,
                  MazeCoord &finalCoord);
void displayWithAllPath(std::vector<MazeCoord> &maze, MazeCoord &coord);
void displayWithoutAllPath(std::vector<MazeCoord> &maze, MazeCoord &coord);
void readDiskMaze(int mazeChoice, std::string &mazeStr);
void mazeRead(std::vector<MazeCoord> &maze, MazeCoord &coord,
              std::string &mazeStr);
void setCoordAvailable(std::vector<MazeCoord> &maze, MazeCoord &coord);
void setCoordUnavailable(std::vector<MazeCoord> &maze, MazeCoord &coord);
void menuOptionOne();
void menuOptionTwo();
void menuOptionThree();
void returnToMenuOptionOne();
void returnToMenuOptionTwo();
void coordCheck(int index);
int findCoord(std::vector<MazeCoord> &maze, MazeCoord &coord);

// Function implementations

void menu()
{
    std::cout << "\n\nWelcome, what task would you like to do?\n";
    std::cout << "1. View a maze\n";
    std::cout << "2. View a solved maze\n";
    std::cout << "3. Exit\n";

    std::cout << "\nPlease enter your choice: ";

    int choice;
    bool isSuccess = false;

    do {
        std::cin >> choice;

        switch (choice) {
            case 1:
                menuOptionOne();
                isSuccess = true;
                break;
            case 2:
                menuOptionTwo();
                isSuccess = true;
                break;
            case 3:
                std::cout << "Thank you for using this programme.\n";
                exit(0);
                isSuccess = true;
                break;
            default:
                std::cout << "Invalid choice. Please try again: ";
        }
    } while (isSuccess == false);
}

void traverseMaze(std::vector<MazeCoord> &maze, MazeCoord &startCoord,
                  MazeCoord &finalCoord)
{
    srand(time(NULL)); // obtain random seed
    MazeCoord coord;
    std::stack<MazeCoord> coordStack; // contains coordinates as progression is
                                      // made through the maze

    int index = findCoord(maze, startCoord); // begin at the start coordinate
    coordCheck(index);
    maze[index].setUsed();

    int visitedCoord = 0;

    do {
        int chosenDirection = (rand() % 4) + 1; // random number between 1 and 4

        if ((chosenDirection == 1) && (maze[index - 20].getAvailability()
            == true) && (maze[index - 20].getUsed() == false)) {
            index = index - 20;
            maze[index].setUsed();
            coordStack.push(maze[index]);
            visitedCoord++;
        } else if ((chosenDirection == 2) && (maze[index + 20].getAvailability()
                    == true) && (maze[index + 20].getUsed() == false)) {
            index = index + 20;
            maze[index].setUsed();
            coordStack.push(maze[index]);
            visitedCoord++;
        } else if ((chosenDirection == 3) && (maze[index + 1].getAvailability()
                    == true) && (maze[index + 1].getUsed() == false)) {
            index = index + 1;
            maze[index].setUsed();
            coordStack.push(maze[index]);
            visitedCoord++;
        } else if ((chosenDirection == 4) && (maze[index - 1].getAvailability()
                    == true) && (maze[index - 1].getUsed() == false)) {
            index = index - 1;
            maze[index].setUsed();
            coordStack.push(maze[index]);
            visitedCoord++;
        } else if (((maze[index - 20].getAvailability() == false) ||
                   (maze[index - 20].getUsed() == true)) &&
                   ((maze[index + 20].getAvailability() == false) ||
                   (maze[index + 20].getUsed() == true)) &&
                   ((maze[index + 1].getAvailability() == false) ||
                   (maze[index + 1].getUsed() == true)) &&
                   ((maze[index - 1].getAvailability() == false) ||
                   (maze[index - 1].getUsed() == true))) {
            maze[index].setTravelled(); // go in opposite direction
            coordStack.pop();
            coord = coordStack.top(); // return to previous coordinate
            index = findCoord(maze, coord);
            coordCheck(index);
        }
    } while (maze[index] != finalCoord); // final coord is diagonally opposite
}                                        // from the start coordinate

void displayWithAllPath(std::vector<MazeCoord> &maze, MazeCoord &coord)
{
    for (unsigned int i = 0; i < maze.size(); i++) {
        if (maze[i].getUsed() == true) std::cout << "."; // chosen path
        else if (maze[i].getCoordType() == FLOOR) std::cout << " ";
        else if (maze[i].getCoordType() == WALL) std::cout << "@";
        else if (maze[i].getCoordType() == BORDER) std::cout << "#";

        // end of line
        if (maze[i].getCoordX() == coord.getMaxX()) std::cout << std::endl;
    }
}

void displayWithoutAllPath(std::vector<MazeCoord> &maze, MazeCoord &coord)
{
    for (unsigned int i = 0; i < maze.size(); i++) {
        if (maze[i].getUsed() == true) std::cout << "."; // chosen path
        else if (maze[i].getCoordType() == FLOOR) std::cout << " ";
        else if (maze[i].getCoordType() == WALL) std::cout << "@";
        else if (maze[i].getCoordType() == BORDER) std::cout << "#";

        // delete previous "." and replace with " "
        if (maze[i].getTravelled() == true) std::cout << "\b ";

        // end of line
        if (maze[i].getCoordX() == coord.getMaxX()) std::cout << std::endl;
    }
}

void readDiskMaze(int mazeChoice, std::string &mazeStr)
{
    std::ifstream diskIn;
    if (mazeChoice == 1) diskIn.open("maze1");
    if (mazeChoice == 2) diskIn.open("maze2");
    if (mazeChoice == 3) diskIn.open("maze3");

    if (!diskIn.is_open()) {
        std::cout << "Cannot open maze file.\n"; exit(1); // exit programme
    }

    std::getline(diskIn, mazeStr);
    diskIn.close();
}

void mazeRead(std::vector<MazeCoord> &maze, MazeCoord &coord,
              std::string &mazeStr)
{
    for (unsigned int i = 0; i < maze.size(); i++) {
        maze[i] = coord;
        if (mazeStr[i] == ' ') maze[i].setFloor();
        else if (mazeStr[i] == 'X') maze[i].setWall();
        else if (mazeStr[i] == '#') maze[i].setBorder();
        else { std::cerr << "Maze reading error\n"; exit(1); } // exit programme
        ++coord;
    }
}

void setCoordAvailable(std::vector<MazeCoord> &maze, MazeCoord &coord)
{
    for (unsigned int i = 0; i < maze.size(); i++) {
        maze[i].setAvailable();
    }
}

void setCoordUnavailable(std::vector<MazeCoord> &maze, MazeCoord &coord)
{
    for (unsigned int i = 0; i < maze.size(); i++) {
        if (maze[i].getCoordType() == WALL || maze[i].getCoordType() == BORDER)
            maze[i].setUnavailable();
    }
}

void menuOptionOne()
{
    std::cout << "Please enter the number of the maze you wish to view: ";

    std::string mazeStr;
    int mazeChoice;

    std::cin >> mazeChoice;

    MazeCoord coord(0, 0); // standard coordinate template
    coord.setMaxX(MAXVALX);
    coord.setMaxY(MAXVALY);
    coord.setNumCoord();

    readDiskMaze(mazeChoice, mazeStr);

    std::vector<MazeCoord> maze(coord.getNumCoord());

    mazeRead(maze, coord, mazeStr);
    setCoordAvailable(maze, coord);
    setCoordUnavailable(maze, coord);
    displayWithoutAllPath(maze, coord);

    returnToMenuOptionOne();
}

void menuOptionTwo()
{
    std::cout << "Please enter the number of the solution you wish to view: ";

    std::string mazeStr;
    int mazeChoice;

    std::cin >> mazeChoice;

    MazeCoord coord(0, 0); // standard coordinate template
    MazeCoord startCoord(1, MAXVALY); // starting coordinate
    MazeCoord finalCoord(MAXVALX - 1, 0); // finishing coordinate
    coord.setMaxX(MAXVALX);
    coord.setMaxY(MAXVALY);
    coord.setNumCoord();
    startCoord.setMaxX(MAXVALX);
    startCoord.setMaxY(MAXVALY);
    startCoord.setNumCoord();
    finalCoord.setMaxX(MAXVALX);
    finalCoord.setMaxY(MAXVALY);
    finalCoord.setNumCoord();

    readDiskMaze(mazeChoice, mazeStr);

    std::vector<MazeCoord> maze(coord.getNumCoord());

    mazeRead(maze, coord, mazeStr);
    setCoordAvailable(maze, coord);
    setCoordUnavailable(maze, coord);
    traverseMaze(maze, startCoord, finalCoord);

    std::cout << "\nWould you like to view with or without all paths?\n";
    std::cout << "1. With\n";
    std::cout << "2. Without\n";

    std::cout << "\nPlease enter your choice: ";

    int choice;
    bool isSuccess = false;

    do {
        std::cin >> choice;

        if (choice == 1) {
            displayWithAllPath(maze, coord);
            isSuccess = true;
        }
        else if (choice == 2) {
            displayWithoutAllPath(maze, coord);
            isSuccess = true;
        }
        else std::cout << "Invalid choice. Please try again: ";
    } while (isSuccess == false);

    returnToMenuOptionTwo();
}

void returnToMenuOptionOne()
{
    std::cout << "\nWhat would you like to do: \n";
    std::cout << "1. View another maze\n";
    std::cout << "2. Return to the menu\n";

    std::cout << "Please enter your choice: ";

    int choice;
    bool isSuccess = false;

    do {
        std::cin >> choice;

        if (choice == 1) { menuOptionOne(); isSuccess = true; }
        else if (choice == 2) { menu(); isSuccess = true; }
        else std::cout << "Invalid input. Please try again: ";
    } while (isSuccess == false);
}

void returnToMenuOptionTwo()
{
    std::cout << "\nWhat would you like to do: \n";
    std::cout << "1. View another solution\n";
    std::cout << "2. Return to the menu\n";

    std::cout << "Please enter your choice: ";

    int choice;
    bool isSuccess = false;

    do {
        std::cin >> choice;

        if (choice == 1) { menuOptionTwo(); isSuccess = true; }
        else if (choice == 2) { menu(); isSuccess = true; }
        else std::cout << "Invalid input. Please try again: ";
    } while (isSuccess == false);
}

void coordCheck(int index)
{
    if (index == -1) {
        std::cerr << "coordCheck() error\n" << std::endl; // index is not in
    }                                                     // range
}

int findCoord(std::vector<MazeCoord> &maze, MazeCoord &coord)
{
    for (unsigned int i = 0; i < maze.size(); i++) {
        if (maze[i].getCoordX() == coord.getCoordX() &&
            maze[i].getCoordY() == coord.getCoordY()) {
            return i;
        }
    }

    return -1; // will be caught by coordCheck() function
}
