#include "Watopoly.h"
#include <cassert>
#include <cstdio>
#include <fstream>
#include <functional>
#include <map>
#include <sstream>
#include <stdexcept>

void require(bool condition) {
    if (!condition) throw std::runtime_error("regression check failed");
}
struct Input {
    std::istringstream input;
    std::streambuf *previous;
    explicit Input(const std::string &text) : input(text), previous(std::cin.rdbuf(input.rdbuf())) { std::cin.clear(); }
    ~Input() { std::cin.rdbuf(previous); std::cin.clear(); }
};
struct Game {
    Watopoly game;
    std::shared_ptr<Player> a, b;
    Game() {
        Input input("G\nS\n");
        game.init(2);
        a = game.getPlayers()[0]; b = game.getPlayers()[1];
    }
    void give(int position, const std::shared_ptr<Player> &player) {
        game.buybuilding(position, player);
    }
    void trade(const std::string &give, const std::string &receive, const std::string &answer = "accept\n") {
        Input input(answer); game.trade(b->getname(), give, receive);
    }
    ~Game() {
        // The original model has shared ownership in both directions.
        for (auto &building : game.getBuildings())
            if (building->getType() == 'P') building->setOwner(nullptr);
    }
};
Academic property() { return Academic("AL", "Arts1", 40, 50, 2, 10, 30, 90, 160, 250); }
int main(int argc, char **argv) {
    const std::map<std::string, std::function<void()>> cases = {
        {"initial_level", [] { auto p = property(); require(p.getImproveLevel() == 0); }},
        {"exact_cash", [] { auto p = property(); p.setImprovementLevel(0); require(p.improve(true, 50)); require(p.getImproveLevel() == 1); }},
        {"insufficient_cash", [] { auto p = property(); p.setImprovementLevel(2); require(!p.improve(true, 49)); require(p.getImproveLevel() == 2); }},
        {"improvement_bounds", [] { auto p = property(); p.setImprovementLevel(5); require(!p.improve(true, 500)); require(p.getImproveLevel() == 5); p.setImprovementLevel(0); require(!p.improve(false, 0)); require(p.getImproveLevel() == 0); }},
        {"sell_improvement", [] { auto p = property(); p.setImprovementLevel(2); require(p.improve(false, 0)); require(p.getImproveLevel() == 1); }},
        {"mortgaged_improvement", [] { auto p = property(); p.setImprovementLevel(0); p.setMortgaged(true); require(!p.improve(true, 500)); require(p.getImproveLevel() == 0); }},
        {"money_for_property", [] { Game f; f.give(1, f.b); int a=f.a->getCashAmount(), b=f.b->getCashAmount(); f.trade("100", "AL"); auto p=f.game.getproperty(1); require(p->getOwner()==f.a); require(f.a->checkProperty("AL") && !f.b->checkProperty("AL")); require(f.a->getCashAmount()==a-100 && f.b->getCashAmount()==b+100); p->action(*f.b); require(f.b->getCreditor().name==f.a->getname()); }},
        {"property_for_money", [] { Game f; f.give(1, f.a); int a=f.a->getCashAmount(), b=f.b->getCashAmount(); f.trade("AL", "100"); require(f.game.getproperty(1)->getOwner()==f.b); require(!f.a->checkProperty("AL") && f.b->checkProperty("AL")); require(f.a->getCashAmount()==a+100 && f.b->getCashAmount()==b-100); }},
        {"property_exchange", [] { Game f; f.give(1,f.a); f.give(3,f.b); f.trade("AL","ML"); require(f.game.getproperty(1)->getOwner()==f.b && f.game.getproperty(3)->getOwner()==f.a); require(f.a->checkProperty("ML") && !f.a->checkProperty("AL")); require(f.b->checkProperty("AL") && !f.b->checkProperty("ML")); }},
        {"rejected_trade", [] { Game f; f.give(1,f.b); int money=f.a->getCashAmount(); f.trade("100","AL","reject\n"); require(f.game.getproperty(1)->getOwner()==f.b); require(f.a->getCashAmount()==money); }},
        {"malformed_money", [] { Game f; f.give(1,f.b); f.trade("100abc","AL"); require(f.game.getproperty(1)->getOwner()==f.b); require(!f.a->checkProperty("AL")); }},
        {"self_trade", [] { Game f; f.give(1,f.a); Input input("accept\n"); f.game.trade(f.a->getname(),"100","AL"); require(f.a->checkProperty("AL")); require(f.a->getProperties().size()==1); }},
        {"unowned_unmortgage", [] { Game f; int money=f.a->getCashAmount(); f.game.unmortgagebuilding("AL",f.a); require(f.a->getCashAmount()==money); }},
        {"unowned_gym", [] { Game f; f.game.getproperty(12)->action(*f.a); require(!f.a->if_owe_money()); }},
        {"unowned_residence", [] { Game f; f.game.getproperty(5)->action(*f.a); require(!f.a->if_owe_money()); }},
        {"mortgaged_rent", [] { Game f; for (int pos : {1,5,12}) { f.give(pos,f.b); auto p=f.game.getproperty(pos); p->setMortgaged(true); p->action(*f.a); require(!f.a->if_owe_money()); } }},
        {"trade_save_load", [] { Game f; f.give(1,f.b); f.trade("100","AL"); f.game.save("roundtrip.sav"); /* Load into a fresh game. */ Watopoly loaded; require(loaded.load("roundtrip.sav")); require(loaded.getproperty(1)->getOwner()->getname()==f.a->getname()); require(loaded.getPlayers()[0]->checkProperty("AL")); for (auto &p: loaded.getBuildings()) if(p->getType()=='P') p->setOwner(nullptr); std::remove("roundtrip.sav"); }},
        {"zero_player_save", [] { std::ofstream("invalid.sav") << "0\n"; Watopoly game; require(!game.load("invalid.sav")); std::remove("invalid.sav"); }}
    };
    if (argc != 2 || cases.count(argv[1]) != 1) return 2;
    try { cases.at(argv[1])(); return 0; }
    catch (const std::exception &error) { std::cerr << error.what() << '\n'; return 1; }
}
