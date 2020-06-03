//
// Created by ekeri on 4/21/2020.
//

#ifndef MANUALMINESWEEPER_MYAI_HPP
#define MANUALMINESWEEPER_MYAI_HPP

#include "Agent.hpp"
#include <iostream> // temporary use
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <iomanip>      // setw
#include <chrono>   // time
#include <iomanip>

using namespace std;


class MyAI : public Agent {
public:
    bool mydebug = false;

    // Tile structure
    struct Tile {
        bool uncovered = false; // the tile uncovered or not
        bool flag = false; // the tile has been flag or not
        //numbers set to -1 for error checking if needed
        double ogNumber = -1;     // original number of tile
        double changeNumber = -1; //OG number - # of flags it is touching
        double prob = -1; //changenumber/number of covered tiles it is touching
    };

    MyAI(int _rowDimension, int _colDimension, int _totalMines, int _agentX, int _agentY);

    ~MyAI(); //Deconstructor

    Tile **myBoard; // create our own board
    Action getAction(int number) override;
    Action uncoverNeighbor(); // UNCOVER the first neighbor that is covered
    Action findCovered(); // walk through the board to find the first covered && next_to_zero tile
    Action guess();
    Action stuckGuess();

    bool isInBounds(int c, int r);
    bool isReady(); // might have to combine this function somewhere else if it takes up too much time
    bool ready = false; // all tiles attached to 0 are uncovered?
    bool stuck = false;
    int unCoveredCount; // how many times we returned uncovered
    void printMyWorldInfo(); // prints myboard
    void printTileInfo(int c, int r);

    /**
     * Function for finding out how many flags are touching a given tile at r, c
     * @param r Row
     * @param c Col
     * @return how many flags are touching that tile
     */
    double flagTouchingNum(int c, int r);


    /**
     * Function for finding out how many covered tiles are touching a given tile at r, c
     * @param r Row
     * @param c Col
     * @return how many covered tiles are touching that tile
     */
    double coverSquareTouchingNum(int c, int r);


    /**
     * Given that the tile at the coordinate is quarenteed to be touching the all mines, flag em
     * @param c Col
     * @param r row
     * @param flagNum how many mines it is touching
     * @return true if all the flagnum == number of tiles flagged, false if not
     */
    bool flagThemTiles(int c, int r, int flagNum);

    /**
     * Goes through the entire myboard and updates each tile's changeFlag and prob #
     */
    void updateTiles();

};


#endif //MANUALMINESWEEPER_MYAI_HPP
