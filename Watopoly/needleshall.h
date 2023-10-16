#ifndef NEEDLEHALL_H
#define NEEDLEHALL_H
#include <iostream>
#include <string>
#include "nonproperty.h"
#include "player.h"

class NeedlesHall : public NonProperty
{
    public:
        NeedlesHall(std::string name);
        void action(Player & p);
};

#endif

