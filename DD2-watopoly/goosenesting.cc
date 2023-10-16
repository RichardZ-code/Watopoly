#include "goosenesting.h"
#include "player.h"
#include <iostream>
#include <string>
using namespace std;


GooseNesting::GooseNesting(string name) : NonProperty{name} {}

void GooseNesting::action(Player & p) {
    cout << "You arrived at " << name << endl;
    cout << "You are attacked by a flock of geese!" << endl;
}

