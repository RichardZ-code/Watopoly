#include "property.h"
#include <iostream>
#include <string>
using namespace std;

Property::Property(string name, int purchase_price) : Building{name,'P'}, purchase_price{purchase_price}, 
                                                            owner{nullptr}, if_Mortgaged{false} {}

void Property::setOwner(std::shared_ptr<Player> owner){
    this->owner = owner;
}

std::shared_ptr<Player> Property::getOwner(){
    return owner;
}

void Property::setMortgaged(bool Mortgage_status){
    if_Mortgaged = Mortgage_status;
}

bool Property::getMortgaged(){
    return if_Mortgaged;
}

int Property::getPurchasePrice(){
    return purchase_price;
}

bool Property::improve(bool bs, int cash){
    return false;
}

int Property::getImproveCost(){
    return -1;
}

int Property::getImproveLevel(){
    return -1;
}

std::string Property::getMonopolyBlock(){
    return "";
}

void Property::setImprovementLevel(int imp) {

}


