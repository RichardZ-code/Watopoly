#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include "Watopoly.h"

using namespace std;

int main(int argc, char *argv[])
{
    bool test = false;
    Watopoly game;

    if (argc == 1)
    {
        int n;
        cout << "Please enter the number of players(2-7): ";
        std::cin >> n;
        if ((n < 2) || (n > 7))
        {
            cout << " Invalid Player number " << endl;
            return 0;
        }
        game.init(n); // initialize the game with n number of players
    }
    else if (argc == 2)
    {
        std::string a1(argv[1]);
        if (a1 == "-testing")
        {
            test = true; // testing mode enabled
            int n;
            cout << "Please enter the number of players(2-7): ";
            std::cin >> n;
            if ((n < 2) || (n > 7))
            {
                cout << " Invalid Player number " << endl;
                return 0;
            }

            game.init(n); // initialize the game with n number of players
        }
        else
        {
            cout << "Invalid command line argument" << endl; //-testing is the only optional command line argument
            return 1;
        }
    }
    else if (argc == 3)
    {
        std::string a2(argv[1]);
        if (a2 == "-load")
        {
            std::string a3(argv[2]);
            // cout << a3 << endl;
            if (game.load(a3))
            {
            }
            else
            {
                cout << "BAD File read!" << endl;
                return 1;
            }
        }
        else
        {
            cout << "Invalid command line argument" << endl;
            return 0;
        }
    }
    else if (argc == 4)
    { // both load game and testing mode enabled
        std::string a3(argv[1]);
        std::string a4(argv[2]);
        if (a3 == "-testing" && a4 == "-load")
        {
            test = true;
            std::string a5(argv[3]);
            if (game.load(a5))
            {
            }
            else
            {
                cout << "BAD File read!" << endl;
                return 1;
            }
        }
        else
        {
            cout << "Invalid command line argument" << endl;
            return 0;
        }
    }

    cout << game << endl
         << endl;
    cout << "Welcome to Watopoly!" << endl
         << endl;
    bool if_quit = false;
    while (!game.finish() && !if_quit && !cin.eof())
    { // game is only finished when there is only one player left or enter cmd quit
        game.check_cup_active();
        bool next_player = false;
        bool if_roll = false;
        bool cur_broke = false;
        int num_doubles = 0;
        string pname = game.getCurPlayer()->getname();
        cout << "Current Player is " << pname << endl; // display the current player

        string cmd;
        if (game.getCurPlayer()->if_sentToTim())
        {
            game.getCurPlayer()->setDCTime(game.getCurPlayer()->getTimTime() + 1);
            int time = game.getCurPlayer()->getTimTime();
            cout << endl
                 << "You are in DC Tims Line" << endl;
            cout << "It is your " << time << " turn in DC Tims Line" << endl;
            cout << "You can choose to leave DC Tims Line by paying $50, rolling doubles or using a Roll Up the Rim cup" << endl
                 << endl;
        }
        bool c1 = false;
        bool c2 = false;
        bool c3 = false;
        while (game.getCurPlayer()->if_sentToTim() && !cin.eof())
        {
            int time = game.getCurPlayer()->getTimTime();
            if (c1 && c2 && c3 && (time != 3))
            {
                cout << "You don't have other options, now it is next player's turn" << endl;
                game.nextplayer(game.get_Cur_Player());
                next_player = true;
                break;
            }
            cout << "Please enter a command: roll , pay , cup , pass " << endl;
            std::cin >> cmd;
            if (cmd == "roll")
            {
                c1 = true;
                if (if_roll == true)
                {
                    cout << "You have rolled " << endl
                         << endl;
                    continue;
                }
                if (test == false)
                {
                    int di1 = game.roll();
                    int di2 = game.roll();
                    game.getCurPlayer()->setLastRoll(di1 + di2);
                    if_roll = true;
                    if (di1 == di2)
                    {
                        cout << game.getCurPlayer()->getname() << " rolled a double!" << endl;
                        cout << "You are free to leave DC Tims Line" << endl;
                        game.getCurPlayer()->setDCTime(0);
                        game.getCurPlayer()->sentToTims(false);
                        game.playermove(di1 + di2, game.getCurPlayer());
                        game.action(game.getCurPlayer()->getPosition());
                        if (game.ifpurchaseable(game.getCurPlayer()->getPosition()))
                        {
                            cout << "You have landed on " << game.getproperty(game.getCurPlayer()->getPosition())->getName() << endl
                                 << endl;
                            cout << "It cost:" << game.getproperty(game.getCurPlayer()->getPosition())->getPurchasePrice() << endl;
                            if (game.getproperty(game.getCurPlayer()->getPosition())->getPurchasePrice() <= game.getCurPlayer()->getCashAmount())
                            {
                                cout << "Do you want to buy it? (y/n)" << endl
                                     << endl;
                            }
                            else
                            {
                                cout << "You do not have enough money to buy it" << endl;
                                cout << "the building is up for auction " << endl;
                                game.auction(game.getproperty(game.getCurPlayer()->getPosition()), game.getCurPlayer());
                                break;
                            }
                            string answer;
                            while (true)
                            {
                                std::cin >> answer;
                                if (answer == "y")
                                {
                                    game.buybuilding(game.getCurPlayer()->getPosition(), game.getCurPlayer());
                                    break;
                                }
                                else if (answer == "n")
                                {
                                    cout << "You have chosen not to buy it" << endl
                                         << endl;
                                    cout << "The building is now up for auction" << endl
                                         << endl;
                                    game.auction(game.getproperty(game.getCurPlayer()->getPosition()), game.getCurPlayer());
                                    break;
                                }
                                else
                                {
                                    cout << "Invalid input, please enter (y/n) again " << endl;
                                }
                            }
                        }
                    }
                    else
                    {
                        cout << "You did not roll a double" << endl;
                        if (time == 3)
                        {
                            cout << "You have been in DC Tims Line for 3 turns" << endl;
                            cout << "You have to pay $50 or use a Roll Up the Rim cup to leave DC Tims Line" << endl;
                            cout << "Please enter a command: pay , cup" << endl;
                            std::cin >> cmd;
                            if (cmd == "pay")
                            {
                                if (game.getCurPlayer()->getCashAmount() >= 50)
                                {
                                    game.getCurPlayer()->addMoney(-50);
                                    game.getCurPlayer()->setDCTime(0);
                                    game.getCurPlayer()->sentToTims(false);
                                    game.playermove(di1 + di2, game.getCurPlayer());
                                    game.action(game.getCurPlayer()->getPosition());
                                    if (game.ifpurchaseable(game.getCurPlayer()->getPosition()))
                                    {
                                        cout << "You have landed on " << game.getproperty(game.getCurPlayer()->getPosition())->getName() << endl
                                             << endl;
                                        cout << "It cost:" << game.getproperty(game.getCurPlayer()->getPosition())->getPurchasePrice() << endl;
                                        if (game.getproperty(game.getCurPlayer()->getPosition())->getPurchasePrice() <= game.getCurPlayer()->getCashAmount())
                                        {
                                            cout << "Do you want to buy it? (y/n)" << endl
                                                 << endl;
                                        }
                                        else
                                        {
                                            cout << "You do not have enough money to buy it" << endl;
                                            cout << "the building is up for auction " << endl;
                                            game.auction(game.getproperty(game.getCurPlayer()->getPosition()), game.getCurPlayer());
                                            break;
                                        }
                                        string answer;
                                        while (true)
                                        {
                                            std::cin >> answer;
                                            if (answer == "y")
                                            {
                                                game.buybuilding(game.getCurPlayer()->getPosition(), game.getCurPlayer());
                                                break;
                                            }
                                            else if (answer == "n")
                                            {
                                                cout << "You have chosen not to buy it" << endl
                                                     << endl;
                                                cout << "The building is now up for auction" << endl
                                                     << endl;
                                                game.auction(game.getproperty(game.getCurPlayer()->getPosition()), game.getCurPlayer());
                                                break;
                                            }
                                            else
                                            {
                                                cout << "Invalid input, please enter (y/n) again " << endl;
                                            }
                                        }
                                    }
                                }
                                else
                                {
                                    cout << "You do not have enough money to pay" << endl;
                                    game.getCurPlayer()->adddebt("Bank", 50);
                                    if (game.ultimatebankrupt(game.getCurPlayer()))
                                    {
                                        cout << "You are bankrupt" << endl;
                                        cur_broke = true;
                                        break;
                                    }
                                    else
                                    {
                                        cout << "You are free to leave DC Tims Line" << endl;
                                        game.getCurPlayer()->setDCTime(0);
                                        game.getCurPlayer()->sentToTims(false);
                                        game.playermove(di1 + di2, game.getCurPlayer());
                                        game.action(game.getCurPlayer()->getPosition());
                                        if (game.ifpurchaseable(game.getCurPlayer()->getPosition()))
                                        {
                                            cout << "You have landed on " << game.getproperty(game.getCurPlayer()->getPosition())->getName() << endl
                                                 << endl;
                                            cout << "It cost:" << game.getproperty(game.getCurPlayer()->getPosition())->getPurchasePrice() << endl;
                                            if (game.getproperty(game.getCurPlayer()->getPosition())->getPurchasePrice() <= game.getCurPlayer()->getCashAmount())
                                            {
                                                cout << "Do you want to buy it? (y/n)" << endl
                                                     << endl;
                                            }
                                            else
                                            {
                                                cout << "You do not have enough money to buy it" << endl;
                                                cout << "the building is up for auction " << endl;
                                                game.auction(game.getproperty(game.getCurPlayer()->getPosition()), game.getCurPlayer());
                                                break;
                                            }
                                            string answer;
                                            while (true)
                                            {
                                                std::cin >> answer;
                                                if (answer == "y")
                                                {
                                                    game.buybuilding(game.getCurPlayer()->getPosition(), game.getCurPlayer());
                                                    break;
                                                }
                                                else if (answer == "n")
                                                {
                                                    cout << "You have chosen not to buy it" << endl
                                                         << endl;
                                                    cout << "The building is now up for auction" << endl
                                                         << endl;
                                                    game.auction(game.getproperty(game.getCurPlayer()->getPosition()), game.getCurPlayer());
                                                    break;
                                                }
                                                else
                                                {
                                                    cout << "Invalid input, please enter (y/n) again " << endl;
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                            else if (cmd == "cup")
                            {
                                game.getCurPlayer()->setDCTime(0);
                                game.getCurPlayer()->sentToTims(false);
                                game.playermove(di1 + di2, game.getCurPlayer());
                                game.action(game.getCurPlayer()->getPosition());
                                if (game.ifpurchaseable(game.getCurPlayer()->getPosition()))
                                {
                                    cout << "You have landed on " << game.getproperty(game.getCurPlayer()->getPosition())->getName() << endl
                                         << endl;
                                    cout << "It cost:" << game.getproperty(game.getCurPlayer()->getPosition())->getPurchasePrice() << endl;
                                    if (game.getproperty(game.getCurPlayer()->getPosition())->getPurchasePrice() <= game.getCurPlayer()->getCashAmount())
                                    {
                                        cout << "Do you want to buy it? (y/n)" << endl
                                             << endl;
                                    }
                                    else
                                    {
                                        cout << "You do not have enough money to buy it" << endl;
                                        cout << "the building is up for auction " << endl;
                                        game.auction(game.getproperty(game.getCurPlayer()->getPosition()), game.getCurPlayer());
                                        break;
                                    }
                                    string answer;
                                    while (true)
                                    {
                                        std::cin >> answer;
                                        if (answer == "y")
                                        {
                                            game.buybuilding(game.getCurPlayer()->getPosition(), game.getCurPlayer());
                                            break;
                                        }
                                        else if (answer == "n")
                                        {
                                            cout << "You have chosen not to buy it" << endl
                                                 << endl;
                                            cout << "The building is now up for auction" << endl
                                                 << endl;
                                            game.auction(game.getproperty(game.getCurPlayer()->getPosition()), game.getCurPlayer());
                                            break;
                                        }
                                        else
                                        {
                                            cout << "Invalid input, please enter (y/n) again " << endl;
                                        }
                                    }
                                }
                            }
                            else
                            {
                                cout << "Invalid command" << endl;
                            }
                        }
                    }
                }
                else
                {
                    int di1;
                    int di2;
                    std::cin >> di1 >> di2;
                    game.getCurPlayer()->setLastRoll(di1 + di2);
                    if_roll = true;
                    if (di1 == di2)
                    {
                        cout << game.getCurPlayer()->getname() << " rolled a double!" << endl;
                        game.getCurPlayer()->setDCTime(0);
                        game.getCurPlayer()->sentToTims(false);
                        game.playermove(di1 + di2, game.getCurPlayer());
                        game.action(game.getCurPlayer()->getPosition());
                        if (game.ifpurchaseable(game.getCurPlayer()->getPosition()))
                        {
                            cout << "You have landed on " << game.getproperty(game.getCurPlayer()->getPosition())->getName() << endl
                                 << endl;
                            cout << "It cost:" << game.getproperty(game.getCurPlayer()->getPosition())->getPurchasePrice() << endl;
                            if (game.getproperty(game.getCurPlayer()->getPosition())->getPurchasePrice() <= game.getCurPlayer()->getCashAmount())
                            {
                                cout << "Do you want to buy it? (y/n)" << endl
                                     << endl;
                            }
                            else
                            {
                                cout << "You do not have enough money to buy it" << endl;
                                cout << "the building is up for auction " << endl;
                                game.auction(game.getproperty(game.getCurPlayer()->getPosition()), game.getCurPlayer());
                                break;
                            }
                            string answer;
                            while (true)
                            {
                                std::cin >> answer;
                                if (answer == "y")
                                {
                                    game.buybuilding(game.getCurPlayer()->getPosition(), game.getCurPlayer());
                                    break;
                                }
                                else if (answer == "n")
                                {
                                    cout << "You have chosen not to buy it" << endl
                                         << endl;
                                    cout << "The building is now up for auction" << endl
                                         << endl;
                                    game.auction(game.getproperty(game.getCurPlayer()->getPosition()), game.getCurPlayer());
                                    break;
                                }
                                else
                                {
                                    cout << "Invalid input, please enter (y/n) again " << endl;
                                }
                            }
                        }
                    }
                    else
                    {
                        cout << "You did not roll a double" << endl;
                        if (time == 3)
                        {
                            cout << "You have been in DC Tims Line for 3 turns" << endl;
                            cout << "You have to pay $50 or use a Roll Up the Rim cup to leave DC Tims Line" << endl;
                            cout << "Please enter a command: pay , cup" << endl;
                            std::cin >> cmd;
                            if (cmd == "pay")
                            {
                                if (game.getCurPlayer()->getCashAmount() >= 50)
                                {
                                    game.getCurPlayer()->addMoney(-50);
                                    game.getCurPlayer()->setDCTime(0);
                                    game.getCurPlayer()->sentToTims(false);
                                    game.playermove(di1 + di2, game.getCurPlayer());
                                    game.action(game.getCurPlayer()->getPosition());
                                    if (game.ifpurchaseable(game.getCurPlayer()->getPosition()))
                                    {
                                        cout << "You have landed on " << game.getproperty(game.getCurPlayer()->getPosition())->getName() << endl
                                             << endl;
                                        cout << "It cost:" << game.getproperty(game.getCurPlayer()->getPosition())->getPurchasePrice() << endl;
                                        if (game.getproperty(game.getCurPlayer()->getPosition())->getPurchasePrice() <= game.getCurPlayer()->getCashAmount())
                                        {
                                            cout << "Do you want to buy it? (y/n)" << endl
                                                 << endl;
                                        }
                                        else
                                        {
                                            cout << "You do not have enough money to buy it" << endl;
                                            cout << "the building is up for auction " << endl;
                                            game.auction(game.getproperty(game.getCurPlayer()->getPosition()), game.getCurPlayer());
                                            break;
                                        }
                                        string answer;
                                        while (true)
                                        {
                                            std::cin >> answer;
                                            if (answer == "y")
                                            {
                                                game.buybuilding(game.getCurPlayer()->getPosition(), game.getCurPlayer());
                                                break;
                                            }
                                            else if (answer == "n")
                                            {
                                                cout << "You have chosen not to buy it" << endl
                                                     << endl;
                                                cout << "The building is now up for auction" << endl
                                                     << endl;
                                                game.auction(game.getproperty(game.getCurPlayer()->getPosition()), game.getCurPlayer());
                                                break;
                                            }
                                            else
                                            {
                                                cout << "Invalid input, please enter (y/n) again " << endl;
                                            }
                                        }
                                    }
                                }
                                else
                                {
                                    cout << "You do not have enough money to pay" << endl;
                                    game.getCurPlayer()->adddebt("Bank", 50);
                                    if (game.ultimatebankrupt(game.getCurPlayer()))
                                    {
                                        cout << "You are bankrupt" << endl;
                                        cur_broke = true;
                                        break;
                                    }
                                    else
                                    {
                                        cout << "You are free to leave DC Tims Line" << endl;
                                        game.getCurPlayer()->setDCTime(0);
                                        game.getCurPlayer()->sentToTims(false);
                                        game.playermove(di1 + di2, game.getCurPlayer());
                                        game.action(game.getCurPlayer()->getPosition());
                                        if (game.ifpurchaseable(game.getCurPlayer()->getPosition()))
                                        {
                                            cout << "You have landed on " << game.getproperty(game.getCurPlayer()->getPosition())->getName() << endl
                                                 << endl;
                                            cout << "It cost:" << game.getproperty(game.getCurPlayer()->getPosition())->getPurchasePrice() << endl;
                                            if (game.getproperty(game.getCurPlayer()->getPosition())->getPurchasePrice() <= game.getCurPlayer()->getCashAmount())
                                            {
                                                cout << "Do you want to buy it? (y/n)" << endl
                                                     << endl;
                                            }
                                            else
                                            {
                                                cout << "You do not have enough money to buy it" << endl;
                                                cout << "the building is up for auction " << endl;
                                                game.auction(game.getproperty(game.getCurPlayer()->getPosition()), game.getCurPlayer());
                                                break;
                                            }
                                            string answer;
                                            while (true)
                                            {
                                                std::cin >> answer;
                                                if (answer == "y")
                                                {
                                                    game.buybuilding(game.getCurPlayer()->getPosition(), game.getCurPlayer());
                                                    break;
                                                }
                                                else if (answer == "n")
                                                {
                                                    cout << "You have chosen not to buy it" << endl
                                                         << endl;
                                                    cout << "The building is now up for auction" << endl
                                                         << endl;
                                                    game.auction(game.getproperty(game.getCurPlayer()->getPosition()), game.getCurPlayer());
                                                    break;
                                                }
                                                else
                                                {
                                                    cout << "Invalid input, please enter (y/n) again " << endl;
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                            else if (cmd == "cup")
                            {
                                game.getCurPlayer()->setDCTime(0);
                                game.getCurPlayer()->sentToTims(false);
                                game.playermove(di1 + di2, game.getCurPlayer());
                                game.action(game.getCurPlayer()->getPosition());
                                if (game.ifpurchaseable(game.getCurPlayer()->getPosition()))
                                {
                                    cout << "You have landed on " << game.getproperty(game.getCurPlayer()->getPosition())->getName() << endl
                                         << endl;
                                    cout << "It cost:" << game.getproperty(game.getCurPlayer()->getPosition())->getPurchasePrice() << endl;
                                    if (game.getproperty(game.getCurPlayer()->getPosition())->getPurchasePrice() <= game.getCurPlayer()->getCashAmount())
                                    {
                                        cout << "Do you want to buy it? (y/n)" << endl
                                             << endl;
                                    }
                                    else
                                    {
                                        cout << "You do not have enough money to buy it" << endl;
                                        cout << "the building is up for auction " << endl;
                                        game.auction(game.getproperty(game.getCurPlayer()->getPosition()), game.getCurPlayer());
                                        break;
                                    }
                                    string answer;
                                    while (true)
                                    {
                                        std::cin >> answer;
                                        if (answer == "y")
                                        {
                                            game.buybuilding(game.getCurPlayer()->getPosition(), game.getCurPlayer());
                                            break;
                                        }
                                        else if (answer == "n")
                                        {
                                            cout << "You have chosen not to buy it" << endl
                                                 << endl;
                                            cout << "The building is now up for auction" << endl
                                                 << endl;
                                            game.auction(game.getproperty(game.getCurPlayer()->getPosition()), game.getCurPlayer());
                                            break;
                                        }
                                        else
                                        {
                                            cout << "Invalid input, please enter (y/n) again " << endl;
                                        }
                                    }
                                }
                            }
                            else
                            {
                                cout << "Invalid command" << endl;
                            }
                        }
                    }
                }
            }
            else if (cmd == "pay")
            {
                c2 = true;
                if (game.getCurPlayer()->getCashAmount() >= 50)
                {
                    game.getCurPlayer()->addMoney(-50);
                    game.getCurPlayer()->setDCTime(0);
                    game.getCurPlayer()->sentToTims(false);
                    game.playermove(game.getCurPlayer()->getLastRoll(), game.getCurPlayer());
                    game.action(game.getCurPlayer()->getPosition());
                    if (game.ifpurchaseable(game.getCurPlayer()->getPosition()))
                    {
                        cout << "You have landed on " << game.getproperty(game.getCurPlayer()->getPosition())->getName() << endl
                             << endl;
                        cout << "It cost:" << game.getproperty(game.getCurPlayer()->getPosition())->getPurchasePrice() << endl;
                        if (game.getproperty(game.getCurPlayer()->getPosition())->getPurchasePrice() <= game.getCurPlayer()->getCashAmount())
                        {
                            cout << "Do you want to buy it? (y/n)" << endl
                                 << endl;
                        }
                        else
                        {
                            cout << "You do not have enough money to buy it" << endl;
                            cout << "the building is up for auction " << endl;
                            game.auction(game.getproperty(game.getCurPlayer()->getPosition()), game.getCurPlayer());
                            break;
                        }
                        string answer;
                        while (true)
                        {
                            std::cin >> answer;
                            if (answer == "y")
                            {
                                game.buybuilding(game.getCurPlayer()->getPosition(), game.getCurPlayer());
                                break;
                            }
                            else if (answer == "n")
                            {
                                cout << "You have chosen not to buy it" << endl
                                     << endl;
                                cout << "The building is now up for auction" << endl
                                     << endl;
                                game.auction(game.getproperty(game.getCurPlayer()->getPosition()), game.getCurPlayer());
                                break;
                            }
                            else
                            {
                                cout << "Invalid input, please enter (y/n) again " << endl;
                            }
                        }
                    }
                }
                else
                {
                    cout << "You do not have enough money to pay" << endl;
                    if (time == 3)
                    {
                        if (game.ultimatebankrupt(game.getCurPlayer()))
                        {
                            cout << "You are bankrupt" << endl;
                            cur_broke = true;
                            break;
                        }
                        else
                        {
                            cout << "You are free to leave DC Tims Line" << endl;
                            game.getCurPlayer()->setDCTime(0);
                            game.getCurPlayer()->sentToTims(false);
                            game.playermove(0, game.getCurPlayer());
                            game.action(game.getCurPlayer()->getPosition());
                            if (game.ifpurchaseable(game.getCurPlayer()->getPosition()))
                            {
                                cout << "You have landed on " << game.getproperty(game.getCurPlayer()->getPosition())->getName() << endl
                                     << endl;
                                cout << "It cost:" << game.getproperty(game.getCurPlayer()->getPosition())->getPurchasePrice() << endl;
                                if (game.getproperty(game.getCurPlayer()->getPosition())->getPurchasePrice() <= game.getCurPlayer()->getCashAmount())
                                {
                                    cout << "Do you want to buy it? (y/n)" << endl
                                         << endl;
                                }
                                else
                                {
                                    cout << "You do not have enough money to buy it" << endl;
                                    cout << "the building is up for auction " << endl;
                                    game.auction(game.getproperty(game.getCurPlayer()->getPosition()), game.getCurPlayer());
                                    break;
                                }
                                string answer;
                                while (true)
                                {
                                    std::cin >> answer;
                                    if (answer == "y")
                                    {
                                        game.buybuilding(game.getCurPlayer()->getPosition(), game.getCurPlayer());
                                        break;
                                    }
                                    else if (answer == "n")
                                    {
                                        cout << "You have chosen not to buy it" << endl
                                             << endl;
                                        cout << "The building is now up for auction" << endl
                                             << endl;
                                        game.auction(game.getproperty(game.getCurPlayer()->getPosition()), game.getCurPlayer());
                                        break;
                                    }
                                    else
                                    {
                                        cout << "Invalid input, please enter (y/n) again " << endl;
                                    }
                                }
                            }
                        }
                    }
                }
            }
            else if (cmd == "cup")
            {
                c3 = true;
                if (game.getCurPlayer()->get_cup() > 0)
                {
                    game.getCurPlayer()->set_cup(game.getCurPlayer()->get_cup() - 1);
                    game.getCurPlayer()->setDCTime(0);
                    game.getCurPlayer()->sentToTims(false);
                    game.playermove(0, game.getCurPlayer());
                    game.action(game.getCurPlayer()->getPosition());
                    if (game.ifpurchaseable(game.getCurPlayer()->getPosition()))
                    {
                        cout << "You have landed on " << game.getproperty(game.getCurPlayer()->getPosition())->getName() << endl
                             << endl;
                        cout << "It cost:" << game.getproperty(game.getCurPlayer()->getPosition())->getPurchasePrice() << endl;
                        if (game.getproperty(game.getCurPlayer()->getPosition())->getPurchasePrice() <= game.getCurPlayer()->getCashAmount())
                        {
                            cout << "Do you want to buy it? (y/n)" << endl
                                 << endl;
                        }
                        else
                        {
                            cout << "You do not have enough money to buy it" << endl;
                            cout << "the building is up for auction " << endl;
                            game.auction(game.getproperty(game.getCurPlayer()->getPosition()), game.getCurPlayer());
                            break;
                        }
                        string answer;
                        while (true)
                        {
                            std::cin >> answer;
                            if (answer == "y")
                            {
                                game.buybuilding(game.getCurPlayer()->getPosition(), game.getCurPlayer());
                                break;
                            }
                            else if (answer == "n")
                            {
                                cout << "You have chosen not to buy it" << endl
                                     << endl;
                                cout << "The building is now up for auction" << endl
                                     << endl;
                                game.auction(game.getproperty(game.getCurPlayer()->getPosition()), game.getCurPlayer());
                                break;
                            }
                            else
                            {
                                cout << "Invalid input, please enter (y/n) again " << endl;
                            }
                        }
                    }
                }
                else
                {
                    cout << "You do not have any Roll Up the Rim cup" << endl;
                    if (time == 3)
                    {
                        game.getCurPlayer()->adddebt("Bank", 50);
                        if (game.ultimatebankrupt(game.getCurPlayer()))
                        {
                            cout << "You are bankrupt" << endl;
                            cur_broke = true;
                            break;
                        }
                        else
                        {
                            cout << "You are free to leave DC Tims Line" << endl;
                            game.getCurPlayer()->setDCTime(0);
                            game.getCurPlayer()->sentToTims(false);
                            game.playermove(0, game.getCurPlayer());
                            game.action(game.getCurPlayer()->getPosition());
                            if (game.ifpurchaseable(game.getCurPlayer()->getPosition()))
                            {
                                cout << "You have landed on " << game.getproperty(game.getCurPlayer()->getPosition())->getName() << endl
                                     << endl;
                                cout << "It cost:" << game.getproperty(game.getCurPlayer()->getPosition())->getPurchasePrice() << endl;
                                if (game.getproperty(game.getCurPlayer()->getPosition())->getPurchasePrice() <= game.getCurPlayer()->getCashAmount())
                                {
                                    cout << "Do you want to buy it? (y/n)" << endl
                                         << endl;
                                }
                                else
                                {
                                    cout << "You do not have enough money to buy it" << endl;
                                    cout << "the building is up for auction " << endl;
                                    game.auction(game.getproperty(game.getCurPlayer()->getPosition()), game.getCurPlayer());
                                    break;
                                }
                                string answer;
                                while (true)
                                {
                                    std::cin >> answer;
                                    if (answer == "y")
                                    {
                                        game.buybuilding(game.getCurPlayer()->getPosition(), game.getCurPlayer());
                                        break;
                                    }
                                    else if (answer == "n")
                                    {
                                        cout << "You have chosen not to buy it" << endl
                                             << endl;
                                        cout << "The building is now up for auction" << endl
                                             << endl;
                                        game.auction(game.getproperty(game.getCurPlayer()->getPosition()), game.getCurPlayer());
                                        break;
                                    }
                                    else
                                    {
                                        cout << "Invalid input, please enter (y/n) again " << endl;
                                    }
                                }
                            }
                        }
                    }
                }
            }
            else if (cmd == "pass")
            {
                cout << endl
                     << "You decided to pass to the next player " << endl
                     << endl;
                game.nextplayer(game.get_Cur_Player());
                next_player = true;
                break;
            }
            else
            {
                cout << "Invalid command" << endl
                     << endl;
            }
        }

        if (cur_broke)
        {
            continue;
        }

        while (next_player == false && !if_quit && !cin.eof())
        {
            string cmd;
            cout << endl
                 << "Please enter a command: ";
            std::cin >> cmd; // get the command from the user
            cout << endl;
            if (cmd == "roll")
            {
                if (if_roll == false)
                {
                    if (test == false)
                    { // if testing mode is not enabled, roll the dice
                        int di1 = game.roll();
                        int di2 = game.roll();
                        if_roll = true;
                        game.playermove(di1 + di2, game.getCurPlayer());
                        int curp = game.getCurPlayer()->getPosition();
                        cout << game << endl;
                        if (di1 == di2)
                        {
                            num_doubles++;
                            cout << game.getCurPlayer()->getname() << " rolled " << di1 << " " << di2 << ", total is " << di1 + di2 << endl
                                 << endl;
                            cout << game.getCurPlayer()->getname() << " rolled a double!" << endl
                                 << endl;
                            if_roll = false;
                            if (num_doubles == 3)
                            {
                                game.sentToTims(game.getCurPlayer());
                                game.nextplayer(game.get_Cur_Player());
                                next_player = true;
                                break;
                            }
                            else
                            {
                                cout << "You can roll again! " << endl
                                     << endl;
                            }
                        }
                        else
                        {
                            cout << game.getCurPlayer()->getname() << " rolled " << di1 << " " << di2 << ", total is " << di1 + di2 << endl
                                 << endl;
                        }

                        game.getCurPlayer()->setLastRoll(di1 + di2);
                        if (game.isproperty(game.getCurPlayer()->getPosition()))
                        {
                            if (game.ifpurchaseable(game.getCurPlayer()->getPosition()))
                            {
                                cout << "You have landed on " << game.getproperty(game.getCurPlayer()->getPosition())->getName() << endl
                                     << endl;
                                cout << "It cost:" << game.getproperty(game.getCurPlayer()->getPosition())->getPurchasePrice() << endl;
                                if (game.getproperty(game.getCurPlayer()->getPosition())->getPurchasePrice() <= game.getCurPlayer()->getCashAmount())
                                {
                                    cout << "Do you want to buy it? (y/n)" << endl
                                         << endl;
                                }
                                else
                                {
                                    cout << "You do not have enough money to buy it" << endl;
                                    cout << "the building is up for auction " << endl;
                                    game.auction(game.getproperty(game.getCurPlayer()->getPosition()), game.getCurPlayer());
                                    break;
                                }
                                string answer;
                                while (true)
                                {
                                    std::cin >> answer;
                                    if (answer == "y")
                                    {
                                        game.buybuilding(game.getCurPlayer()->getPosition(), game.getCurPlayer());
                                        break;
                                    }
                                    else if (answer == "n")
                                    {
                                        cout << "You have chosen not to buy it" << endl
                                             << endl;
                                        cout << "The building is now up for auction" << endl
                                             << endl;
                                        game.auction(game.getproperty(game.getCurPlayer()->getPosition()), game.getCurPlayer());
                                        break;
                                    }
                                    else
                                    {
                                        cout << "Invalid input, please enter (y/n) again " << endl;
                                    }
                                }
                            }
                            else
                            {
                                game.action(game.getCurPlayer()->getPosition());

                                if (curp != game.getCurPlayer()->getPosition())
                                {
                                    cout << game << endl;
                                }
                                if (game.ifpurchaseable(game.getCurPlayer()->getPosition()))
                                {
                                    cout << "You have landed on " << game.getproperty(game.getCurPlayer()->getPosition())->getName() << endl
                                         << endl;
                                    cout << "It cost:" << game.getproperty(game.getCurPlayer()->getPosition())->getPurchasePrice() << endl;
                                    if (game.getproperty(game.getCurPlayer()->getPosition())->getPurchasePrice() <= game.getCurPlayer()->getCashAmount())
                                    {
                                        cout << "Do you want to buy it? (y/n)" << endl
                                             << endl;
                                    }
                                    else
                                    {
                                        cout << "You do not have enough money to buy it" << endl;
                                        cout << "the building is up for auction " << endl;
                                        game.auction(game.getproperty(game.getCurPlayer()->getPosition()), game.getCurPlayer());
                                        break;
                                    }
                                    string answer;
                                    while (true)
                                    {
                                        std::cin >> answer;
                                        if (answer == "y")
                                        {
                                            game.buybuilding(game.getCurPlayer()->getPosition(), game.getCurPlayer());
                                            break;
                                        }
                                        else if (answer == "n")
                                        {
                                            cout << "You have chosen not to buy it" << endl
                                                 << endl;
                                            cout << "The building is now up for auction" << endl
                                                 << endl;
                                            game.auction(game.getproperty(game.getCurPlayer()->getPosition()), game.getCurPlayer());
                                            break;
                                        }
                                        else
                                        {
                                            cout << "Invalid input, please enter (y/n) again " << endl;
                                        }
                                    }
                                }
                            }
                        }
                        else
                        {
                            game.action(game.getCurPlayer()->getPosition());
                            if (game.getCurPlayer()->if_sentToTim())
                            {
                                cout << game << endl;
                                game.nextplayer(game.get_Cur_Player());
                                cout << "Now is next player's turn" << endl;
                                next_player = true;
                            }
                            if (curp != game.getCurPlayer()->getPosition())
                            {
                                cout << game << endl;
                            }
                            if (game.ifpurchaseable(game.getCurPlayer()->getPosition()))
                            {
                                cout << "You have landed on " << game.getproperty(game.getCurPlayer()->getPosition())->getName() << endl
                                     << endl;
                                cout << "It cost:" << game.getproperty(game.getCurPlayer()->getPosition())->getPurchasePrice() << endl;
                                if (game.getproperty(game.getCurPlayer()->getPosition())->getPurchasePrice() <= game.getCurPlayer()->getCashAmount())
                                {
                                    cout << "Do you want to buy it? (y/n)" << endl
                                         << endl;
                                }
                                else
                                {
                                    cout << "You do not have enough money to buy it" << endl;
                                    cout << "the building is up for auction " << endl;
                                    game.auction(game.getproperty(game.getCurPlayer()->getPosition()), game.getCurPlayer());
                                    break;
                                }
                                string answer;
                                while (true)
                                {
                                    std::cin >> answer;
                                    if (answer == "y")
                                    {
                                        game.buybuilding(game.getCurPlayer()->getPosition(), game.getCurPlayer());
                                        break;
                                    }
                                    else if (answer == "n")
                                    {
                                        cout << "You have chosen not to buy it" << endl
                                             << endl;
                                        cout << "The building is now up for auction" << endl
                                             << endl;
                                        game.auction(game.getproperty(game.getCurPlayer()->getPosition()), game.getCurPlayer());
                                        break;
                                    }
                                    else
                                    {
                                        cout << "Invalid input, please enter (y/n) again " << endl;
                                    }
                                }
                            }
                        }
                    }
                    else
                    {
                        int di1;
                        int di2;
                        std::cin >> di1 >> di2;
                        if_roll = true;
                        game.playermove(di1 + di2, game.getCurPlayer());
                        int curp = game.getCurPlayer()->getPosition();
                        cout << game << endl;
                        if (di1 == di2)
                        {
                            num_doubles++;
                            cout << game.getCurPlayer()->getname() << " rolled " << di1 << " " << di2 << ", total is " << di1 + di2 << endl
                                 << endl;
                            cout << "You rolled a double!" << endl
                                 << endl;
                            if_roll = false;
                            if (num_doubles == 3)
                            {
                                game.sentToTims(game.getCurPlayer());
                                game.nextplayer(game.get_Cur_Player());
                                next_player = true;
                                break;
                            }
                            else
                            {
                                cout << "You can roll again! " << endl
                                     << endl;
                            }
                        }
                        else
                        {
                            cout << game.getCurPlayer()->getname() << " rolled " << di1 << " " << di2 << ", total is " << di1 + di2 << endl
                                 << endl;
                        }
                        game.getCurPlayer()->setLastRoll(di1 + di2);
                        if (game.isproperty(game.getCurPlayer()->getPosition()))
                        {
                            // cout << "here" << endl;
                            if (game.ifpurchaseable(game.getCurPlayer()->getPosition()))
                            {
                                cout << "You have landed on " << game.getproperty(game.getCurPlayer()->getPosition())->getName() << endl
                                     << endl;
                                cout << "It cost:" << game.getproperty(game.getCurPlayer()->getPosition())->getPurchasePrice() << endl;
                                if (game.getproperty(game.getCurPlayer()->getPosition())->getPurchasePrice() <= game.getCurPlayer()->getCashAmount())
                                {
                                    cout << "Do you want to buy it? (y/n)" << endl
                                         << endl;
                                }
                                else
                                {
                                    cout << "You do not have enough money to buy it" << endl;
                                    cout << "the building is up for auction " << endl;
                                    game.auction(game.getproperty(game.getCurPlayer()->getPosition()), game.getCurPlayer());
                                    break;
                                }
                                string answer;
                                while (true)
                                {
                                    std::cin >> answer;
                                    if (answer == "y")
                                    {
                                        game.buybuilding(game.getCurPlayer()->getPosition(), game.getCurPlayer());
                                        break;
                                    }
                                    else if (answer == "n")
                                    {
                                        cout << "You have chosen not to buy it" << endl
                                             << endl;
                                        cout << "The building is now up for auction" << endl
                                             << endl;
                                        game.auction(game.getproperty(game.getCurPlayer()->getPosition()), game.getCurPlayer());
                                        break;
                                    }
                                    else
                                    {
                                        cout << "Invalid input, please enter (y/n) again " << endl;
                                    }
                                }
                            }
                            else
                            {
                                game.action(game.getCurPlayer()->getPosition());
                                if (curp != game.getCurPlayer()->getPosition())
                                {
                                    cout << game << endl;
                                }
                            }
                        }
                        else
                        {
                            game.action(game.getCurPlayer()->getPosition());
                            if (game.getCurPlayer()->if_sentToTim())
                            {
                                cout << game << endl;
                                game.nextplayer(game.get_Cur_Player());
                                cout << "Now is next player's turn" << endl;
                                next_player = true;
                            }
                            if (curp != game.getCurPlayer()->getPosition())
                            {
                                cout << game << endl;
                            }
                            if (game.ifpurchaseable(game.getCurPlayer()->getPosition()))
                            {
                                cout << "You have landed on " << game.getproperty(game.getCurPlayer()->getPosition())->getName() << endl
                                     << endl;
                                cout << "It cost:" << game.getproperty(game.getCurPlayer()->getPosition())->getPurchasePrice() << endl;
                                if (game.getproperty(game.getCurPlayer()->getPosition())->getPurchasePrice() <= game.getCurPlayer()->getCashAmount())
                                {
                                    cout << "Do you want to buy it? (y/n)" << endl
                                         << endl;
                                }
                                else
                                {
                                    cout << "You do not have enough money to buy it" << endl;
                                    cout << "the building is up for auction " << endl;
                                    game.auction(game.getproperty(game.getCurPlayer()->getPosition()), game.getCurPlayer());
                                    break;
                                }
                                string answer;
                                while (true)
                                {
                                    std::cin >> answer;
                                    if (answer == "y")
                                    {
                                        game.buybuilding(game.getCurPlayer()->getPosition(), game.getCurPlayer());
                                        break;
                                    }
                                    else if (answer == "n")
                                    {
                                        cout << "You have chosen not to buy it" << endl
                                             << endl;
                                        cout << "The building is now up for auction" << endl
                                             << endl;
                                        game.auction(game.getproperty(game.getCurPlayer()->getPosition()), game.getCurPlayer());
                                        break;
                                    }
                                    else
                                    {
                                        cout << "Invalid input, please enter (y/n) again " << endl;
                                    }
                                }
                            }
                        }
                    }
                }
                else
                {
                    cout << "You have already rolled" << endl;
                }
            }
            else if (cmd == "next")
            {
                if (if_roll == false)
                {
                    cout << "You havn't rolled this turn" << endl;
                }
                else
                {
                    cout << endl
                         << "Now is next player's turn" << endl
                         << endl;
                    game.nextplayer(game.get_Cur_Player());
                    next_player = true;
                }
            }
            else if (cmd == "trade")
            {
                string name;
                string give;
                string receive;
                std::cin >> name;

                if (name == "GRT")
                {
                    std::cin >> name;
                    name = "GRT Bus";
                }
                else if (name == "Tim")
                {
                    std::cin >> name >> name;
                    name = "Tim Hortons Doughnut";
                }
                else if (name == "Pink")
                {
                    std::cin >> name;
                    name = "Pink Tie";
                }

                std::cin >> give >> receive;

                game.trade(name, give, receive);
            }
            else if (cmd == "improve")
            {

                string buildingname;
                string option;
                bool buy_or_sell = false;
                std::cin >> buildingname >> option;
                if (game.improvable(buildingname, game.getCurPlayer()))
                {
                    if (option == "buy")
                    {
                        buy_or_sell = true;
                        game.improve(buildingname, buy_or_sell);
                    }
                    else if (option == "sell")
                    {
                        game.improve(buildingname, buy_or_sell);
                    }
                    else
                    {
                        cout << "Invalid command" << endl;
                    }
                }
                else
                {
                    cout << "You cannot improve this building" << endl;
                }
            }
            else if (cmd == "mortgage")
            {

                string buildingname;
                std::cin >> buildingname;
                game.mortgagebuilding(buildingname, game.getCurPlayer()); // do we need to pass by reference or pointer to modify building object?
            }
            else if (cmd == "unmortgage")
            {

                string buildingname;
                std::cin >> buildingname;
                game.unmortgagebuilding(buildingname, game.getCurPlayer());
            }
            else if (cmd == "assets")
            {
                game.assets();
            }
            else if (cmd == "save")
            {
                string filename;
                std::cin >> filename;
                game.save(filename);
            }
            else if (cmd == "all")
            {
                game.all();
            }
            else if (cmd == "quit")
            {
                if_quit = true;
                break;
            }
            else if (cmd == "help")
            {
                cout << "=========================================" << endl
                     << endl;
                cout << " Here are the commands you can use: " << endl
                     << endl;
                cout << " roll: roll two dice" << endl
                     << endl;
                cout << " next: go to the next player" << endl
                     << endl;
                cout << " trade <name> <give> <receive>: trade with other players" << endl
                     << endl;
                cout << " improve <property> buy/sell: improve or sell improvements of your building" << endl
                     << endl;
                cout << " mortgage <property>: mortgage your building" << endl
                     << endl;
                cout << " unmortgage <property>: unmortgage your building" << endl
                     << endl;
                cout << " assets: show your assets" << endl
                     << endl;
                cout << " all: show all the assets of all players" << endl
                     << endl;
                cout << " save <filename>: save the game" << endl
                     << endl;
                cout << " quit: quit the game" << endl
                     << endl;
                cout << "=========================================" << endl;
            }
            else
            {
                cout << "Invalid command" << endl;
                // break;
            }

            if (game.ultimatebankrupt(game.getCurPlayer()))
            {
                next_player = true;
            }
        }
    }
    return 0;
}

