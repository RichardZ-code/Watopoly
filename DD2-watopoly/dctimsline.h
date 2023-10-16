#ifndef DCTIMSLINE_H
#define DCTIMSLINE_H
#include <iostream>
#include <string>
#include "nonproperty.h"
#include "player.h"

class DCTL : public NonProperty
{
    public:
        DCTL(std::string name);
        void action(Player & p);
};

#endif

