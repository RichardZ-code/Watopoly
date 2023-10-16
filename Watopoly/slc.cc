#include "slc.h"
#include "player.h"
#include <iostream>
#include <string>
#include <random>
#include <algorithm>
#include <vector>
using namespace std;

SLC::SLC(string name): NonProperty(name) {}

void SLC::action(Player & p) {
    cout << endl << "You arrived at " << name << endl << endl;
    vector<int> v = {1,1,1, 2,2,2,2, 3,3,3,3, 4,4,4, 5,5,5,5, 6,6,6,6, 7,8};
    vector<int> k(99,0);
    k.emplace_back(1);
    random_device rd;
    mt19937 g(rd());
    for(int i = 0; i < 1000; i++) {
        std::shuffle(v.begin(), v.end(), g);
        std::shuffle(k.begin(), k.end(), g);
    }
    int num = v[0];
    int cnum = k[0];
    bool cu = p.get_cup_active();
    if(cnum == 1 && cu == true){
        cout<< endl << "You got a Roll Up the Rim cup!" << endl << endl;
        p.set_cup(p.get_cup() + 1);

    } else {
        if(num==1){
            p.move(-3);
            cout << "You have been moved back 3 spaces." << endl;
        } else if( num == 2){
            p.move(-2);
            cout << "You have been moved back 2 spaces." << endl;
        } else if( num == 3){
            p.move(-1);
            cout << "You have been moved back 1 space." << endl;

        } else if( num == 4){
            p.move(1);
            cout << "You have been moved forward 1 space." << endl;

        } else if( num == 5){
            p.move(2);
            cout << "You have been moved forward 2 spaces." << endl;

        } else if( num == 6){
            p.move(3);
            cout << "You have been moved forward 3 spaces." << endl;

        } else if( num == 7){
            p.setPosition(10);// need to fix this
            p.sentToTims(true);
            p.setDCTime(0);
            cout << "You have been sent to DC Tims Line." << endl;

        } else if( num == 8){
            p.setPosition(0);
            cout << "You have been moved to OSAP." << endl;
        }
    }
}

