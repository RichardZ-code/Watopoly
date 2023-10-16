#ifndef COOPFEE_H
#define COOPFEE_H
#include <iostream>
#include <string>
#include "nonproperty.h"
#include "player.h"

class CoopFee : public NonProperty
{
    public:
        CoopFee(std::string name);
        void action(Player & p);
};


#endif
