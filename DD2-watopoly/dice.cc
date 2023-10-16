#include "dice.h"
#include <iostream>
#include <stdlib.h>
#include <random>
#include <vector>
#include <algorithm>
using namespace std;

int Dice::roll(){
    vector<int> v = {1, 2, 3, 4, 5, 6};
    random_device rd;
    mt19937 gen(rd());
    shuffle(v.begin(), v.end(), gen);
    return v[0];
}

