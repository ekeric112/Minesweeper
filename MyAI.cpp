// ======================================================================
// FILE:        MyAI.cpp
//
// AUTHOR:      Jian Li
//
// DESCRIPTION: This file contains your agent class, which you will
//              implement. You are responsible for implementing the
//              'getAction' function and any helper methods you feel you
//              need.
//
// NOTES:       - If you are having trouble understanding how the shell
//                works, look at the other parts of the code, as well as
//                the documentation.
//
//              - You are only allowed to make changes to this portion of
//                the code. Any changes to other portions of the code will
//                be lost when the tournament runs your code.
// ======================================================================


/*
 * 4/22/2020: Eric: try to finish implementing constructor
 * Shangyi: come up with functions that should be inside getAction
 *
 *
 */


#include "MyAI.hpp"


MyAI::MyAI(int _rowDimension, int _colDimension, int _totalMines, int _agentX, int _agentY) : Agent() {

    rowDimension = _rowDimension;
    colDimension = _colDimension;
    totalMines = _totalMines;
    agentX = _agentX;
    agentY = _agentY;

    //initialize board with new tiles
    myBoard = new Tile *[colDimension];
    for (int index = 0; index < colDimension; ++index)
        myBoard[index] = new Tile[rowDimension];

}


Agent::Action MyAI::getAction(int number) {

    myBoard[agentX][agentY].uncovered = true;
    myBoard[agentX][agentY].ogNumber = number;

    while (!ready) {
        // if found a 0, UNCOVER neighbors
        if (number == 0) {
            //check clockwise around the number and uncover the first square that is still covered
            return uncoverNeighbor();
        }
            // if found a 1, loop through the board to find a covered tile that is attached to a 0
        else if (number == 1) {
            return findCovered();
        }
    }

    /*
     * TODO:
     * READY
     *
     */

    return {LEAVE, -1, -1};

}

// iterate 8 neighbours around a tile, UNCOVER the first covered neighbor
Agent::Action MyAI::uncoverNeighbor() {

    int dir[8][2] = {{-1, 1},
                     {-1, 0},
                     {-1, -1},
                     {0,  1},
                     {0,  -1},
                     {1,  1},
                     {1,  0},
                     {1,  -1}};

    for (int *i : dir) {
        int nc = agentX + i[0];
        int nr = agentY + i[1];
        if (isInBounds(nc, nr) && !myBoard[nc][nr].uncovered) {
            agentX = nc;
            agentY = nr;
            return {UNCOVER, nc, nr};
        }
    }
    return findCovered();
}

// walk through the board to find a covered & next_to_zero tile, then UNCOVER it
Agent::Action MyAI::findCovered() {

    for (int r = 0; r < rowDimension; r++)
        for (int c = 0; c < colDimension; c++)
            if (!myBoard[c][r].uncovered) {
                int dir[8][2] = {{-1, 1},
                                 {-1, 0},
                                 {-1, -1},
                                 {0,  1},
                                 {0,  -1},
                                 {1,  1},
                                 {1,  0},
                                 {1,  -1}};
                for (int *i : dir) {
                    int nc = c + i[0];
                    int nr = r + i[1];
                    if (isInBounds(nc, nr) && myBoard[nc][nr].ogNumber == 0) {
                    agentX = c;
                    agentY = r;
                    return {UNCOVER, c, r};
                    }
                }
            }

    ready = true; // do not find any covered tile that is attached to a 0, ready to do the logic part
}

bool MyAI::isInBounds(int c, int r) {
    return (0 <= c && c < colDimension && 0 <= r && r < rowDimension);
}

MyAI::~MyAI() {
    for (int index = 0; index < colDimension; ++index)
        delete[] myBoard[index];

    delete[] myBoard;

}

void MyAI::printMyWorldInfo() {
    cout << "---------------- MyBoard ------------------\n" << endl;
    for (int r = rowDimension - 1; r >= 0; --r) {
        printf("%-4d%c", r + 1, '|');
        for (int c = 0; c < colDimension; ++c)
            printTileInfo(c, r);
        cout << endl << endl;
    }

    cout << "     ";
    for (int c = 0; c < colDimension; ++c)
        cout << setw(8) << "-";
    cout << endl << "     ";
    for (int c = 0; c < colDimension; ++c)
        cout << setw(8) << c + 1;
    cout << endl;

}

void MyAI::printTileInfo(int c, int r) {
    string tileString;

    if (myBoard[c][r].uncovered)
//        if ( myBoard[c][r].mine )
//            tileString.append("*");
//        else
//        {
        tileString.append(to_string(myBoard[c][r].ogNumber));

//        }
    else if (myBoard[c][r].flag)
        tileString.append("#");
    else
        tileString.append(".");

    cout << setw(8) << tileString;

}
