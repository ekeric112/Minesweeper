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

    /*
     * Member functions:
     * create a Tile** board that holds tiles
     *
     */
    // Tile structure
    struct Tile {
        bool uncovered = false; // the tile uncovered or not
        bool flag = false; // the tile has been flag or not
        int ogNumber;     // original number of tile
        int changeNumber; //OG number - # of flags it is touching
    };


    /**
    * an AI capable of finishing the minesweeper game by itself within a time limit
    * @param _rowDimension # of rows in the game
    * @param _colDimension # number of col in the game
    * @param _totalMines total # of mines
    * @param _agentX
    * @param _agentY
    */
    MyAI(int _rowDimension, int _colDimension, int _totalMines, int _agentX, int _agentY);

    /**
    * Uses the parameter to judge what move to make, also keeps track of how long the move
    * was and how much time is left
    *
    * @param number Label of the tile that says how many mines are near it, -1 if
     * previous move was flag/unflag
    * @return an Action on a specific tile
    */
    Action getAction(int number) override;

    // ======================================================================
    // YOUR CODE BEGINS
    //other functions needed
    // ======================================================================

    /*
     *
     * void uncoverNeighbors(int c, int r);
     * void guess();
     * bool isInBounds(int c, int r);
     *
     *
     *
     */

    // ======================================================================
    // YOUR CODE ENDS
    // ======================================================================

};


#endif //MANUALMINESWEEPER_MYAI_HPP
