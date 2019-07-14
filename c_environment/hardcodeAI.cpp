#include "gobang.cpp"
#include <hash_map>

void findCentreOfMass(board_type board, int location[2]) {
    int x = 7, y = 7;
    int count = 1;
    for (int i = 0; i < 15; ++i) {
        for (int j = 0; j < 15; ++j) {
            if (board[i][j]) {
                x += i;
                y += j;
                count++;
            }
        }
    }
    location[0] = x / count;
    location[1] = y / count;
}


int alphaBeta(int whichPerson, board_type board, int alpha, int beta, int depth) {
    if (depth > 30) {
        cout<<"depth reach 30"<<endl;
        // 搜索超过30直接认为是平局
        return 0;
    }
    vector<board_type> children;
    int location[2];
    findCentreOfMass(board, location);
    int x = location[0];
    int y = location[1];

    // circleSearch
    if (!board[x][y]) {
        children.push_back(board);
        int tempLoc[2] = {x, y};
        int state;
        state = nextStep(children.back(), whichPerson, tempLoc);
        if (state == 1) {
            if (whichPerson == 2) {
                return -1;
            }
            return 1;
        } else if (state == 2) {
            return 0;
        }
    }
    for (int circle = 1; circle < 10; ++circle) {
        x = location[0] - circle;
        y = location[1] + circle;
        int d[2] = {1, 0};
        for (int dir = 0; dir < 4; ++dir) {
            int tmp = d[0];
            for (int tic = 0; tic < 2 * circle; ++tic) {
                if (x >= 0 && x < 15 && y >= 0 && y < 15 && !board[x][y]) {
                    children.push_back(board);
                    int tempLoc[2] = {x, y};
                    int state;
                    state = nextStep(children.back(), whichPerson, tempLoc);
                    if (state == 1) {
                        if (whichPerson == 2) {
                            return -1;
                        }
                        return 1;
                    } else if (state == 2) {
                        return 0;
                    }
                }
                x += d[0];
                y += d[1];
            }
            d[0] = d[1];
            d[1] = -tmp;
        }
    }

    int score;
    // MAX
    if (whichPerson == 1) {
        for (board_type child : children) {

            score = alphaBeta(2, child, alpha, beta, ++depth);
            if (score > alpha) {
                alpha = score;
            }
            if (alpha >= beta) {
                return alpha;
            }
        }
        return alpha;
    }
    // MIN
    else {
        for (board_type child : children) {
            score = alphaBeta(1, child, alpha, beta, ++depth);
            if (score < beta) {
                beta = score;
            }
            if (alpha >= beta) {
                return beta;
            }
        }
        return beta;
    }
}

int searchAI(board_type board, int position[2], int whoAmI){
    board_type state(15, vector<int>(15, 0));


}