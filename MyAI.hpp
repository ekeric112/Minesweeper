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

using namespace std;


class MyAI : public Agent {
public:

    // Tile structure
    struct Tile {
        bool uncovered = false; // the tile uncovered or not
        bool flag = false; // the tile has been flag or not
        //numbers set to -1 for error checking if needed
        int ogNumber = -1;     // original number of tile
        int changeNumber = -1; //OG number - # of flags it is touching
    };

    MyAI(int _rowDimension, int _colDimension, int _totalMines, int _agentX, int _agentY);

    ~MyAI(); //Deconstructor


    Action getAction(int number) override;
    Action uncoverNeighbor(); // UNCOVER the first neighbor that is covered
    Action findCovered(); // walk through the board to find the first covered && next_to_zero tile

    Tile **myBoard; // create our own board

    bool isInBounds(int c, int r);

    bool ready = false; // all tiles attached to 0 are uncovered?

    //Prints myboard
    void printMyWorldInfo();

    void printTileInfo(int c, int r);

};


#endif //MANUALMINESWEEPER_MYAI_HPP
