#ifndef RESIDENCE_H
#define RESIDENCE_H
#include <iostream>
#include <string>
#include "building.h"
#include "player.h"
#include "property.h"

class Residence : public Property
{
    public:
        Residence(std::string name, int purchase_price);
        void action(Player & p);
        bool improve(bool bs, int cash) override;
};


#endif

