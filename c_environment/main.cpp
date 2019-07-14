#include "gobang.cpp"
#include "hardcodeAI.cpp"

using namespace std;

int main() {
    board_type board(15, vector<int>(15, 0));

    int location[2] = {7, 7};

    nextStep(board, 1, location);


    cout<<alphaBeta(2, board, -2, 2, 0);



    return 0;
}