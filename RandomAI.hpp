//
// Created by ekeri on 4/21/2020.
//

#ifndef MANUALMINESWEEPER_RANDOMAI_HPP
#define MANUALMINESWEEPER_RANDOMAI_HPP

#include <cstdlib>
#include "Agent.hpp"
#include<iostream>


class RandomAI : public Agent {
public:
    //todo delete later
    void printMyWorldInfo() override {

    }

    RandomAI(int _rowDimension, int _colDimension, int _totalMines, int _agentX, int _agentY) {
        rowDimension = _rowDimension;
        colDimension = _colDimension;
    };

    Action getAction(int number) override {
        return {actions[rand() % 4], rand() % rowDimension, rand() % colDimension};
    }

private:

    const Action_type actions[4] =
            {
                    LEAVE,
                    UNCOVER,
                    FLAG,
                    UNFLAG,
            };

};


#endif //MANUALMINESWEEPER_RANDOMAI_HPP
