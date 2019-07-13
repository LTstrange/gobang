#include <iostream>
#include <vector>

using namespace std;

void showBoard(vector<vector<int>> board){
    for (vector<int> i : board) {
        for (int j : i) {
            cout << j << ' ';
        }
        cout << endl;
    }
}

int jugingWinOrLose(vector<vector<int>> board, int x, int y) {
    int i, j, k;
    const int step[4][2] = {{1, 0},
                            {0, 1},
                            {1, 1},
                            {1, -1}};
    for (i = 0; i < 4; ++i) {
        const int d[2] = {-1, 1};
        int count = 1;
        for (j = 0; j < 2; ++j) {
            for (k = 1; k <= 4; ++k) {
                int row = x + k*d[j]*step[i][0];
                int col = y + k*d[j]*step[i][1];
                if (row >= 0 && row < 15 && col >= 0 && col < 15 &&
                    board[x][y] == board[row][col]) {
                    count ++;
                } else {
                    break;
                }
            }
        }
        if (count >= 5) {
            return 1;
        }
    }
    return 0;
}

int getWhichPerson(vector<vector<int>> board) {
    int res = 0;
    for (vector<int> row : board) {
        for (int i : row) {
            res ^= i;
        }
    }
    switch (res) {
        case 0:
        case 3:
            return 1;
        case 1:
        case 2:
            return 2;
        default:
            cout << "ERROR" << endl;
            return 0;
    }
}

int nextStep(vector<vector<int>> board, int whichPerson, int location[2]) {
    if (whichPerson == getWhichPerson(board)) {
        if (board[location[0]][location[1]] == 0)
            board[location[0]][location[1]] = whichPerson;
        else {
            cout<<"落子冲突"<<endl;
            return -1;
        }
        if (jugingWinOrLose(board, location[0], location[1])) {
            cout<<"YOU WIN!"<<endl;
            switch (whichPerson) {
                case 1:
                    cout<<"执黑获胜"<<endl;
                    break;
                case 2:
                    cout<<"执白获胜"<<endl;
                    break;
                default:
                    break;
            }
            return 1;
        }
        return 0;
    }
    cout<<"wrong person!"<<endl;
    return -1;
}
