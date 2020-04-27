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

using namespace std;


class MyAI : public Agent {
public:

    // Tile structure
    struct Tile {
        bool uncovered = false; // the tile uncovered or not
        bool flag = false; // the tile has been flag or not
        int ogNumber;     // original number of tile
        int changeNumber; //OG number - # of flags it is touching
    };

    MyAI(int _rowDimension, int _colDimension, int _totalMines, int _agentX, int _agentY);

    Action getAction(int number) override;
    Action uncoverNeighbor(); // UNCOVER the first neighbor that is covered
    Action findCovered(); // walk through the board to find the first covered && next_to_zero tile

    Tile**	myBoard; // create our own board

    bool next_to_zero(int c, int r);
    bool isInBounds(int c, int r);
    bool ready = false; // all tiles attached to 0 are uncovered?

};


#endif //MANUALMINESWEEPER_MYAI_HPP
