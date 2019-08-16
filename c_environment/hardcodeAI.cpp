#include "gobang.cpp"
#include <map>
#include <regex>
#include <math.h>
#include <string>
#include <algorithm>

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

int compileTypes(vector<int> list, int whoAmI) {
    map <string, string> types;
    vector<string> type_huo_si = {"011110"}; // 1
    vector<string> type_chong_si = {"011112", "0101110", "0110110"}; // 2
    vector<string> type_huo_san = {"01110", "010110"}; // 3
    vector<string> type_main_san = {"001112", "010112", "011012", "10011", "10101", "2011102"}; // 4
    vector<string> type_huo_er = {"00110", "01010", "010010", "010010", "010010", "010010", "010010", "010010",
                                  "010010"}; // 5
    vector<string> type_main_er = {"000112", "001012", "010012", "10001", "2010102", "2011002"}; // 6
    vector<string> type_dead_four = {"211112"}; // 7
    vector<string> type_dead_three = {"21112"}; // 8
    vector<string> type_dead_two = {"2112"}; // 9

    if (whoAmI == 2) {
        for (int i = 0; i < list.size(); i++) {
            if (list[i] == 1) {
                list[i] = 2;
            } else if (list[i] == 2) {
                list[i] = 1;
            }
        }
    }

    string res = "";
    string rres = "";
    for (int i:list) {
        res += to_string(i);
    }
    reverse(list.begin(), list.end());
    for (int i : list) {
        rres += to_string(i);
    }

    for (string i : type_huo_si) {
        if (regex_search(res, regex(i)) || regex_search(rres, regex(i))) {
            return 1;
        }
    }
    for (string i : type_chong_si) {
        if (regex_search(res, regex(i)) || regex_search(rres, regex(i))) {
            return 2;
        }
    }
    for (string i : type_huo_san) {
        if (regex_search(res, regex(i)) || regex_search(rres, regex(i))) {
            return 3;
        }
    }
    for (string i : type_main_san) {
        if (regex_search(res, regex(i)) || regex_search(rres, regex(i))) {
            return 4;
        }
    }
    for (string i : type_huo_er) {
        if (regex_search(res, regex(i)) || regex_search(rres, regex(i))) {
            return 5;
        }
    }
    for (string i : type_main_er) {
        if (regex_search(res, regex(i)) || regex_search(rres, regex(i))) {
            return 6;
        }
    }
    for (string i : type_dead_four) {
        if (regex_search(res, regex(i)) || regex_search(rres, regex(i))) {
            return 7;
        }
    }
    for (string i : type_dead_three) {
        if (regex_search(res, regex(i)) || regex_search(rres, regex(i))) {
            return 8;
        }
    }
    for (string i : type_dead_two) {
        if (regex_search(res, regex(i)) || regex_search(rres, regex(i))) {
            return 9;
        }
    }
    return 0;
}

int getScore(board_type board, int location[2]) {
    int scores[4] = {0, 0, 0, 0};
    scores[0] = compileTypes(board[location[0]], board[location[0]][location[1]]);
    vector<int> col;
    for (int i = 0; i < 15; ++i) {
        col.push_back(board[i][location[1]]);
    }
    scores[1] = compileTypes(col, board[location[0]][location[1]]);
    int x, y;
    if ((location[0] - location[1]) < 0) {
        x = 0;
        y = location[1] - location[0];
    } else {
        x = location[0] - location[1];
        y = 0;
    }
    vector<int> RD;
    for (int i = 0; x < 15 && y < 15; ++i) {
        RD.push_back(board[x][y]);
        x++;
        y++;
    }
    scores[2] = compileTypes(RD, board[location[0]][location[1]]);
    vector<int> LD;
    if (location[0] + location[1] > 14) {
        y = 14;
        x = location[0] + location[1] - 14;
    } else {
        y = location[0] + location[1];
        x = 0;
    }
    for (int i = 0; x < 15 && y > 0; ++i) {
        LD.push_back(board[x][y]);
        x++;
        y--;
    }
    scores[3] = compileTypes(LD, board[location[0]][location[1]]);
    int count_two = 0, count_three = 0, count_four = 0, count_five = 0, count_six = 0, count_seven = 0, count_eight = 0, count_nine = 0;
    for (int i : scores) {
        switch (i) {
            case 1:
                return 5000;
            case 2:
                count_two++;
                break;
            case 3:
                count_three++;
                break;
            case 4:
                count_four++;
                break;
            case 5:
                count_five++;
                break;
            case 6:
                count_six++;
                break;
            case 7:
                count_seven++;
                break;
            case 8:
                count_eight++;
                break;
            case 9:
                count_nine++;
                break;

        }
    }
    if (count_two >= 2) return 5000;
    if (count_two && count_three) return 5000;
    if (count_three >= 2) return 2000;
    if (count_three && count_four) return 1000;
    if (count_three) return 200;
    if (count_five >= 2) return 100;
    if (count_four) return 50;
    if (count_five && count_six) return 10;
    if (count_five) return 5;
    if (count_six) return 3;
    if (count_seven || count_eight || count_nine) return -5;
    return 0;
}


int alphaBeta(int whichPerson, board_type board, int alpha, int beta, int depth) {
    bool overdepth = false;
    vector<int> scores;
    if (depth > 1) {
        overdepth = true;
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
                return -10000;
            }
            return 10000;
        } else if (state == 2) {
            return 0;
        } else if (overdepth && !state) {
            scores.push_back(getScore(children.back(), tempLoc));
        }
    }
    for (int circle = 1; circle < 5; ++circle) {
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
                            return -10000;
                        }
                        return 10000;
                    } else if (state == 2) {
                        return 0;
                    } else if (overdepth && !state) {
                        scores.push_back(getScore(children.back(), tempLoc));
                    }
                }
                x += d[0];
                y += d[1];
            }
            d[0] = d[1];
            d[1] = -tmp;
        }
    }
    if (overdepth) {
        int max = -999999999;
        for (int i : scores) {
            if (max < i) {
                max = i;
            }
        }
        if (whichPerson == 2) {
            return -max;
        }
        return max;
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

int searchAI(board_type board, int position[2], int whoAmI) {
    int temp, max = -999999999;
    board_type tempBoard;
    for (int i = 0; i < 15; ++i) {
        for (int j = 0; j < 15; ++j) {
            if (!board[i][j]) {
                tempBoard = board;
                tempBoard[i][j] = whoAmI;
                if (whoAmI == 1) {
                    temp = alphaBeta(2, tempBoard, -999999999, 999999999, 0);
                    if (max < temp) {
                        max = temp;
                        position[0] = i;
                        position[1] = j;
                    }
                } else {
                    temp = alphaBeta(1, tempBoard, -999999999, 999999999, 0);
                    if (max < -temp) {
                        max = -temp;
                        position[0] = i;
                        position[1] = j;
                    }
                }

            }
        }
    }
    return 0;
}