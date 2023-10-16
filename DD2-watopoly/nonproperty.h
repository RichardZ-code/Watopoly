#ifndef NONPROPERTY_H
#define NONPROPERTY_H
#include <iostream>
#include <string>
#include "building.h"
#include "player.h"

class NonProperty : public Building
{
    public:
        NonProperty(std::string name);
        virtual void action(Player & p) = 0;
};


#endif

