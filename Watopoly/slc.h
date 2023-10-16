#ifndef SLC_H
#define SLC_H
#include <iostream>
#include <string>
#include "nonproperty.h"
#include "player.h"

class SLC : public NonProperty
{
    public:
        SLC(std::string name);
        void action(Player & p);
};

#endif
