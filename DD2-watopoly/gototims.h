#ifndef GOTOTIMS_H
#define GOTOTIMS_H
#include <iostream>
#include <string>
#include "nonproperty.h"
#include "player.h"

class GoToTims : public NonProperty
{
    public:
        GoToTims(std::string name);
        void action(Player & p);
};

#endif
