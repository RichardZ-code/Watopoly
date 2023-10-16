#include "dctimsline.h"
#include "player.h"
#include <iostream>
#include <string>
using namespace std;

DCTL::DCTL(string name) : NonProperty{name} {}


void DCTL::action(Player & p) {
        if( p.if_sentToTim()){
                cout << "You are sent to DC Tims Line " << endl << endl;
        } else {
                cout << p.getname() << " arrived at " << name << endl;
        }
}


