#include "coopfee.h"
#include "player.h"
#include <iostream>
#include <string>
using namespace std;

CoopFee::CoopFee(string name) : NonProperty{name} {}

void CoopFee::action(Player &p)
{
    cout << "You arrived at " << name << endl;
    cout << "You have to pay $150 to the coop fee" << endl;
    p.adddebt("Bank", 150);
}
