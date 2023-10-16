#include <iostream>
#include <string>
#include <vector>
#include "player.h"
using namespace std;

std::vector<std::shared_ptr<Building>> properties;
creditor owe_whom;
std::string name;
int cash;
int pos;
bool sentToTim;
int Timtime;
char player_id;
int cup_own;
int lastroll;

Player::Player(string k, char id) : owe_whom{creditor{"None", 0}}, name{k}, cash{1500}, pos{0},
                                    sentToTim{false}, Timtime{0}, player_id{id}, cup_own{0}, lastroll{0}, cup_active{true}{}

string Player::getname()
{
    return name;
}

int Player::getCashAmount()
{
    return cash;
} // get player's cash amount

creditor Player::getCreditor()
{
    return owe_whom;
}

bool Player::AbletoRaiseMoney()
{
    int n = properties.size();
    for (int i = 0; i < n; i++)
    {
        if (properties[i]->getMortgaged() == false)
        {
            return true;
        }
    }
    return false;
}

void Player::addMoney(int amount)
{
    cash += amount;
} // give player with amount of cash

void Player::addProperty(std::shared_ptr<Building> b)
{
    properties.emplace_back(b);
} // add property to player's property list

void Player::adddebt(string name, int amount)
{
    owe_whom.name = name;
    owe_whom.amount = amount;
}

void Player::improve(string name, bool bs)
{
    int n = properties.size();
    int count = 0;
    for (int i = 0; i < n; i++)
    {
        count++;
        if (properties[i]->getName() == name)
        {
            if (properties[i]->improve(bs, cash))
            {
                if (bs)
                {
                    cash -= properties[i]->getImproveCost();
                    cout << "You've successfully improved your Property" << endl;
                    return;
                }
                else
                {
                    int my = properties[i]->getImproveCost()/2;
                    cash += my;
                    cout << "You've successfully sold your improvement, and recived $" << my << endl; 
                    return;
                }
            }
            else
            {
                cout << "Improve fails" << endl;
                return;
            }
        }
    }
    if (count == n)
    {
        cout << "You don't own this property" << endl;
    }
}

void Player::assets()
{
    cout << "Name: " << name << endl;
    cout << "Cash: " << cash << endl;
    cout << "Roll Up the Rim Cup: " << cup_own << endl;
    cout << "Position: " << pos << endl;
    cout << "Properties: " << endl;
    int n = properties.size();
    for (int i = 0; i < n; i++)
    {
        string m = "mortgaged";
        if (properties[i]->getMortgaged() == false)
        {
            m = "unmortgaged";
        }
        cout << properties[i]->getName() << "  Mortgage status: " << m << "  ";
        int imp = properties[i]->getImproveLevel();
        if ( imp != -1 ) {
            cout << "  Improvement level: " << imp;
        }
        cout << endl;
    }
}

bool Player::if_owe_money()
{
    if (owe_whom.amount > 0)
    {
        return true;
    }
    return false;
}

void Player::sellProperty(std::shared_ptr<Building> b)
{
    int n = properties.size();
    for (int i = 0; i < n; i++)
    {
        if (properties[i]->getName() == b->getName())
        {
            properties.erase(properties.begin() + i);
        }
    }
} // sell property to player's property list

int Player::getPosition()
{
    return pos;
} // get player's position

void Player::setPosition(int n)
{
    pos = n;
}

char Player::getid()
{
    return player_id;
} // get player's id

int Player::getResNum()
{
    string name;
    int ans = 0;
    int n = properties.size();
    for (int i = 0; i < n; i++)
    {
        name = properties[i]->getName();
        if (name == "MKV" || name == "UWP" || name == "V1" || name == "REV")
        {
            ans++;
        }
    }
    return ans;
} // get player resident number

int Player::getGymNum()
{
    string name;
    int ans = 0;
    int n = properties.size();
    for (int i = 0; i < n; i++)
    {
        name = properties[i]->getName();
        if (name == "PAC" || name == "CIF")
        {
            ans++;
        }
    }
    return ans;
} // get player gym number

void Player::move(int num)
{
    pos += num;
    if (pos > 39)
    {
        pos %= 40;
        if (sentToTim == false)
            cash += 200;
    }

} // move player

int Player::get_cup()
{
    return cup_own;
} // get player's rim cup number

void Player::set_cup(int n)
{
    cup_own = n;
} // set player's rim cup number;

bool Player::if_sentToTim()
{
    return sentToTim;
}

void Player::sentToTims(bool s)
{
    sentToTim = s;
}

bool Player::checkifBankruptcy()
{
    if (cash < owe_whom.amount)
    {
        return true;
    }
    return false;
}

int Player::getTimTime()
{
    return Timtime;
}

vector<std::shared_ptr<Building>> &Player::getProperties()
{
    return properties;
}

bool Player::checkMonopoly(string name)
{
    int n = properties.size();
    int ans = 0;
    for (int i = 0; i < n; i++)
    {
        if (properties[i]->getMonopolyBlock() == name)
        {
            ans++;
        }
    }
    if ((ans == 2) && ((name == "Arts1") || (name == "Math")))
    {
        return true;
    }
    else if ((ans == 3) && ((name == "Arts2") || (name == "Eng") ||
                            (name == "Health") || (name == "Env") ||
                            (name == "Sci1") || (name == "Sci2")))
    {
        return true;
    }
    // cout << "You havn't Monoply this block" << endl;
    return false;
}

void Player::setLastRoll(int n)
{
    lastroll = n;
}

int Player::getLastRoll()
{
    return lastroll;
}

int Player::netWorth()
{
    int ans = cash;
    int n = properties.size();
    for (int i = 0; i < n; i++)
    {
        ans += properties[i]->getPurchasePrice();
        ans += properties[i]->getImproveLevel() * properties[i]->getImproveCost();
        // check if need to add mortgage price
    }
    return ans;
}

void Player::setMoney(int n)
{
    cash = n;
}

bool Player::checkProperty(std::string name)
{
    int n = properties.size();
    for (int i = 0; i < n; i++)
    {
        if (properties[i]->getName() == name)
        {
            return true;
        }
    }
    return false;
}

std::shared_ptr<Building> Player::getProperty(std::string name)
{
    int n = properties.size();
    for (int i = 0; i < n; i++)
    {
        if (properties[i]->getName() == name)
        {
            return properties[i];
        }
    }
    return nullptr;
}

void Player::removeProperty(std::string name)
{
    int n = properties.size();
    for (int i = 0; i < n; i++)
    {
        if (properties[i]->getName() == name)
        {
            properties.erase(properties.begin() + i);
            return;
        }
    }
}

void Player::setDCTime(int n)
{
    Timtime = n;
}

void Player::set_cup_active(bool s){
    cup_active = s;
}

bool Player::get_cup_active() {
    return cup_active;
}


