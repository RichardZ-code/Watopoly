#include "residence.h"
#include "player.h"
#include <iostream>
#include <string>
using namespace std;

Residence::Residence(string name, int purchase_price) : Property{name, purchase_price} {}

void Residence::action(Player & p) {
    cout << "You arrived at " << name << endl;
    
    if(owner->getname() == p.getname()) {
        cout << "You own this property" << endl;
        return;
    }

    int rent = 0;
    if(owner->getResNum() == 1) {
        rent = 25;
    } else if(owner->getResNum() == 2) {
        rent = 50;
    } else if(owner->getResNum() == 3) {
        rent = 100;
    } else if(owner->getResNum() == 4) {
        rent = 200;
    }

    p.adddebt(owner->getname(), rent);

}

bool Residence::improve(bool bs, int cash){
    cout << "You can not improve Residence" << endl;
    return false;
}

