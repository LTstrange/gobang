#ifndef C_ENVIRONMENT_GOBANG_H
#define C_ENVIRONMENT_GOBANG_H

#include <iostream>
#include <vector>

using namespace std;

#define boardsize 15

class gobang {
private:
    vector<vector<int>> board;
    int size;

    int jugingWinOrLose(int x, int y);

    int getWhichPerson();

public:
    gobang() : board(boardsize, vector<int>(boardsize, 0)), size(boardsize) {};

    void showBoard();

    int nextStep(int whichPerson, int location[2]);
};

#endif //C_ENVIRONMENT_GOBANG_H
