#include "osap.h"
#include "player.h"
#include <iostream>
#include <string>
using namespace std;

OSAP::OSAP(string name) : NonProperty{name} {}

void OSAP::action(Player & p) {
    cout << p.getname() << " arrived at " << name << endl;
}

