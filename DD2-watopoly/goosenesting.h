#ifndef GOOSENESTING_H
#define GOOSENESTING_H
#include <iostream>
#include <string>
#include "nonproperty.h"
#include "player.h"

class GooseNesting : public NonProperty
{
    public:
        GooseNesting(std::string name);
        void action(Player & p);
};


#endif

