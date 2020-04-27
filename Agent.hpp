//
// Created by ekeri on 4/21/2020.
//

#ifndef MANUALMINESWEEPER_AGENT_HPP
#define MANUALMINESWEEPER_AGENT_HPP


class Agent {
public:
    int rowDimension;
    int colDimension;
    int totalMines;
    int agentX;
    int agentY;
public:

    // Actuators
    enum Action_type {
        LEAVE,
        UNCOVER,
        FLAG,
        UNFLAG,
    };

    struct Action {
        Action_type action;
        int x;
        int y;

    };

    virtual Action getAction
            (
                    int number
            ) = 0;

    //TODO delete later
    virtual void printMyWorldInfo() =0;

};


#endif //MANUALMINESWEEPER_AGENT_HPP
