#include "textdisplay.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;



void block::p_improve(std::ostream & out) const {
    for(int i=0; i < imp; i++) {
        out << "I";
    }
    for(int i=0; i < 6-imp; i++) {
        out << " ";
    }
}

void block::p_mort(std::ostream & out) const {
    if(mort) {
        out << "M";
    }
    else {
        out << " ";
    }
}

void block::p_p1(std::ostream & out) const {
    for(int i=0; i < P1.size(); i++) {
        out << P1[i];
    }
    for(int i=0; i < 7-P1.size(); i++) {
        out << " ";
    }
}



TextDisplay::TextDisplay(vector<Player> & p, int n) {
    p_num = n;
    
    for(int i=0; i < 40; i++) {
        block k;
        k.mort = false;
        k.bp = 0;
        k.imp = 0;
        ds.emplace_back(k);
    }
    for (int i=0; i<p_num; i++){
            ds[p[i].getPosition()].P1.emplace_back(p[i].getid());
            ds[p[i].getPosition()].bp++;
    }
}


void TextDisplay::notify(Watopoly & game) {
    for(int i=0; i < 40; i++) {
        ds[i].bp = 0;
        ds[i].P1.clear();
        ds[i].P2.clear();
        ds[i].mort = false;
        ds[i].imp = 0;
    }
    
    for (int i=0; i<p_num; i++){
            ds[game.getPlayers()[i].getPosition()].P1.emplace_back(game.getPlayers()[i].getid());
            ds[game.getPlayers()[i].getPosition()].bp++;
    }

    for(int i=0; i < 40; i++) {
        ds[i].imp = game.getBuildings()[i].getImproveLevel();
        ds[i].mort = game.getBuildings()[i].getMortgaged();
    }

}



void TextDisplay::print(std::ostream&out) const {
    out << "_________________________________________________________________________________________" << std::endl;
    out << "|Goose  |";ds[21].p_improve(out);ds[21].p_mort(out);out<<"|NEEDLES|";ds[23].p_improve(out);ds[23].p_mort(out);out<<"|";ds[24].p_improve(out);ds[24].p_mort(out);out<<"|V1     |";ds[26].p_improve(out);ds[26].p_mort(out);out<<"|";ds[27].p_improve(out);ds[27].p_mort(out);out<<"|CIF    |";ds[29].p_improve(out);ds[29].p_mort(out);out<<"|GO TO  |" << std::endl;
    out << "|Nesting|-------|HALL   |-------|-------|       |-------|-------|       |-------|TIMS   |" << std::endl;
    out << "|       |EV1    |       |EV2    |EV3    |       |PHYS   |B1     |       |B2     |       |" << std::endl;
    out << "|";ds[20].p_p1(out);out<<"|";
                ds[21].p_p1(out);out<<"|";
                ds[22].p_p1(out);out<<"|";
                ds[23].p_p1(out);out<<"|";
                ds[24].p_p1(out);out<<"|";
                ds[25].p_p1(out);out<<"|";
                ds[26].p_p1(out);out<<"|";
                ds[27].p_p1(out);out<<"|";
                ds[28].p_p1(out);out<<"|";
                ds[29].p_p1(out);out<<"|";
                ds[30].p_p1(out);out<<"|" << std::endl;
    out << "|_______|_______|_______|_______|_______|_______|_______|_______|_______|_______|_______|" << std::endl;
    out << "|";ds[19].p_improve(out);ds[19].p_mort(out);out<<"|                                                                       |";ds[31].p_improve(out);ds[31].p_mort(out);out<<"|" << std::endl;
    out << "|-------|                                                                       |-------|" << std::endl;
    out << "|OPT    |                                                                       |EIT    |" << std::endl;
    out << "|";ds[19].p_p1(out);out<<"|                                                                       |";ds[31].p_p1(out);out<<"|" << std::endl;
    out << "|_______|                                                                       |_______|" << std::endl;
    out << "|";ds[18].p_improve(out);ds[18].p_mort(out);out<<"|                                                                       |";ds[32].p_improve(out);ds[31].p_mort(out);out<<"|" << std::endl;
    out << "|-------|                                                                       |-------|" << std::endl;
    out << "|BMH    |                                                                       |ESC    |" << std::endl;
    out << "|";ds[18].p_p1(out);out<<"|                                                                       |";ds[32].p_p1(out);out<<"|" << std::endl;
    out << "|_______|                                                                       |_______|" << std::endl;
    out << "|SLC    |                                                                       |SLC    |" << std::endl;
    out << "|       |                                                                       |       |" << std::endl;
    out << "|";ds[17].p_p1(out);out<<"|                                                                       |";ds[33].p_p1(out);out<<"|" << std::endl;
    out << "|       |                                                                       |       |" << std::endl;
    out << "|_______|                                                                       |_______|" << std::endl;
    out << "|";ds[16].p_improve(out);ds[16].p_mort(out);out<<"|                                                                       |";ds[34].p_improve(out);ds[34].p_mort(out);out<<"|" << std::endl;
    out << "|-------|                                                                       |-------|" << std::endl;
    out << "|LHI    |                                                                       |C2     |" << std::endl;
    out << "|";ds[16].p_p1(out);out<<"|           _______________________________________________             |";ds[34].p_p1(out);out<<"|" << std::endl;
    out << "|_______|           |                                             |             |_______|" << std::endl;
    out << "|UWP    |           | #   #  ##  #####  ###  ###   ###  #   #   # |             |REV    |" << std::endl;
    out << "|       |           | #   # #  #   #   #   # #  # #   # #   #   # |             |       |" << std::endl;
    out << "|";ds[15].p_p1(out);out<<"|           | # # # ####   #   #   # ###  #   # #    # #  |             |";ds[35].p_p1(out);out<<"|" << std::endl;
    out << "|       |           | # # # #  #   #   #   # #    #   # #     #   |             |       |" << std::endl;
    out << "|_______|           | ##### #  #   #    ###  #     ###  ## #  #   |             |_______|" << std::endl;
    out << "|";ds[14].p_improve(out);ds[14].p_mort(out);out<<"|           |_____________________________________________|             |NEEDLES|" << std::endl;
    out << "|-------|                                                                       |HALL   |" << std::endl;
    out << "|CPH    |                                                                       |       |" << std::endl;
    out << "|";ds[14].p_p1(out);out<<"|                                                                       |";ds[36].p_p1(out);out<<"|" << std::endl;
    out << "|_______|                                                                       |_______|" << std::endl;
    out << "|";ds[13].p_improve(out);ds[13].p_mort(out);out<<"|                                                                       |";ds[37].p_improve(out);ds[37].p_mort(out);out<<"|" << std::endl;
    out << "|-------|                                                                       |-------|" << std::endl;
    out << "|DWE    |                                                                       |MC     |" << std::endl;
    out << "|";ds[13].p_p1(out);out<<"|                                                                       |";ds[37].p_p1(out);out<<"|" << std::endl;
    out << "|_______|                                                                       |_______|" << std::endl;
    out << "|PAC    |                                                                       |COOP   |" << std::endl;
    out << "|       |                                                                       |FEE    |" << std::endl;
    out << "|";ds[12].p_p1(out);out<<"|                                                                       |";ds[38].p_p1(out);out<<"|" << std::endl;
    out << "|       |                                                                       |       |" << std::endl;
    out << "|_______|                                                                       |_______|" << std::endl;
    out << "|";ds[11].p_improve(out);ds[11].p_mort(out);out<<"|                                                                       |";ds[39].p_improve(out);ds[39].p_mort(out);out<<"|" << std::endl;
    out << "|-------|                                                                       |-------|" << std::endl;
    out << "|RCH    |                                                                       |DC     |" << std::endl;
    out << "|";ds[11].p_p1(out);out<<"|                                                                       |";ds[39].p_p1(out);out<<"|" << std::endl;
    out << "|_______|_______________________________________________________________________|_______|" << std::endl;
    out << "|DC Tims|";ds[9].p_improve(out);ds[9].p_mort(out);out<<"|";ds[8].p_improve(out);ds[8].p_mort(out);out<<"|NEEDLES|";ds[6].p_improve(out);ds[6].p_mort(out);out<<"|MKV    |TUITION|";ds[3].p_improve(out);ds[3].p_mort(out);out<<"|SLC    |";ds[1].p_improve(out);ds[1].p_mort(out);out<<"|COLLECT|" << std::endl;
    out << "|Line   |-------|-------|HALL   |-------|       |       |-------|       |-------|OSAP   |" << std::endl;
    out << "|       |HH     |PAS    |       |ECH    |       |       |ML     |       |AL     |       |" << std::endl;
    out << "|";ds[10].p_p1(out); out<<"|";
                ds[9].p_p1(out); out<<"|"; 
                ds[8].p_p1(out); out<<"|";
                ds[7].p_p1(out); out<<"|";
                ds[6].p_p1(out); out<<"|";
                ds[5].p_p1(out); out<<"|"; 
                ds[4].p_p1(out); out<<"|"; 
                ds[3].p_p1(out); out<<"|";
                ds[2].p_p1(out); out<<"|";
                ds[1].p_p1(out); out<<"|";
                ds[0].p_p1(out); out<<"|" << std::endl;
    
    out << "|_______|_______|_______|_______|_______|_______|_______|_______|_______|_______|_______|" << std::endl;
}

std::ostream &operator<<(std::ostream &out, const TextDisplay &g){
    g.print(out);
    return out;
}

