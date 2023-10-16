#include "needleshall.h"
#include "player.h"
#include <iostream>
#include <string>
#include <random>
#include <algorithm>
#include <vector>
using namespace std;

NeedlesHall::NeedlesHall(std::string name) : NonProperty(name) {}

void NeedlesHall::action(Player &p)
{
    cout << "You arrived at " << name << endl;
    vector<int> k(99,0);
    k.emplace_back(1);
    vector<int> v = {1, 2, 2, 3, 3, 3, 4, 4, 4, 4, 4, 4, 5, 5, 5, 6, 6, 7};
    std::random_device rd;
    std::mt19937 g(rd());
    for (int i = 0; i < 1000; i++)
    {
        std::shuffle(v.begin(), v.end(), g);
        std::shuffle(k.begin(), k.end(), g);
    }
    int num = v[0];
    int cnum = k[0];
    
    bool cu = p.get_cup_active();

    if(cnum == 1 && cu == true) {
        cout << endl << "You got a Roll Up the Rim Cup! " << endl << endl;
        p.set_cup(p.get_cup() + 1);
    } else {
        if (num == 1)
        {
            cout << "You lost $200" << endl;
            p.adddebt("Bank", 200);
        }
        else if (num == 2)
        {
            cout << "You lost $100" << endl;
            p.adddebt("Bank", 100);
        }
        else if (num == 3)
        {
            cout << "You lost $50" << endl;
            p.adddebt("Bank", 50);
        }
        else if (num == 4)
        {
            cout << "You gained $25" << endl;
            p.addMoney(25);
        }
        else if (num == 5)
        {
            cout << "You gained $50" << endl;
            p.addMoney(50);
        }
        else if (num == 6)
        {
            cout << "You gained $100" << endl;
            p.addMoney(100);
        }
        else if (num == 7)
        {
            cout << "You gained $200" << endl;
            p.addMoney(200);
        }
    }
}

