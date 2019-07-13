#include "gobang.cpp"
#include "hardcodeAI.cpp"

using namespace std;

int main() {
    vector<vector<int>> board(15, vector<int>(15, 0));


    showBoard(board);

    int location[2] = {7, 7};

    for (int i = 0; i < 9; ++i) {
        nextStep(board, i % 2 + 1, location);
        location[i % 2]++;
    }


    showBoard(board);


    return 0;
}