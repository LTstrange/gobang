
#ifndef C_ENVIRONMENT_GOBANG_CPP
#define C_ENVIRONMENT_GOBANG_CPP

#include <iostream>
#include <vector>

#define board_type vector<vector<int>>

using namespace std;

void showBoard(board_type board) {
    for (vector<int> i : board) {
        for (int j : i) {
            cout << j << ' ';
        }
        cout << endl;
    }
}

int judgingWinOrLose(board_type board, int x, int y) {  // 无需打包
    // 判断是否是平局，检查是否有空位
    bool haveZero = false;
    for (vector<int> row : board) {
        for (int i : row) {
            if (i == 0) {
                haveZero = true;
                break;
            }
        }
        if (haveZero) {
            break;
        }
    }
    if (!haveZero) {
        // 棋盘下满，平局
        return 2;
    }

    // 判断这个子落下后，周围有没有连成五个
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
                int row = x + k * d[j] * step[i][0];
                int col = y + k * d[j] * step[i][1];
                if (row >= 0 && row < 15 && col >= 0 && col < 15 &&
                    board[x][y] == board[row][col]) {
                    count++;
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

int getWhichPerson(board_type board) {  // 无需打包
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

int nextStep(board_type &board, int whichPerson, int location[2]) {
    if (location[0] > 14 || location[0] < 0 || location[1] > 14 || location[1] < 0) {
        cout << "落子超出范围" << endl;
        return -1;
    }
    if (whichPerson == getWhichPerson(board)) {
        if (board[location[0]][location[1]] == 0)
            board[location[0]][location[1]] = whichPerson;
        else {
            cout << "落子冲突" << endl;
            return -1;
        }

        int state = judgingWinOrLose(board, location[0], location[1]);
        switch (state) {
            case 1: {
                return 1;
            }
            case 0:
                // 比赛未结束
                return 0;
            case 2: {
                return 2;
            }
        }
    }
    cout << "wrong person!" << endl;
    return -1;
}

int B_PYtoB_C(int board_PY[15 * 15], board_type &board) {
    for (int i = 0; i < 15; ++i) {
        for (int j = 0; j < 15; ++j) {
            board[i][j] = board_PY[0];
        }
    }
    return 0;
}

extern "C" {
int show_board(int board_PY[15 * 15]) {
    cout<<board_PY[0]<<endl;
    board_type board;
    B_PYtoB_C(board_PY, board);
    showBoard(board);
    return 0;
}

int next_step(int board_PY[15 * 15], int whichPerson, int location[2]) {
    board_type board;
    B_PYtoB_C(board_PY, board);
    int r_type = nextStep(board, whichPerson, location);
    return r_type;
}
int func() {
    return 1;
}
}

#endif //C_ENVIRONMENT_GOBANG_CPP
