#include "gobang.cpp"
#include "hardcodeAI.cpp"

using namespace std;

int main() {
    int b[15 * 15]={2};
    board_type board(15, vector<int>(15, 0));
    B_PYtoB_C(b, board);
    showBoard(board);

    return 0;
}