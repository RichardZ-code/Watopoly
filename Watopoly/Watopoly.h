#ifndef WATOPOLY_H
#define WATOPOLY_H
#include <iostream>
#include <string>
#include "player.h"
#include "building.h"
#include "nonproperty.h"
#include "property.h"
#include "academic.h"
#include "residence.h"
#include "gym.h"

#include "goosenesting.h"
#include "dctimsline.h"
#include "slc.h"
#include "osap.h"
#include "tuition.h"
#include "needleshall.h"
#include "coopfee.h"
#include "gototims.h"

#include "dice.h"

struct block
{
    std::vector<char> P1;
    int imp;
    bool mort;
    int bp;
    void p_improve(std::ostream &out);
    void p_mort(std::ostream &out);
    void p_p1(std::ostream &out);
};

class Watopoly
{
private:
    std::vector<std::shared_ptr<Player>> theplayers;
    std::vector<std::shared_ptr<Building>> thebuildings;
    std::shared_ptr<Player> cur_player;
    std::vector<block> ds;
    Dice di;


public:
    // ~Watopoly();
    Watopoly();
    bool load(std::string f);
    void save(std::string f);
    bool finish();
    void init(int n);
    std::vector<std::shared_ptr<Player>> getPlayers() const;             
    std::vector<std::shared_ptr<Building>> getBuildings() const;         
    int playerNum() const;                                               //                         f
    std::shared_ptr<Player> getCurPlayer();
    std::shared_ptr<Player> & get_Cur_Player();                              //                 f
    int roll();                                                          //                                    f
    void playermove(int num,std::shared_ptr<Player> p);                                            //                      f
    void nextplayer(std::shared_ptr<Player>& p);                                                   //                             f
    std::shared_ptr<Building> getproperty(int pos);                      //               f
    bool isproperty(int pos);                                            //                     f
    bool ifpurchaseable(int pos);          //,std::shared_ptr<Player> p                              
    void buybuilding(int pos,std::shared_ptr<Player> p);                                           //                     f
    void improve(std::string b_name, bool b_or_s);                       // f
    bool improvable(std::string name,std::shared_ptr<Player> p);                                 //           f
    void trade(std::string name, std::string give, std::string receive); //
    void mortgagebuilding(std::string name,std::shared_ptr<Player> p);                           //     f
    void unmortgagebuilding(std::string name,std::shared_ptr<Player> p);                         //   f
    void Bankrupt(std::shared_ptr<Player> p);                                                     //                               f
    //bool ifoweMoney();                                                   //                             f
    //bool checkifBankruptcy();                                            //                      f
    void paydebt(std::shared_ptr<Player> p);                                                      //                                f
    void removePlayer(std::shared_ptr<Player> p);                                                 //                           f
    void assets();                                                       //                                 f
    void all();                                                          //                                    f
    void sentToTims(std::shared_ptr<Player> p);                                                   //                             f
    // void changeActiveRim();
    // void get_Rim();
    // void notifyText();//                             f
    void action(int pos);                      //                         f
    void auction(std::shared_ptr<Building> b,std::shared_ptr<Player> p); //                     f
    void print(std::ostream &out);
    bool ultimatebankrupt(std::shared_ptr<Player> p);
    void check_cup_active();
    friend std::ostream &operator<<(std::ostream &out, Watopoly &g);
};

#endif


