#include "building.h"
using namespace std;

Building::Building(std::string name, char type) : name{name}, type{type} {}

std::string Building::getName() { return name; }


char Building::getType() { 
    return type; 
}

void Building::action(Player&p){}


void Building::setOwner(std::shared_ptr<Player> owner) { cout << endl <<"using Building setOwner" << endl << endl;}

std::shared_ptr<Player> Building::getOwner() {
    return nullptr;
}
void Building::setMortgaged(bool if_Mortgaged) {}
bool Building::getMortgaged() {
    return false;
}

int Building::getPurchasePrice() {
    return -1;
}

int Building::getImproveCost() {
    return -1;
}

int Building::getImproveLevel() {
    return -1;
}

bool Building::improve(bool bs, int cash) {
    return false;
}

std::string Building::getMonopolyBlock() {
    return "";
}

void Building::setImprovementLevel(int imp){

}


