#ifndef TUITION_H
#define TUITION_H
#include <iostream>
#include <string>
#include "nonproperty.h"
#include "player.h"

class Tuition : public NonProperty
{
    public:
        Tuition(std::string name);
        void action(Player & p);
};

#endif

