#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "building.h"

struct creditor
{
    std::string name;
    int amount;
};

class Player
{
private:
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
    bool cup_active;

public:
    Player(std::string k, char id); //                      f

    std::string getname();                                   // get player's name            f
    int getCashAmount();                                     // get player's cash amount  f
    creditor getCreditor();                                  // get player's creditor     f
    bool AbletoRaiseMoney();                                 //                              f
    void addMoney(int amount);                               // add player's cash         f
    void adddebt(std::string name, int amount);              //           f
    void improve(std::string name, bool bs);                 //              f
    void assets();                                           // print player's asset                  f
    bool if_owe_money();                                     // check if player owe money       f
    void addProperty(std::shared_ptr<Building> b);           //                        f
    void sellProperty(std::shared_ptr<Building> b);          //                       f
    int getPosition();                                       // get player's position           f
    void setPosition(int n);                                 // set player's position       f
    char getid();                                            // get player's id                 f
    int getResNum();                                         // get player resident number      f
    int getGymNum();                                         // get player gym number
    void move(int num);                                      // move player                     f
    int get_cup();                                           // get player's rim cup number     f
    void set_cup(int n);                                     // set player's rim cup number;    f
    bool if_sentToTim();                                     // check if player is sent to Tim  f
    void sentToTims(bool s);                                 // set player sent to Tim     f
    bool checkifBankruptcy();                                //                             f
    int getTimTime();                                        // get player's time in Tim           f
    std::vector<std::shared_ptr<Building>> &getProperties(); // get player's properties, for auction f
    bool checkMonopoly(std::string name);                    // check if player has monopoly of a property
    void setLastRoll(int n);                                 // set player's last roll
    int getLastRoll();                                       // get player's last roll
    int netWorth();                                          // get player's net worth
    void setMoney(int n);                                    // set player's money for loading game
    bool checkProperty(std::string name);                    // check if player has a property
    std::shared_ptr<Building> getProperty(std::string name); // get a property
    void removeProperty(std::string name);                   // remove a property
    void setDCTime(int n);                                   // set player's DC time
    void set_cup_active(bool s);                             // set cup_active
    bool get_cup_active(); // get player's cup active
};

#endif

