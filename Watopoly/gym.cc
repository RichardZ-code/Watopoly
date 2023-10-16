#include "gym.h"
#include "player.h"
#include <iostream>
#include <string>
using namespace std;

Gym::Gym(string name, int purchase_price) : Property{name, purchase_price} {}

void Gym::action(Player & p) {
    cout << "You arrived at " << name << endl;

    if(owner->getname() == p.getname()) {
        cout << "You own this property" << endl;
        return;
    }
    int fee = 0;

    if(owner->getGymNum() == 1) {
        fee = 4 * p.getLastRoll();
    } else if(owner->getGymNum() == 2) {
        fee = 10 * p.getLastRoll();
    }
    
    p.adddebt(owner->getname(), fee);
}

bool Gym::improve(bool bs, int cash){
    cout << "You can not improve Gyms" << endl;
    return false;
}


