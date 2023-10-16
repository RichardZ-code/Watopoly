#ifndef OSAP_H
#define OSAP_H
#include <iostream>
#include <string>
#include "nonproperty.h"
#include "player.h"

class OSAP : public NonProperty
{
    public:
        OSAP(std::string name);
        void action(Player & p);
};


#endif

