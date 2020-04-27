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



MyAI::MyAI ( int _rowDimension, int _colDimension, int _totalMines, int _agentX, int _agentY ) : Agent()
{

    rowDimension = _rowDimension;
    colDimension = _colDimension;
    totalMines = _totalMines;
    agentX = _agentX;
    agentY = _agentY;

};

/*
 * I use a different order to UNCOVER the tiles
 *
 * The order we talked about at the meeting:
 * uncover ALL neighbors of the initial tile, then start over from the first tile on the board
 * to find the first covered && next_to_zero tile
 *
 * The order I use:
 * uncover the FIRST covered neighbor of a tile,
 * if find a 0, uncover that 0's FIRST covered neighbor, repeat
 * if find a 1 or all neighbors are covered, start over from the first tile on the board to find
 * the first covered && next_to_zero tile
 *
 */

Agent::Action MyAI::getAction( int number )
{

    /*
     * should this part be in while(!ready)?
     *
     */
    myBoard[agentX][agentY].uncovered = true;
    myBoard[agentX][agentY].ogNumber = number;

    while (!ready)
    {
        // if found a 0, UNCOVER neighbors
        if (number == 0)
        {
            uncoverNeighbor();
        }
        // if found a 1, loop through the board to find a covered tile that is attached to a 0
        else if (number == 1)
        {
            findCovered();
        }
    }

    /*
     * TODO:
     * READY
     *
     */

    return {LEAVE,-1,-1};

}

Agent::Action MyAI::uncoverNeighbor()
{
    // iterate 8 neighbours around a tile, UNCOVER the first covered neighbor
    int dir[8][2] = { {-1, 1}, {-1, 0}, {-1 , -1},
                      {0, 1},           {0, -1},
                      {1, 1}, {1, 0}, {1, -1} };

    for (int *i : dir) {
        int nc = agentX + i[0];
        int nr = agentY + i[1];
        if (isInBounds(nc, nr) && myBoard[nc][nr].uncovered) {
            return {UNCOVER, nc, nr};
        }
    }
    findCovered();
}

Agent::Action MyAI::findCovered()
{
    // walk through the board to find a covered & next_to_zero tile, then UNCOVER it
    for (int r = 0; r < rowDimension; r++)
        for (int c = 0; c < colDimension; c++)
            if (!myBoard[c][r].uncovered && next_to_zero(c, r)){
                return {UNCOVER, c, r};
            }

    // if all tiles attached to 0 are uncovered, we are ready to do the logic part
    ready = true;
}

bool MyAI::next_to_zero(int c, int r)
{
    // iterate 8 neighbours around a tile, return true if find a 0
    int dir[8][2] = { {-1, 1}, {-1, 0}, {-1 , -1},
                      {0, 1},           {0, -1},
                      {1, 1}, {1, 0}, {1, -1} };

    for (int *i : dir) {
        int nc = c + i[0];
        int nr = r + i[1];
        if (isInBounds(nc, nr) && myBoard[nc][nr].ogNumber == 0)
            return true;
        else if (isInBounds(nc, nr) && myBoard[nc][nr].ogNumber == 1)
            return false;
    }

    // if all neighbors are uncovered, start over with the first tile on the board
    findCovered();
}

bool MyAI::isInBounds ( int c, int r )
{
    return ( 0 <= c && c < colDimension && 0 <= r && r < rowDimension );
}
