#include "Watopoly.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

// Watopoly::~Watopoly(){
//     for (auto building : thebuildings) {
//         delete building;
//     }

//     for (auto player : theplayers) {
//         delete player;
//     }
// }

Watopoly::Watopoly() : cur_player{nullptr}
{
    std::shared_ptr<OSAP> g0 = std::make_shared<OSAP>("COLLECT OSAP");
    std::shared_ptr<Academic> g1 = std::make_shared<Academic>("AL", "Arts1", 40, 50, 2, 10, 30, 90, 160, 250);
    std::shared_ptr<SLC> g2 = std::make_shared<SLC>("SLC");
    std::shared_ptr<Academic> g3 = std::make_shared<Academic>("ML", "Arts1", 60, 50, 4, 20, 60, 180, 320, 450);
    std::shared_ptr<Tuition> g4 = std::make_shared<Tuition>("TUITION");
    std::shared_ptr<Residence> g5 = std::make_shared<Residence>("MKV", 200);
    std::shared_ptr<Academic> g6 = std::make_shared<Academic>("ECH", "Arts2", 100, 50, 6, 30, 90, 270, 400, 550);
    std::shared_ptr<NeedlesHall> g7 = std::make_shared<NeedlesHall>("NEEDLES HALL");
    std::shared_ptr<Academic> g8 = std::make_shared<Academic>("PAS", "Arts2", 100, 50, 6, 30, 90, 270, 400, 550);
    std::shared_ptr<Academic> g9 = std::make_shared<Academic>("HH", "Arts2", 120, 50, 8, 40, 100, 300, 450, 600);
    std::shared_ptr<DCTL> g10 = std::make_shared<DCTL>("DC Tims Line");
    std::shared_ptr<Academic> g11 = std::make_shared<Academic>("RCH", "Eng", 140, 100, 10, 50, 150, 450, 625, 750);
    std::shared_ptr<Gym> g12 = std::make_shared<Gym>("PAC", 150);
    std::shared_ptr<Academic> g13 = std::make_shared<Academic>("DWE", "Eng", 140, 100, 10, 50, 150, 450, 625, 750);
    std::shared_ptr<Academic> g14 = std::make_shared<Academic>("CPH", "Eng", 160, 100, 12, 60, 180, 500, 700, 900);
    std::shared_ptr<Residence> g15 = std::make_shared<Residence>("UWP", 200);
    std::shared_ptr<Academic> g16 = std::make_shared<Academic>("LHI", "Health", 180, 100, 14, 70, 200, 550, 750, 950);
    std::shared_ptr<SLC> g17 = std::make_shared<SLC>("SLC");
    std::shared_ptr<Academic> g18 = std::make_shared<Academic>("BMH", "Health", 180, 100, 14, 70, 200, 550, 750, 950);
    std::shared_ptr<Academic> g19 = std::make_shared<Academic>("OPT", "Health", 200, 100, 16, 80, 220, 600, 800, 1000);
    std::shared_ptr<GooseNesting> g20 = std::make_shared<GooseNesting>("Goose Nesting");
    std::shared_ptr<Academic> g21 = std::make_shared<Academic>("EV1", "Env", 220, 150, 18, 90, 250, 700, 875, 1050);
    std::shared_ptr<NeedlesHall> g22 = std::make_shared<NeedlesHall>("NEEDLES HALL");
    std::shared_ptr<Academic> g23 = std::make_shared<Academic>("EV2", "Env", 220, 150, 18, 90, 250, 700, 875, 1050);
    std::shared_ptr<Academic> g24 = std::make_shared<Academic>("EV3", "Env", 240, 150, 20, 100, 300, 750, 925, 1100);
    std::shared_ptr<Residence> g25 = std::make_shared<Residence>("V1", 200);
    std::shared_ptr<Academic> g26 = std::make_shared<Academic>("PHYS", "Sci1", 260, 150, 22, 110, 330, 800, 975, 1150);
    std::shared_ptr<Academic> g27 = std::make_shared<Academic>("B1", "Sci1", 260, 150, 22, 110, 330, 800, 975, 1150);
    std::shared_ptr<Gym> g28 = std::make_shared<Gym>("CIF", 150);
    std::shared_ptr<Academic> g29 = std::make_shared<Academic>("B2", "Sci1", 280, 150, 24, 120, 360, 850, 1025, 1200);
    std::shared_ptr<GoToTims> g30 = std::make_shared<GoToTims>("Go To Tims");
    std::shared_ptr<Academic> g31 = std::make_shared<Academic>("EIT", "Sci2", 300, 200, 26, 130, 390, 900, 1100, 1275);
    std::shared_ptr<Academic> g32 = std::make_shared<Academic>("ESC", "Sci2", 300, 200, 26, 130, 390, 900, 1100, 1275);
    std::shared_ptr<SLC> g33 = std::make_shared<SLC>("SLC");
    std::shared_ptr<Academic> g34 = std::make_shared<Academic>("C2", "Sci2", 320, 200, 28, 150, 450, 1000, 1200, 1400);
    std::shared_ptr<Residence> g35 = std::make_shared<Residence>("REV", 200);
    std::shared_ptr<NeedlesHall> g36 = std::make_shared<NeedlesHall>("NEEDLES HALL");
    std::shared_ptr<Academic> g37 = std::make_shared<Academic>("MC", "Math", 350, 200, 35, 175, 500, 1100, 1300, 1500);
    std::shared_ptr<CoopFee> g38 = std::make_shared<CoopFee>("COOP FEE");
    std::shared_ptr<Academic> g39 = std::make_shared<Academic>("DC", "Math", 400, 200, 50, 200, 600, 1400, 1700, 2000);

    thebuildings.emplace_back(g0);
    thebuildings.emplace_back(g1);
    thebuildings.emplace_back(g2);
    thebuildings.emplace_back(g3);
    thebuildings.emplace_back(g4);
    thebuildings.emplace_back(g5);
    thebuildings.emplace_back(g6);
    thebuildings.emplace_back(g7);
    thebuildings.emplace_back(g8);
    thebuildings.emplace_back(g9);
    thebuildings.emplace_back(g10);
    thebuildings.emplace_back(g11);
    thebuildings.emplace_back(g12);
    thebuildings.emplace_back(g13);
    thebuildings.emplace_back(g14);
    thebuildings.emplace_back(g15);
    thebuildings.emplace_back(g16);
    thebuildings.emplace_back(g17);
    thebuildings.emplace_back(g18);
    thebuildings.emplace_back(g19);
    thebuildings.emplace_back(g20);
    thebuildings.emplace_back(g21);
    thebuildings.emplace_back(g22);
    thebuildings.emplace_back(g23);
    thebuildings.emplace_back(g24);
    thebuildings.emplace_back(g25);
    thebuildings.emplace_back(g26);
    thebuildings.emplace_back(g27);
    thebuildings.emplace_back(g28);
    thebuildings.emplace_back(g29);
    thebuildings.emplace_back(g30);
    thebuildings.emplace_back(g31);
    thebuildings.emplace_back(g32);
    thebuildings.emplace_back(g33);
    thebuildings.emplace_back(g34);
    thebuildings.emplace_back(g35);
    thebuildings.emplace_back(g36);
    thebuildings.emplace_back(g37);
    thebuildings.emplace_back(g38);
    thebuildings.emplace_back(g39);

    for (int i = 0; i < 40; i++)
    {
        block k;
        k.mort = false;
        k.bp = 0;
        k.imp = 0;
        ds.emplace_back(k);
    }
}

bool Watopoly::load(std::string f)
{
    int total_cup = 0;
    cout << "Start loading..." << endl;
    ifstream file{f};
    if (!file)
    {
        cout << "File not found" << endl;
        return false;
    }
    int n;
    file >> n;
    if ((n < 0) || (n > 7))
    {
        cout << "Invalid Player number " << endl;
        return false;
    }

    for (int i = 0; i < n; ++i)
    {
        string name;
        char c;
        int pos;
        int timcup;
        int money;
        int dc;
        file >> name;

        if (name == "GRT")
        {
            file >> name;
            name = "GRT Bus";
        }
        else if (name == "Tim")
        {
            file >> name >> name;
            name = "Tim Hortons Doughnut";
        }
        else if (name == "Pink")
        {
            file >> name;
            name = "Pink Tie";
        }

        file >> c >> timcup >> money >> pos;
        total_cup += timcup;
        if (total_cup > 4)
        {
            cout << "Total Roll Up the Rim Cup is greater than 4!" << endl;
            return false;
        }
        auto p = std::make_shared<Player>(name, c);
        if (pos == 10)
        {
            file >> dc;
            if (dc == 1)
            {
                int t;
                file >> t;
                p->sentToTims(true);
                p->setDCTime(t);
            }
            else
            {
                p->sentToTims(false);
            }
        }
        else if (pos == 30)
        {
            cout << "You Can't have player in block 30!" << endl;
            return false;
        }
        p->set_cup(timcup);
        p->setPosition(pos);
        p->setMoney(money);
        theplayers.emplace_back(p);
    }
    cur_player = theplayers[0];
    string line;

    while (getline(file, line))
    {
        // cout << line << endl;
        stringstream ss{line};
        string name;
        string owner;
        string imp;
        ss >> name;

        int k = thebuildings.size();
        for (int i = 0; i < k; i++)
        {
            if (thebuildings[i]->getName() == name)
            {
                if (thebuildings[i]->getType() == 'N')
                {
                    cout << "Loading Nonproperty!" << endl;
                    return false;
                }
            }
        }

        if ((name == "V1") || (name == "MKV") || (name == "UWP") || (name == "REV") || (name == "PAC") || (name == "CIF"))
        {
            ss >> owner;
            // cout << name << owner << endl;
            if (owner != "BANK")
            {
                int n = thebuildings.size();
                for (int i = 0; i < n; ++i)
                {
                    if (thebuildings[i]->getName() == name)
                    {
                        int m = theplayers.size();
                        for (int j = 0; j < m; ++j)
                        {
                            if (theplayers[j]->getname() == owner)
                            {
                                thebuildings[i]->setOwner(theplayers[j]);
                                theplayers[j]->addProperty(thebuildings[i]);
                                break;
                            }
                        }
                    }
                }
            }
        }
        else
        {
            ss >> owner >> imp;
            // cout << name << owner << imp << endl;
            if (owner != "BANK")
            {
                int n = thebuildings.size();
                for (int i = 0; i < n; ++i)
                {
                    if (thebuildings[i]->getName() == name)
                    {
                        int m = theplayers.size();
                        for (int j = 0; j < m; ++j)
                        {
                            if (theplayers[j]->getname() == owner)
                            {
                                thebuildings[i]->setOwner(theplayers[j]);
                                theplayers[j]->addProperty(thebuildings[i]);
                                break;
                            }
                        }
                        if (imp == "-1")
                        {
                            thebuildings[i]->setMortgaged(true);
                        }
                        else
                        {
                            int np = stoi(imp);
                            thebuildings[i]->setImprovementLevel(np);
                        }
                    }
                }
            }
        }
    }
    return true;
}

void Watopoly::save(std::string f)
{
    ofstream file{f};
    file << theplayers.size() << endl;
    for (int i = 0; i < theplayers.size(); ++i)
    {
        file << theplayers[i]->getname() << " " << theplayers[i]->getid() << " " << theplayers[i]->get_cup() << " " << theplayers[i]->getCashAmount() << " " << theplayers[i]->getPosition();
        if (theplayers[i]->getPosition() == 10)
        {
            if (theplayers[i]->if_sentToTim())
            {
                file << " 1 " << theplayers[i]->getTimTime();
            }
            else
            {
                file << " 0";
            }
        }
        file << endl;
    }

    for (int i = 0; i < thebuildings.size(); ++i)
    {
        if (thebuildings[i]->getType() == 'P')
        {
            file << thebuildings[i]->getName() << " ";
            if (thebuildings[i]->getOwner() == nullptr)
            {
                file << "BANK";
            }
            else
            {
                file << thebuildings[i]->getOwner()->getname();
            }
            if (thebuildings[i]->getImproveLevel() != -1)
            {
                if (thebuildings[i]->getMortgaged())
                {
                    file << " " << -1 << endl;
                }
                else
                {
                    file << " " << thebuildings[i]->getImproveLevel() << endl;
                }
            }
            else
            {
                file << endl;
            }
        }
    }
    cout << "You've save the game with file name: " << f << endl;
}

bool Watopoly::finish()
{
    if (theplayers.size() == 1)
    {
        cout << "Winner: " << theplayers[0]->getname() << endl;
        cout << "Game Over" << endl;
        return true;
    }
    else
    {
        return false;
    }
}

void Watopoly::init(int n)
{
    int k = 0;

    cout << " Here are the characters you can choose from: " << endl
         << endl;
    cout << "   G - Goose" << endl;
    cout << "   B - GRT Bus" << endl;
    cout << "   D - Tim Hortons Doughnut" << endl;
    cout << "   P - Professor" << endl;
    cout << "   S - Student" << endl;
    cout << "   $ - Money" << endl;
    cout << "   L - Laptop" << endl;
    cout << "   T - Pink Tie" << endl
         << endl;

    while (k != n && !cin.eof())
    {
        char id;
        cout << "Please enter the id of player " << k + 1 << endl;
        cin >> id;
        if (id == 'G')
        {
            auto p1 = std::make_shared<Player>("Goose", 'G');
            theplayers.emplace_back(p1);
            k++;
        }
        else if (id == 'B')
        {
            auto p2 = std::make_shared<Player>("GRT Bus", 'B');
            theplayers.emplace_back(p2);
            k++;
        }
        else if (id == 'D')
        {
            auto p3 = std::make_shared<Player>("Tim Hortons Doughnut", 'D');
            theplayers.emplace_back(p3);
            k++;
        }
        else if (id == 'P')
        {
            auto p4 = std::make_shared<Player>("Professor", 'P');
            theplayers.emplace_back(p4);
            k++;
        }
        else if (id == 'S')
        {
            auto p5 = std::make_shared<Player>("Student", 'S');
            theplayers.emplace_back(p5);
            k++;
        }
        else if (id == '$')
        {
            auto p6 = std::make_shared<Player>("Money", '$');
            theplayers.emplace_back(p6);
            k++;
        }
        else if (id == 'L')
        {
            auto p7 = std::make_shared<Player>("Laptop", 'L');
            theplayers.emplace_back(p7);
            k++;
        }
        else if (id == 'T')
        {
            auto p8 = std::make_shared<Player>("Pink Tie", 'T');
            theplayers.emplace_back(p8);
            k++;
        }
        else
        {
            cout << "Invalid character id" << endl;
        }
    }
    if (theplayers[0])
    {
        cur_player = theplayers[0];
    }
}

std::vector<std::shared_ptr<Player>> Watopoly::getPlayers() const
{
    return theplayers;
}

std::vector<std::shared_ptr<Building>> Watopoly::getBuildings() const
{
    return thebuildings;
}

int Watopoly::playerNum() const
{
    return theplayers.size();
}

std::shared_ptr<Player> Watopoly::getCurPlayer()
{
    return cur_player;
}

std::shared_ptr<Player> &Watopoly::get_Cur_Player()
{
    return cur_player;
}

int Watopoly::roll()
{
    int n = di.roll();
    return n;
}

void Watopoly::playermove(int num, std::shared_ptr<Player> p)
{
    p->move(num);
}

void Watopoly::nextplayer(std::shared_ptr<Player> &p)
{
    int n = theplayers.size();
    for (int i = 0; i < n; i++)
    {
        if (theplayers[i]->getname() == p->getname())
        {
            if (i == n - 1)
            {
                p = theplayers[0];
                return;
            }
            else
            {
                p = theplayers[i + 1];
                return;
            }
        }
    }
}

std::shared_ptr<Building> Watopoly::getproperty(int pos)
{
    return thebuildings[pos];
}

bool Watopoly::isproperty(int pos)
{
    if (thebuildings[pos]->getType() == 'P')
    {
        return true;
    }
    return false;
}

bool Watopoly::ifpurchaseable(int pos)
{
    if (thebuildings[pos]->getType() == 'P')
    {
        if (thebuildings[pos]->getOwner() == nullptr ) //&& p->getCashAmount() >= thebuildings[pos]->getPurchasePrice()
        {
            return true;
        }
    }

    return false;
}

void Watopoly::buybuilding(int pos, std::shared_ptr<Player> p)
{
    thebuildings[pos]->setOwner(p);
    p->addMoney(-thebuildings[pos]->getPurchasePrice());
    p->addProperty(thebuildings[pos]);
    string k = thebuildings[pos]->getName();
    cout << endl
         << "You have purchased " << k << " ! " << endl;
}

void Watopoly::improve(string name, bool bs)
{
    cur_player->improve(name, bs);
}

bool Watopoly::improvable(string name, std::shared_ptr<Player> p)
{
    int n = thebuildings.size();
    for (int i = 0; i < n; i++)
    {
        if (thebuildings[i]->getName() == name)
        {
            if (thebuildings[i]->getType() == 'P')
            {
                string mb = thebuildings[i]->getMonopolyBlock();
                // cout << mb << endl;
                if (p->checkMonopoly(mb))
                {
                    return true;
                }
                else
                {
                    cout << "You don't have this monopoly yet" << endl;
                    return false;
                }
            }
        }
    }
    return false;
}

void Watopoly::trade(string name, string give, string receive)
{
    char g;
    char r;
    int gm;
    int rm;

    if ('0' <= give[0] && give[0] <= '9')
    {
        stringstream ss{give};
        ss >> gm;
        g = 'M';
    }
    else
    {
        g = 'P';
    }

    if ('0' <= receive[0] && receive[0] <= '9')
    {
        stringstream ss{receive};
        ss >> rm;
        r = 'M';
    }
    else
    {
        r = 'P';
    }

    if ((g == 'M') && (r == 'M'))
    {
        cout << "You can't trade money for money" << endl;
        return;
    }

    int n = theplayers.size();

    if ((g == 'M') && (r == 'P'))
    {
        for (int i = 0; i < n; i++)
        {
            if (theplayers[i]->getname() == name)
            {
                if (theplayers[i]->checkProperty(receive))
                {
                    if (cur_player->getCashAmount() >= gm)
                    {
                        cout << "Player " << name << " do you accept this trade? Please enter 'accept' or 'reject' " << endl;
                        string s;
                        cin >> s;
                        if (s == "reject")
                        {
                            cout << "Player " << name << " has rejected this trade" << endl;
                            return;
                        }
                        else if (s == "accept")
                        {
                            cur_player->addMoney(-gm);
                            theplayers[i]->addMoney(gm);
                            cur_player->addProperty(theplayers[i]->getProperty(receive));
                            theplayers[i]->removeProperty(receive);
                            cout << "You have traded $" << gm << " for " << receive << " with " << name << endl;
                            return;
                        }
                        else
                        {
                            cout << "Invalid input" << endl;
                            return;
                        }
                    }
                    else
                    {
                        cout << "You don't have enough money to trade" << endl;
                        return;
                    }
                }
                else
                {
                    cout << "This player doesn't have this property" << endl;
                    return;
                }
            }
        }
    }
    else if ((g == 'P') && (r == 'M'))
    {
        for (int i = 0; i < n; i++)
        {
            if (theplayers[i]->getname() == name)
            {
                if (cur_player->checkProperty(give))
                {
                    if (theplayers[i]->getCashAmount() >= rm)
                    {
                        cout << "Player " << name << " do you accept this trade? Please enter 'accept' or 'reject' " << endl;
                        string s;
                        cin >> s;
                        if (s == "reject")
                        {
                            cout << "Player " << name << " has rejected this trade" << endl;
                            return;
                        }
                        else if (s == "accept")
                        {
                            cur_player->addMoney(rm);
                            theplayers[i]->addMoney(-rm);
                            theplayers[i]->addProperty(cur_player->getProperty(give));
                            cur_player->removeProperty(give);
                            cout << "You have traded " << give << " for $" << rm << " with " << name << endl;
                            return;
                        }
                        else
                        {
                            cout << "Invalid input" << endl;
                            return;
                        }
                    }
                    else
                    {
                        cout << "This player doesn't have enough money to trade" << endl;
                        return;
                    }
                }
                else
                {
                    cout << "You don't have this property" << endl;
                    return;
                }
            }
        }
    }
    else if ((g == 'P') && (r == 'P'))
    {
        for (int i = 0; i < n; i++)
        {
            if (theplayers[i]->getname() == name)
            {
                if (cur_player->checkProperty(give))
                {
                    if (theplayers[i]->checkProperty(receive))
                    {
                        cout << "Player " << name << " do you accept this trade? Please enter 'accept' or 'reject' " << endl;
                        string s;
                        cin >> s;
                        if (s == "reject")
                        {
                            cout << "Player " << name << " has rejected this trade" << endl;
                            return;
                        }
                        else if (s == "accept")
                        {
                            cur_player->addProperty(theplayers[i]->getProperty(receive));
                            theplayers[i]->addProperty(cur_player->getProperty(give));
                            cur_player->removeProperty(give);
                            theplayers[i]->removeProperty(receive);
                            cout << "You have traded " << give << " for " << receive << " with " << name << endl;
                            return;
                        }
                        else
                        {
                            cout << "Invalid input" << endl;
                            return;
                        }
                    }
                    else
                    {
                        cout << "This player doesn't have this property" << endl;
                        return;
                    }
                }
                else
                {
                    cout << "You don't have this property" << endl;
                    return;
                }
            }
        }
    }
}

void Watopoly::mortgagebuilding(string name, std::shared_ptr<Player> p)
{
    int n = thebuildings.size();
    for (int i = 0; i < n; i++)
    {
        if (thebuildings[i]->getName() == name)
        {
            if (thebuildings[i]->getOwner())
            {
                string owner = thebuildings[i]->getOwner()->getname();
                if (owner == p->getname())
                {
                    if (thebuildings[i]->getMortgaged() == false)
                    {
                        thebuildings[i]->setMortgaged(true);
                        p->addMoney(thebuildings[i]->getPurchasePrice() / 2);
                        cout << "You have mortgaged " << name << " and received $" << thebuildings[i]->getPurchasePrice() / 2 << " from the Bank" << endl;
                        return;
                    }
                    else
                    {
                        cout << "This building is already mortgaged" << endl;
                        return;
                    }
                }
                else
                {
                    cout << "You are not the owner of this building" << endl;
                    return;
                }
            }
            else
            {
                cout << "This building is not purchased yet" << endl;
                return;
            }
        }
    }
    cout << "There is no building with this name" << endl;
}

void Watopoly::unmortgagebuilding(string name, std::shared_ptr<Player> p)
{
    int n = thebuildings.size();
    for (int i = 0; i < n; i++)
    {
        if (thebuildings[i]->getName() == name)
        {
            string owner = thebuildings[i]->getOwner()->getname();
            if (owner == p->getname())
            {
                if (thebuildings[i]->getMortgaged() == true)
                {
                   if (p->getCashAmount() >= thebuildings[i]->getPurchasePrice() * 0.6)
                    {
                    thebuildings[i]->setMortgaged(false);
                    p->addMoney(-(thebuildings[i]->getPurchasePrice() * 0.6));
                    cout << "You have unmortgaged " << name << " and paid $" << thebuildings[i]->getPurchasePrice() * 0.6 << " to the Bank" << endl;
                    return;
                    }
                    else
                    {
                        cout << "You don't have enough money to unmortgage this building" << endl;
                        return;
                    }
                }
                else
                {
                    cout << "This building is not mortgaged" << endl;
                    return;
                }
            }
            else
            {
                cout << "You are not the owner of this building" << endl;
                return;
            }
        }
    }
    cout << "There is no building with this name" << endl;
}

void Watopoly::Bankrupt(std::shared_ptr<Player> p)
{
    creditor cur_creditor = p->getCreditor();
    int n = theplayers.size();
    vector<std::shared_ptr<Building>> cur_properties = p->getProperties();
    if (cur_creditor.name != "Bank")
    {
        for (int i = 0; i < n; i++)
        {
            if (theplayers[i]->getname() == cur_creditor.name)
            {

                int m = cur_properties.size();
                if (m != 0)
                {
                    for (int j = 0; j < m; j++)
                    {
                        if (cur_properties[j]->getMortgaged() == false)
                        {
                            theplayers[i]->addProperty(cur_properties[j]);
                            cur_properties[j]->setOwner(theplayers[i]);
                        }
                        else
                        {
                            cout << endl
                                 << "Player " << cur_creditor.name << " has been given " << cur_properties[j]->getName() << " but it is mortgaged" << endl;
                            cout << "Player " << cur_creditor.name << " needs to decide whether to unmortgage it now or later" << endl;
                            cout << "Please enter 'unmortgage' or 'later' " << endl;
                            string s;
                            cin >> s;
                            while (true)
                            {
                                if (s == "unmortgage")
                                {
                                    cout << endl
                                         << "Player " << cur_creditor.name << " has to pay $" << cur_properties[j]->getPurchasePrice() * 0.6 << " to unmortgage " << cur_properties[j]->getName() << endl;
                                    theplayers[i]->adddebt("Bank", cur_properties[j]->getPurchasePrice() * 0.6);
                                    if (ultimatebankrupt(theplayers[i]))
                                    {
                                        cout << "Player " << cur_creditor.name << " has been bankrupted" << endl;
                                        break;
                                    }
                                    else
                                    {
                                        theplayers[i]->addProperty(cur_properties[j]);
                                        cur_properties[j]->setOwner(theplayers[i]);
                                        cur_properties[j]->setMortgaged(false);
                                        break;
                                    }
                                }
                                else if (s == "later")
                                {
                                    cout << "Player " << cur_creditor.name << " has to pay $" << cur_properties[j]->getPurchasePrice() * 0.1 << " to unmortgage " << cur_properties[j]->getName() << " later" << endl;
                                    theplayers[i]->adddebt("Bank", cur_properties[j]->getPurchasePrice() * 0.1);
                                    if (ultimatebankrupt(theplayers[i]))
                                    {
                                        cout << "Player " << cur_creditor.name << " has been bankrupted" << endl;
                                        break;
                                    }
                                    else
                                    {
                                        theplayers[i]->addProperty(cur_properties[j]);
                                        cur_properties[j]->setOwner(theplayers[i]);
                                        cur_properties[j]->setMortgaged(true);
                                        break;
                                    }
                                }
                                else
                                {
                                    cout << "Invalid input" << endl;
                                    return;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    else
    {
        int m = cur_properties.size();
        if (m != 0)
        {
            int k = thebuildings.size();
            for (int j = 0; j < m; j++)
            {
                for (int i = 0; i < k; i++)
                {
                    if (thebuildings[i]->getName() == cur_properties[j]->getName())
                    {
                        thebuildings[i]->setOwner(nullptr);
                        thebuildings[i]->setMortgaged(false);
                        if (thebuildings[i]->getImproveLevel() != -1)
                        {
                            thebuildings[i]->setImprovementLevel(0);
                        }
                        auction(thebuildings[i], p);
                    }
                }
            }
        }
    }
    // for(int i = 0; i < n; i++)
    // {
    //     if(theplayers[i]->getname() == p->getname())
    //     {
    //         theplayers[i]->set_cup(0);
    //     }
    // }
    removePlayer(p);
    // cout << cur_player->getname() << endl;
}

// bool Watopoly::ifoweMoney()
// {
//     if (cur_player->if_owe_money())
//     {
//         return true;
//     }
//     return false;
// }

// bool Watopoly::checkifBankruptcy()
// {
//     if (cur_player->checkifBankruptcy())
//     {
//         return true;
//     }
//     return false;
// }

void Watopoly::paydebt(std::shared_ptr<Player> p)
{
    creditor cur_creditor = p->getCreditor();
    if (cur_creditor.name == "Bank")
    {
        p->addMoney(-cur_creditor.amount);
        p->adddebt("None", 0);
        cout << "You have paid your fees!" << endl;
    }
    else
    {
        int n = theplayers.size();
        for (int i = 0; i < n; i++)
        {
            if (theplayers[i]->getname() == cur_creditor.name)
            {
                theplayers[i]->addMoney(cur_creditor.amount);
                p->addMoney(-cur_creditor.amount);
                p->adddebt("None", 0);
                cout << "You have paid your fees!" << endl;
            }
        }
    }
}

void Watopoly::removePlayer(std::shared_ptr<Player> p)
{
    int n = theplayers.size();
    string pname = p->getname();
    for (int i = 0; i < n; i++)
    {
        string tname = theplayers[i]->getname();
        if (tname == pname)
        {

            nextplayer(p);
            theplayers.erase(theplayers.begin() + i);
            cout << "Player " << tname << " has dropped out of the school" << endl;
            // cout << cur_player->getname() << endl;
            int h = theplayers.size();

            if (h)
            {
                if (i == h)
                {
                    cur_player = theplayers[0];
                    return;
                }
                else
                {
                    // cout << i << endl;
                    // cout << theplayers[i]->getname() << endl;
                    cur_player = theplayers[i];
                    return;
                }
            }
            else
            {
                cur_player = nullptr;
                return;
            }
        }
    }
}

void Watopoly::assets()
{
    cur_player->assets();
}

void Watopoly::all()
{
    int n = theplayers.size();
    cout << "===================" << endl;
    for (int i = 0; i < n; i++)
    {
        theplayers[i]->assets();
        cout << "===================" << endl;
    }
}

void Watopoly::sentToTims(std::shared_ptr<Player> p)
{
    p->setPosition(10); // need to fix this
    p->sentToTims(true);
    p->setDCTime(0);
    thebuildings[10]->action(*p);
}

// void Watopoly::notifyText(){
//     td->notify(*this);
// }

void Watopoly::action(int pos)
{

    int cur_pos = pos;
    thebuildings[cur_pos]->action(*cur_player);
    if (cur_player->getPosition() != cur_pos)
    {
        action(cur_player->getPosition());
    }
}

void Watopoly::auction(std::shared_ptr<Building> b, std::shared_ptr<Player> p)
{
    int highest_bid = 0;
    std::shared_ptr<Player> highest_bidder = nullptr;
    vector<std::shared_ptr<Player>> copy_players = theplayers; // check ctor
    int l = copy_players.size();
    for (int i = 0; i < l; i++)
    {
        if (copy_players[i]->getname() == p->getname())
        {
            copy_players.erase(copy_players.begin() + i);
            break;
        }
    }

    while (copy_players.size() != 0)
    {
        int i = 0;
        while (i < copy_players.size())
        {
            if (highest_bidder)
            {
                if (highest_bidder->getname() == copy_players[i]->getname())
                {
                    i++;
                    continue;
                }
            }
            cout << "Player: " << copy_players[i]->getname() << " do you want to bid? (y/n)" << endl;
            string ans;
            cin >> ans;
            if (ans == "y")
            {
                cout << "Please enter your bid: " << endl;
                int bid;
                cin >> bid;
                bool quit_bid = false;

                while (bid > copy_players[i]->getCashAmount() && !quit_bid)
                {
                    cout << endl
                         << "You only have " << copy_players[i]->getCashAmount() << " dollars, you don't have enough money to bid" << endl;
                    cout << "Please enter 'bid' or 'quit' to decide another bid or quit this bid" << endl
                         << endl;
                    cout << "Please enter your Command: ";
                    string ans2;
                    cin >> ans2;
                    cout << endl;
                    if (ans2 == "bid")
                    {
                        cin >> bid;
                    }
                    else if (ans2 == "quit")
                    {
                        copy_players.erase(copy_players.begin() + i);
                        quit_bid = true;
                    }
                }

                // while (bid < b->getPurchasePrice() && !quit_bid) {
                //     cout << "You can't bid below the original purchase price" << endl;
                //     cout << endl << "Please enter 'bid' or 'quit' to decide another bid or quit this bid" << endl;
                //     string ans2;
                //     cin >> ans2;
                //     if (ans2 == "bid") {
                //         cin >> bid;
                //     } else if (ans2 == "quit") {
                //         copy_players.erase(copy_players.begin() + i);
                //         quit_bid = true;
                //     }
                // }

                if (!quit_bid)
                {
                    if (bid > highest_bid)
                    {
                        highest_bid = bid;
                        cout << "Now highest bid is: " << highest_bid << endl;
                        highest_bidder = copy_players[i];
                        i++;
                    }
                    else
                    {
                        cout << "You offer a bid lower than the highest bid, you are out of the auction" << endl;
                        copy_players.erase(copy_players.begin() + i);
                    }
                }
                else
                {
                    cout << "You have quit bidding" << endl;
                }
            }
            else if (ans == "n")
            {
                cout << "You decided to quit the auction" << endl;
                copy_players.erase(copy_players.begin() + i);
            }
        }

        if (copy_players.size() == 1)
        {
            break;
        }
    }

    if (copy_players.size() == 0)
    {
        cout << "No one wants to bid for this building" << endl;
        return;
    }

    string name = highest_bidder->getname();
    int o = theplayers.size();
    for (int i = 0; i < o; i++)
    {
        if (theplayers[i]->getname() == name)
        {
            theplayers[i]->addMoney(-highest_bid);
            theplayers[i]->addProperty(b);
            b->setOwner(theplayers[i]);
            cout << "Player " << name << " has won the auction and paid $" << highest_bid << " for " << b->getName() << endl;
        }
    }
}

bool Watopoly::ultimatebankrupt(std::shared_ptr<Player> p)
{
    bool next_player = false;
    while (p->if_owe_money() && !next_player)
    {
        if (p->checkifBankruptcy())
        {
            std::cout << "You do not have enough money to pay the debt" << endl;
            std::cout << "Do you want to choose bankruptcy? (y/n)" << endl;
            string answer;
            std::cin >> answer;
            if (answer == "y")
            {
                Bankrupt(p);
                next_player = true;
                // auction actions here
            }
            else if (answer == "n")
            {
                std::cout << "You have chosen not to bankrupt" << endl;
                std::cout << "You need to raise enough money to pay the debt" << endl;
                while (p->checkifBankruptcy() && p->AbletoRaiseMoney())
                {

                    std::cout << "Please enter: sell, mortgage" << endl;
                    std::cout << "Note: 'sell' means selling improvments inside a building" << endl;
                    string cmd;
                    std::cin >> cmd;
                    if (cmd == "sell")
                    {
                        std::cout << "Please enter the building name you want to sell improvements" << endl;
                        string buildingname;
                        std::cin >> buildingname;
                        p->improve(buildingname, false); //
                    }
                    else if (cmd == "mortgage")
                    {
                        std::cout << "Please enter the building name you want to mortgage" << endl;
                        string buildingname;
                        std::cin >> buildingname;
                        mortgagebuilding(buildingname, p);
                    }
                    else
                    {
                        std::cout << "Invalid input" << endl;
                    }
                }

                if (p->checkifBankruptcy())
                {
                    std::cout << "You do not have enough money to pay the debt" << endl;
                    std::cout << "You have to choose bankruptcy" << endl;
                    Bankrupt(p);
                    next_player = true;
                }
                else
                {
                    paydebt(p);
                }
            }
            else
            {
                std::cout << "Invalid input" << endl;
            }
        }
        else
        {
            paydebt(p); // already has enough money
        }
    }
    return next_player;
}

void Watopoly::check_cup_active()
{
    int n = theplayers.size();
    int ans = 0;
    bool ca = true;
    for (int i = 0; i < n; i++)
    {
        ans += theplayers[i]->get_cup();
    }
    if (ans >= 4)
    {
        ca = false;
    }
    for (int i = 0; i < n; i++)
    {
        theplayers[i]->set_cup_active(ca);
    }
}

void block::p_improve(std::ostream &out)
{
    for (int i = 0; i < imp; i++)
    {
        out << "I";
    }
    for (int i = 0; i < 6 - imp; i++)
    {
        out << " ";
    }
}

void block::p_mort(std::ostream &out)
{
    if (mort)
    {
        out << "M";
    }
    else
    {
        out << " ";
    }
}

void block::p_p1(std::ostream &out)
{
    int n = P1.size();
    for (int i = 0; i < n; i++)
    {
        out << P1[i];
    }
    for (int i = 0; i < 7 - n; i++)
    {
        out << " ";
    }
}

void Watopoly::print(std::ostream &out)
{
    for (int i = 0; i < 40; i++)
    {
        ds[i].bp = 0;
        if (ds[i].P1.size() != 0)
        {
            ds[i].P1.clear();
        }
        ds[i].mort = false;
        ds[i].imp = 0;
    }
    int p_num = theplayers.size();
    for (int i = 0; i < p_num; i++)
    {
        ds[theplayers[i]->getPosition()].P1.emplace_back(theplayers[i]->getid());
        ds[theplayers[i]->getPosition()].bp++;
    }

    for (int i = 0; i < 40; i++)
    {
        ds[i].imp = thebuildings[i]->getImproveLevel();
        ds[i].mort = thebuildings[i]->getMortgaged();
    }

    out << "_________________________________________________________________________________________" << std::endl;
    out << "|Goose  |";
    ds[21].p_improve(out);
    ds[21].p_mort(out);
    out << "|NEEDLES|";
    ds[23].p_improve(out);
    ds[23].p_mort(out);
    out << "|";
    ds[24].p_improve(out);
    ds[24].p_mort(out);
    out << "|V1     |";
    ds[26].p_improve(out);
    ds[26].p_mort(out);
    out << "|";
    ds[27].p_improve(out);
    ds[27].p_mort(out);
    out << "|CIF    |";
    ds[29].p_improve(out);
    ds[29].p_mort(out);
    out << "|GO TO  |" << std::endl;
    out << "|Nesting|-------|HALL   |-------|-------|       |-------|-------|       |-------|TIMS   |" << std::endl;
    out << "|       |EV1    |       |EV2    |EV3    |       |PHYS   |B1     |       |B2     |       |" << std::endl;
    out << "|";
    ds[20].p_p1(out);
    out << "|";
    ds[21].p_p1(out);
    out << "|";
    ds[22].p_p1(out);
    out << "|";
    ds[23].p_p1(out);
    out << "|";
    ds[24].p_p1(out);
    out << "|";
    ds[25].p_p1(out);
    out << "|";
    ds[26].p_p1(out);
    out << "|";
    ds[27].p_p1(out);
    out << "|";
    ds[28].p_p1(out);
    out << "|";
    ds[29].p_p1(out);
    out << "|";
    ds[30].p_p1(out);
    out << "|" << std::endl;
    out << "|_______|_______|_______|_______|_______|_______|_______|_______|_______|_______|_______|" << std::endl;
    out << "|";
    ds[19].p_improve(out);
    ds[19].p_mort(out);
    out << "|                                                                       |";
    ds[31].p_improve(out);
    ds[31].p_mort(out);
    out << "|" << std::endl;
    out << "|-------|                                                                       |-------|" << std::endl;
    out << "|OPT    |                                                                       |EIT    |" << std::endl;
    out << "|";
    ds[19].p_p1(out);
    out << "|                                                                       |";
    ds[31].p_p1(out);
    out << "|" << std::endl;
    out << "|_______|                                                                       |_______|" << std::endl;
    out << "|";
    ds[18].p_improve(out);
    ds[18].p_mort(out);
    out << "|                                                                       |";
    ds[32].p_improve(out);
    ds[31].p_mort(out);
    out << "|" << std::endl;
    out << "|-------|                                                                       |-------|" << std::endl;
    out << "|BMH    |                                                                       |ESC    |" << std::endl;
    out << "|";
    ds[18].p_p1(out);
    out << "|                                                                       |";
    ds[32].p_p1(out);
    out << "|" << std::endl;
    out << "|_______|                                                                       |_______|" << std::endl;
    out << "|SLC    |                                                                       |SLC    |" << std::endl;
    out << "|       |                                                                       |       |" << std::endl;
    out << "|";
    ds[17].p_p1(out);
    out << "|                                                                       |";
    ds[33].p_p1(out);
    out << "|" << std::endl;
    out << "|       |                                                                       |       |" << std::endl;
    out << "|_______|                                                                       |_______|" << std::endl;
    out << "|";
    ds[16].p_improve(out);
    ds[16].p_mort(out);
    out << "|                                                                       |";
    ds[34].p_improve(out);
    ds[34].p_mort(out);
    out << "|" << std::endl;
    out << "|-------|                                                                       |-------|" << std::endl;
    out << "|LHI    |                                                                       |C2     |" << std::endl;
    out << "|";
    ds[16].p_p1(out);
    out << "|           _______________________________________________             |";
    ds[34].p_p1(out);
    out << "|" << std::endl;
    out << "|_______|           |                                             |             |_______|" << std::endl;
    out << "|UWP    |           | #   #  ##  #####  ###  ###   ###  #   #   # |             |REV    |" << std::endl;
    out << "|       |           | #   # #  #   #   #   # #  # #   # #   #   # |             |       |" << std::endl;
    out << "|";
    ds[15].p_p1(out);
    out << "|           | # # # ####   #   #   # ###  #   # #    # #  |             |";
    ds[35].p_p1(out);
    out << "|" << std::endl;
    out << "|       |           | # # # #  #   #   #   # #    #   # #     #   |             |       |" << std::endl;
    out << "|_______|           | ##### #  #   #    ###  #     ###  ## #  #   |             |_______|" << std::endl;
    out << "|";
    ds[14].p_improve(out);
    ds[14].p_mort(out);
    out << "|           |_____________________________________________|             |NEEDLES|" << std::endl;
    out << "|-------|                                                                       |HALL   |" << std::endl;
    out << "|CPH    |                                                                       |       |" << std::endl;
    out << "|";
    ds[14].p_p1(out);
    out << "|                                                                       |";
    ds[36].p_p1(out);
    out << "|" << std::endl;
    out << "|_______|                                                                       |_______|" << std::endl;
    out << "|";
    ds[13].p_improve(out);
    ds[13].p_mort(out);
    out << "|                                                                       |";
    ds[37].p_improve(out);
    ds[37].p_mort(out);
    out << "|" << std::endl;
    out << "|-------|                                                                       |-------|" << std::endl;
    out << "|DWE    |                                                                       |MC     |" << std::endl;
    out << "|";
    ds[13].p_p1(out);
    out << "|                                                                       |";
    ds[37].p_p1(out);
    out << "|" << std::endl;
    out << "|_______|                                                                       |_______|" << std::endl;
    out << "|PAC    |                                                                       |COOP   |" << std::endl;
    out << "|       |                                                                       |FEE    |" << std::endl;
    out << "|";
    ds[12].p_p1(out);
    out << "|                                                                       |";
    ds[38].p_p1(out);
    out << "|" << std::endl;
    out << "|       |                                                                       |       |" << std::endl;
    out << "|_______|                                                                       |_______|" << std::endl;
    out << "|";
    ds[11].p_improve(out);
    ds[11].p_mort(out);
    out << "|                                                                       |";
    ds[39].p_improve(out);
    ds[39].p_mort(out);
    out << "|" << std::endl;
    out << "|-------|                                                                       |-------|" << std::endl;
    out << "|RCH    |                                                                       |DC     |" << std::endl;
    out << "|";
    ds[11].p_p1(out);
    out << "|                                                                       |";
    ds[39].p_p1(out);
    out << "|" << std::endl;
    out << "|_______|_______________________________________________________________________|_______|" << std::endl;
    out << "|DC Tims|";
    ds[9].p_improve(out);
    ds[9].p_mort(out);
    out << "|";
    ds[8].p_improve(out);
    ds[8].p_mort(out);
    out << "|NEEDLES|";
    ds[6].p_improve(out);
    ds[6].p_mort(out);
    out << "|MKV    |TUITION|";
    ds[3].p_improve(out);
    ds[3].p_mort(out);
    out << "|SLC    |";
    ds[1].p_improve(out);
    ds[1].p_mort(out);
    out << "|COLLECT|" << std::endl;
    out << "|Line   |-------|-------|HALL   |-------|       |       |-------|       |-------|OSAP   |" << std::endl;
    out << "|       |HH     |PAS    |       |ECH    |       |       |ML     |       |AL     |       |" << std::endl;
    out << "|";
    ds[10].p_p1(out);
    out << "|";
    ds[9].p_p1(out);
    out << "|";
    ds[8].p_p1(out);
    out << "|";
    ds[7].p_p1(out);
    out << "|";
    ds[6].p_p1(out);
    out << "|";
    ds[5].p_p1(out);
    out << "|";
    ds[4].p_p1(out);
    out << "|";
    ds[3].p_p1(out);
    out << "|";
    ds[2].p_p1(out);
    out << "|";
    ds[1].p_p1(out);
    out << "|";
    ds[0].p_p1(out);
    out << "|" << std::endl;

    out << "|_______|_______|_______|_______|_______|_______|_______|_______|_______|_______|_______|" << std::endl;
}

std::ostream &operator<<(std::ostream &out, Watopoly &g)
{
    g.print(out);
    return out;
}


