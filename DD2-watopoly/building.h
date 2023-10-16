#ifndef BUILDING_H
#define BUILDING_H
#include <iostream>
#include <string>
#include <memory>
#include <vector>
class Player;

class Building
{
protected:
    char type;
    std::string name;
public:
    Building(std::string name, char type);
    virtual void action(Player & p);
    std::string getName();
    char getType();

    virtual void setOwner(std::shared_ptr<Player> owner);
    virtual std::shared_ptr<Player> getOwner();
    virtual void setMortgaged(bool if_Mortgaged);
    virtual bool getMortgaged();
    virtual int getPurchasePrice();
    virtual std::string getMonopolyBlock();
    virtual int getImproveCost();
    virtual int getImproveLevel();
    virtual bool improve(bool bs, int cash);
    virtual void setImprovementLevel(int imp); // for saving
};




#endif
