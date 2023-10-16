#include "gototims.h"
#include "player.h"
#include <iostream>
#include <string>
using namespace std;

GoToTims::GoToTims(string name) : NonProperty{name} {}

void GoToTims::action(Player & p) {
    cout << "You arrived at " << name << endl;
    cout << "You have to go to Tims" << endl;
    p.sentToTims(true);
    p.setPosition(10);
}

