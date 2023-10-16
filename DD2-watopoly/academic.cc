#include "academic.h"
#include <iostream>
#include <string>
using namespace std;

Academic::Academic(string name, string monopoly_block, int purchase_price, int improvement_cost, int im0, int im1, int im2, int im3, int im4, int im5) : 
    Property{name, purchase_price}, improvement_cost{improvement_cost}, monopoly_block{monopoly_block} {
    improvement_tuition[0] = im0;
    improvement_tuition[1] = im1;
    improvement_tuition[2] = im2;
    improvement_tuition[3] = im3;
    improvement_tuition[4] = im4;
    improvement_tuition[5] = im5;
}

void Academic::action(Player & p){
    cout << "You arrived at " << this->name << endl;
    if(owner == nullptr){
        cout << "this property doesn't have a owner" << endl;
        return;
    }
    
    if(owner->getname() == p.getname()) {
        cout << "You own this property" << endl;
        return;
    }

    string O_name = getOwner()->getname();
    int tuition = getTuition();
    if(O_name == p.getname()){
        cout << "You own this property" << endl;
    } else {
        cout << "You owe " << O_name << " " << tuition << endl;
        p.adddebt(O_name, tuition);
    }
}

bool Academic::improve(bool bs, int cash){
    if((bs) && (cash > improvement_cost) ){
        if(improvement_level < 5){
            improvement_level++;
            return true;
        }
        else{
            cout << "Improvement level cannot exceed 5" << endl;
            return false;
        }
    } else {
        if(improvement_level > 0){
            improvement_level--;
            return true;
        }
        else{
            cout << "Improvement level cannot be less than 0" << endl;
            return false;
        }
    }
}

int Academic::getImproveLevel(){
    return improvement_level;
}

int Academic::getTuition(){
    if(owner->checkMonopoly(monopoly_block) && improvement_level == 0){
        return improvement_tuition[improvement_level] * 2;
    } else {
        return improvement_tuition[improvement_level];
    }
}

int Academic::getImproveCost(){
    return improvement_cost;
}


string Academic::getMonopolyBlock(){
    return monopoly_block;
}

void Academic::setImprovementLevel(int imp) {
    if( ( imp < 0 ) || (imp > 5)){
        cout << "Invalid Improvement level save" << endl;
        return;
    }
    improvement_level = imp;
}

