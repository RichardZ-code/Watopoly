#include "tuition.h"
#include "player.h"
#include <iostream>
#include <string>
using namespace std;

Tuition::Tuition(string name) : NonProperty{name} {}

void Tuition::action(Player &p)
{
    cout << "You arrived at " << name << endl;
    cout << "Do you want to pay 10 percent of your total worth or $300?" << endl;
    cout << "Enter 1 for 10 percent or 2 for $300" << endl;
    char choice;
    cin >> choice;
    if (choice == '1')
    {
        int fee = p.netWorth() * 0.1;
        p.adddebt("Bank", fee);
        return;
    }
    else if (choice == '2')
    {
        p.adddebt("Bank", 300);
        return;
    }
    else
    {
        cout << "Invalid input" << endl;
    }
}

