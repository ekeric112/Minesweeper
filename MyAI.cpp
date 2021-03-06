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


#include "MyAI.hpp"


MyAI::MyAI(int _rowDimension, int _colDimension, int _totalMines, int _agentX, int _agentY) : Agent() {

    rowDimension = _rowDimension;
    colDimension = _colDimension;
    totalMines = _totalMines;
    agentX = _agentX;
    agentY = _agentY;

    //initialize board with new tiles
    myBoard = new Tile *[colDimension];
    for (int index = 0; index < colDimension; ++index) {
        myBoard[index] = new Tile[rowDimension];
    }
    unCoveredCount = 0; //for checking leave condition,

}


Agent::Action MyAI::getAction(int number) {
    stuck = false;
    Action returnAction;
    //if the previous action returned a number >= 0, then it was an uncover action
    if (number >= 0) {
        unCoveredCount++;
    }

    //dont return flag, unflag
    //just uncover colDim*rowDim - totalMines, then leave
    if (unCoveredCount == (colDimension * rowDimension - totalMines)) {
        return {LEAVE, -1, -1};
    }

    //once ready, return these values
    int returnX = -1;
    int returnY = -1;

    myBoard[agentX][agentY].uncovered = true;
    myBoard[agentX][agentY].ogNumber = number;
//    if (!ready) { //TODO might? cause bug later. Before we are ready, changenumber = ognumber
    myBoard[agentX][agentY].changeNumber = number;
//    }
    ready = isReady();
    updateTiles();
    if (mydebug) {
        printMyWorldInfo();
    }

    //todo error here 5/19 after minimal AI, before draft AI, doesnt check numbers > 1
    if (!ready) {
        // if found a 0, UNCOVER neighbors
        if (number == 0) {
            //check clockwise around the number and uncover the first square that is still covered
            returnAction = uncoverNeighbor();
        }
            // if found a 1, loop through the board to find a covered tile that is attached to a 0
        else { //5/19 changed from else if == 1 to else because if should restart the search if the number uncovered != 0
            returnAction = findCovered();
        }

        return returnAction;
    }

    // ready
    //put necessary flags down
    for (int r = 0; r < rowDimension; r++) {
        for (int c = 0; c < colDimension; c++) {
            //do something based off of the number on the square, for now only case: 1
            if (myBoard[c][r].changeNumber > 0 && myBoard[c][r].changeNumber == coverSquareTouchingNum(c, r)) {
                bool work = flagThemTiles(c, r, myBoard[c][r].changeNumber);
                if (mydebug) {
                    printMyWorldInfo();
                }
                if (!work) {
                    cout << "error in flagtiles\n";
                }
                //after putting down flags, change changenumber of everyone
                updateTiles();
            }
        }
    }
    // after exiting for loop, all tiles in board have their correct changeNumber values

    // do not need bool stuck(), findCovered() will check if we are stuck anyways

    //if it goes through the entire board and there is not a tile that is touching a guarenteed mine, we are stuck

    return findCovered();

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
        if (isInBounds(nc, nr) && !myBoard[nc][nr].uncovered && !myBoard[nc][nr].flag) {
            agentX = nc;
            agentY = nr;
            return {UNCOVER, nc, nr};
        }
    }
    return findCovered();
}

Agent::Action MyAI::stuckGuess() {
    //stuck state solution:
    /*
     * take the number / squares it is touching
     * ex: 1 touching 2 squares: 0.5
     * ex: 1 touching 4 squares: 0.25 -> a bigger probability is better
     *
     * so if stuck, loop through board and keep track of largest tile coord prob
     * in the end, guess one of the tiles that it is touching
     */
    int maxRow, maxCol;
    double maxProb = 0;
    for (int r = 0; r < rowDimension; r++) {
        for (int c = 0; c < colDimension; c++) {
            if (myBoard[c][r].changeNumber != 0 && myBoard[c][r].prob > maxProb) {
                maxRow = r;
                maxCol = c;
                maxProb = myBoard[c][r].prob;
            }
        }
    }
    //now, maxRow and maxCol contain the item

//    if (!myBoard[c][r].uncovered && !myBoard[c][r].flag)
    int dir[8][2] = {{-1, 1},
                     {-1, 0},
                     {-1, -1},
                     {0,  1},
                     {0,  -1},
                     {1,  1},
                     {1,  0},
                     {1,  -1}};
    for (int *i : dir) {
        int nc = maxCol + i[0];
        int nr = maxRow + i[1];
        if (isInBounds(nc, nr) && !myBoard[nc][nr].uncovered && !myBoard[nc][nr].flag) {
            agentX = nc;
            agentY = nr;
            return {UNCOVER, nc, nr};
        }
    }

//    cout << "Error in stuck guess\n";
    //usually if it hits this spot, theres a random spot surrounded by mines
    return guess();
}


// walk through the board to find a covered & next_to_zero tile, then UNCOVER it
Agent::Action MyAI::findCovered() {
    //first check if we are in the stuck state

    for (int r = 0; r < rowDimension; r++)
        for (int c = 0; c < colDimension; c++)
            if (!myBoard[c][r].uncovered && !myBoard[c][r].flag) {
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
                    if (isInBounds(nc, nr) && myBoard[nc][nr].changeNumber == 0) {
                        agentX = c;
                        agentY = r;
                        return {UNCOVER, c, r};
                    }
                }
            }

    if (!ready) {
        ready = true; // do not find any covered tile that is attached to a 0, ready to do the logic part
    } else {
        return stuckGuess();
    }
    // we will not get stuck when we are not ready, so when ready && nothing to uncover, we guess
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

    if (myBoard[c][r].uncovered) {
        tileString.append(to_string((int) myBoard[c][r].ogNumber));
        tileString.append("/");
        tileString.append(to_string((int) myBoard[c][r].changeNumber));
    } else if (myBoard[c][r].flag)
        tileString.append("#");
    else
        tileString.append(".");

    cout << setw(8) << tileString;

}

// counting unmber of flags
double MyAI::flagTouchingNum(int c, int r) {
    double flagsTouchingCount = 0;
    int dir[8][2] = {{-1, 1},
                     {-1, 0},
                     {-1, -1},
                     {0,  1},
                     {0,  -1},
                     {1,  1},
                     {1,  0},
                     {1,  -1}};
    //check around the given coordinate
    for (int *i : dir) {
        int nc = c + i[0];
        int nr = r + i[1];
        if (isInBounds(nc, nr) && myBoard[nc][nr].flag) {
            flagsTouchingCount++;
        }
    }
    return flagsTouchingCount;
}


double MyAI::coverSquareTouchingNum(int c, int r) {
    double coveredCount = 0;
    int dir[8][2] = {{-1, 1},
                     {-1, 0},
                     {-1, -1},
                     {0,  1},
                     {0,  -1},
                     {1,  1},
                     {1,  0},
                     {1,  -1}};
    //check around the given coordinate
    for (int *i : dir) {
        int nc = c + i[0];
        int nr = r + i[1];
        if (isInBounds(nc, nr) && !myBoard[nc][nr].uncovered && !myBoard[nc][nr].flag) {
            coveredCount++;
        }
    }
    return coveredCount;
}

bool MyAI::isReady() {
    for (int r = 0; r < rowDimension; r++)
        for (int c = 0; c < colDimension; c++)
            if (!myBoard[c][r].uncovered && !myBoard[c][r].flag) {
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
                    if (isInBounds(nc, nr) && myBoard[nc][nr].changeNumber == 0) {
                        return false;
                    }
                }
            }
    return true; // do not find any covered tile that is attached to a 0, ready to do the logic part
}


bool MyAI::flagThemTiles(int c, int r, int flagNum) {
    bool flagGood = false;
    int tilesFlagged = 0;
    int dir[8][2] = {{-1, 1},
                     {-1, 0},
                     {-1, -1},
                     {0,  1},
                     {0,  -1},
                     {1,  1},
                     {1,  0},
                     {1,  -1}};
    //check around the given coordinate
    for (int *i : dir) {
        int nc = c + i[0];
        int nr = r + i[1];
        if (isInBounds(nc, nr) && !myBoard[nc][nr].uncovered && !myBoard[nc][nr].flag) {
            //if the flag is up, then its still covered
            myBoard[nc][nr].flag = true;
            tilesFlagged++;
        }
    }

    if (tilesFlagged == flagNum) {
        flagGood = true;
    }

    return flagGood;

}

void MyAI::updateTiles() {
    //updates the change number and the prob
    for (int r = 0; r < rowDimension; r++) {
        for (int c = 0; c < colDimension; c++) {
            if (myBoard[c][r].uncovered) {
                myBoard[c][r].changeNumber = myBoard[c][r].ogNumber - flagTouchingNum(c, r);

                //it should only have this number if not /0 or 0
                if (myBoard[c][r].changeNumber != 0 && coverSquareTouchingNum(c, r) != 0) {
                    myBoard[c][r].prob = myBoard[c][r].changeNumber / coverSquareTouchingNum(c, r);

                }

                if (mydebug)
                    printMyWorldInfo();
            }
        }
    }
}

// random guess
Agent::Action MyAI::guess() {
    int c, r;
    //find a random square, if it is uncovered, get new coord
    do {
        r = rand() % rowDimension;
        c = rand() % colDimension;
    } while (myBoard[c][r].uncovered || myBoard[c][r].flag);
    //set the agents coord before returning
    agentX = c;
    agentY = r;
    return {UNCOVER, c, r};
}




