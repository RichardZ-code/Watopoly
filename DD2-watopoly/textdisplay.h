#ifndef TEXTDISPLAY_H
#define TEXTDISPLAY_H
#include <iostream>
#include <vector>
#include "player.h"

struct block {
    std::vector<char> P1;
    std::vector<char> P2;
    int imp;
    bool mort;
    int bp;
    void p_improve(std::ostream & out) const;
    void p_mort(std::ostream & out) const;
    void p_p1(std::ostream & out) const;
};

class TextDisplay{
protected:
    int p_num;
    std::vector<block> ds;

public:
    TextDisplay(std::vector<Player> & p, int n);
    void notify();
    void print(std::ostream &out) const;
    friend std::ostream &operator<<(std::ostream &out, const Watopoly &g);
};



#endif

