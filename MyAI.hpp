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
    MyAI(int _rowDimension, int _colDimension, int _totalMines, int _agentX, int _agentY);

    Action getAction(int number) override;


    // ======================================================================
    // YOUR CODE BEGINS
    // ======================================================================



    // ======================================================================
    // YOUR CODE ENDS
    // ======================================================================

};


#endif //MANUALMINESWEEPER_MYAI_HPP
