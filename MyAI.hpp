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
    * @param number Label of the tile that says how many mines are near it
    * @return an Action on a specific tile
    */
    Action getAction(int number) override;


    // ======================================================================
    // YOUR CODE BEGINS
    //other functions needed
    // ======================================================================



    // ======================================================================
    // YOUR CODE ENDS
    // ======================================================================

};


#endif //MANUALMINESWEEPER_MYAI_HPP
