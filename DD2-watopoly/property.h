#ifndef PROPERTY_H
#define PROPERTY_H
#include <iostream>
#include <string>
#include <memory>
#include "building.h"
#include "player.h"

class Property : public Building
{
    protected:
        int purchase_price;
        std::shared_ptr<Player> owner;
        bool if_Mortgaged;
    public:
        Property(std::string name, int purchase_price);
        virtual void action(Player & p) = 0;
        void setOwner(std::shared_ptr<Player> owner) override;
        std::shared_ptr<Player> getOwner() override;
        void setMortgaged(bool if_Mortgaged) override;
        bool getMortgaged() override;
        int getPurchasePrice() override;
        virtual std::string getMonopolyBlock();
        virtual int getImproveCost();
        virtual int getImproveLevel();
        virtual bool improve(bool bs, int cash);
        virtual void setImprovementLevel(int imp);
};

#endif

