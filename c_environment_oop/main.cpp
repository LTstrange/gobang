#include <iostream>
#include "gobang.h"
using namespace std;

int main() {
    gobang env;
    env.showBoard();

    int location[2] = {7,7};

    for (int i = 0; i < 9; ++i) {
        env.nextStep(i%2+1, location);
        location[i%2]++;
    }


    env.showBoard();


    return 0;
}