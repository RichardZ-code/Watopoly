#ifndef ACADEMIC_H
#define ACADEMIC_H
#include <iostream>
#include <string>
#include <memory>
#include "property.h"

class Academic : public Property
{
    private:
        int improvement_level;
        int improvement_tuition[6];
        int improvement_cost;
        std::string monopoly_block;
    public:
        Academic(std::string name, std::string monopoly_block, int purchase_price, int improvement_cost,int im0, int im1, int im2, int im3, int im4, int im5);
        void action(Player & p);
        int getTuition();
        std::string getMonopolyBlock() override;
        bool improve(bool bs, int cash) override;
        int getImproveCost() override;
        int getImproveLevel()  override;
        void setImprovementLevel(int imp) override;
};



#endif

