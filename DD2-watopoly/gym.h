#ifndef GYM_H
#define GYM_H
#include <iostream>
#include <string>
#include "building.h"
#include "player.h"
#include "property.h"

class Gym : public Property
{
    public:
        Gym(std::string name, int purchase_price);
        void action(Player & p);
        bool improve(bool bs, int cash) override;
};


#endif

