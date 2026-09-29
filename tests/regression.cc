#include "Watopoly.h"
#include <cstdio>
#include <functional>
#include <sstream>
#include <stdexcept>
#include <utility>

// Use the real public game API while supplying deterministic console input.
class Input {
    std::istringstream stream;
    std::streambuf *previous;
public:
    explicit Input(const std::string &text) : stream(text), previous(std::cin.rdbuf(stream.rdbuf())) {
        std::cin.clear();
    }
    ~Input() { std::cin.rdbuf(previous); std::cin.clear(); }
};

void require(bool condition, const std::string &message) {
    if (!condition) throw std::runtime_error(message);
}

struct Game {
    Watopoly game;
    std::shared_ptr<Player> first, second;
    Game() {
        Input input("P S\n");
        game.init(2);
        first = game.getPlayers()[0];
        second = game.getPlayers()[1];
    }
    ~Game() {
        // Existing model uses shared references in both directions.
        for (auto &building : game.getBuildings()) building->setOwner(nullptr);
    }
};

Academic school() { return Academic("AL", "Arts1", 40, 50, 2, 10, 30, 90, 160, 250); }

void initial_improvements() {
    auto building = school();
    require(building.getImproveLevel() == 0, "new property must have zero improvements");
}
void exact_cash() {
    auto building = school();
    building.setImprovementLevel(0);
    require(building.improve(true, 50), "exact construction cost must be sufficient");
    require(building.getImproveLevel() == 1, "successful purchase must increment level");
}
void insufficient_cash() {
    auto building = school();
    building.setImprovementLevel(2);
    require(!building.improve(true, 49), "unaffordable purchase must be rejected");
    require(building.getImproveLevel() == 2, "rejected purchase must not sell an improvement");
}
void level_bounds() {
    auto building = school();
    building.setImprovementLevel(5);
    require(!building.improve(true, 500), "cannot build above five");
    require(building.improve(false, 0), "selling does not require cash");
    require(building.getImproveLevel() == 4, "selling removes one improvement");
    building.setImprovementLevel(0);
    require(!building.improve(false, 0), "cannot sell below zero");
    building.setImprovementLevel(6);
    require(building.getImproveLevel() == 0, "invalid loaded level must be rejected");
}
void player_cash() {
    Game fixture;
    fixture.game.buybuilding(1, fixture.first);
    fixture.game.getproperty(1)->setImprovementLevel(0);
    fixture.first->setMoney(50);
    fixture.first->improve("AL", true);
    require(fixture.first->getCashAmount() == 0, "exact-cost purchase must deduct cash");
    require(fixture.game.getproperty(1)->getImproveLevel() == 1, "purchase must build");
    fixture.first->improve("AL", true);
    require(fixture.first->getCashAmount() == 0, "rejected purchase must not deduct cash");
    require(fixture.game.getproperty(1)->getImproveLevel() == 1, "rejection must preserve level");
    fixture.first->improve("AL", false);
    require(fixture.first->getCashAmount() == 25, "sale refunds half construction cost");
}
void money_for_property() {
    Game fixture;
    fixture.game.buybuilding(1, fixture.second);
    const auto buyer_cash = fixture.first->getCashAmount();
    const auto seller_cash = fixture.second->getCashAmount();
    { Input accept("accept\n"); fixture.game.trade("Student", "100", "AL"); }
    require(fixture.game.getproperty(1)->getOwner() == fixture.first, "building owner must change to buyer");
    require(fixture.first->checkProperty("AL") && !fixture.second->checkProperty("AL"), "inventories must agree");
    require(fixture.first->getCashAmount() == buyer_cash - 100, "buyer payment");
    require(fixture.second->getCashAmount() == seller_cash + 100, "seller payment");
}
void property_for_money() {
    Game fixture;
    fixture.game.buybuilding(1, fixture.first);
    { Input accept("accept\n"); fixture.game.trade("Student", "AL", "100"); }
    require(fixture.game.getproperty(1)->getOwner() == fixture.second, "building owner must change to buyer");
    require(!fixture.first->checkProperty("AL") && fixture.second->checkProperty("AL"), "inventories must agree");
}
void property_for_property() {
    Game fixture;
    fixture.game.buybuilding(1, fixture.first);
    fixture.game.buybuilding(3, fixture.second);
    { Input accept("accept\n"); fixture.game.trade("Student", "AL", "ML"); }
    require(fixture.game.getproperty(1)->getOwner() == fixture.second, "AL must belong to Student");
    require(fixture.game.getproperty(3)->getOwner() == fixture.first, "ML must belong to Professor");
    require(fixture.first->checkProperty("ML") && !fixture.first->checkProperty("AL"), "Professor inventory");
    require(fixture.second->checkProperty("AL") && !fixture.second->checkProperty("ML"), "Student inventory");
}
void rejected_trade() {
    Game fixture;
    fixture.game.buybuilding(1, fixture.second);
    auto owner = fixture.game.getproperty(1)->getOwner();
    const auto cash = fixture.first->getCashAmount();
    { Input reject("reject\n"); fixture.game.trade("Student", "100", "AL"); }
    require(fixture.game.getproperty(1)->getOwner() == owner, "rejected trade keeps owner");
    require(fixture.first->getCashAmount() == cash, "rejected trade keeps cash");
}
void roundtrip_trade() {
    Game fixture;
    fixture.game.buybuilding(1, fixture.second);
    fixture.game.getproperty(1)->setImprovementLevel(0);
    { Input accept("accept\n"); fixture.game.trade("Student", "100", "AL"); }
    fixture.game.save(".roundtrip.tmp");
    Watopoly restored;
    require(restored.load(".roundtrip.tmp"), "save must be loadable");
    std::remove(".roundtrip.tmp");
    require(restored.getproperty(1)->getOwner()->getname() == "Professor", "trade ownership must survive save/load");
    require(restored.getPlayers()[0]->checkProperty("AL"), "restored buyer inventory");
    require(!restored.getPlayers()[1]->checkProperty("AL"), "restored seller inventory");
    for (auto &building : restored.getBuildings()) building->setOwner(nullptr);
}
void unowned_unmortgage() {
    Game fixture;
    const auto cash = fixture.first->getCashAmount();
    fixture.game.unmortgagebuilding("AL", fixture.first);
    require(fixture.first->getCashAmount() == cash, "unowned property must not charge cash");
}
void valid_unmortgage() {
    Game fixture;
    fixture.game.buybuilding(1, fixture.first);
    fixture.game.mortgagebuilding("AL", fixture.first);
    const auto cash = fixture.first->getCashAmount();
    fixture.game.unmortgagebuilding("AL", fixture.first);
    require(!fixture.game.getproperty(1)->getMortgaged(), "mortgage cleared");
    require(fixture.first->getCashAmount() == cash - 24, "repayment equals 60 percent of 40");
}

int main(int argc, char **argv) {
    const std::vector<std::pair<std::string, std::function<void()>>> cases = {
        {"initial_improvements", initial_improvements}, {"exact_cash", exact_cash},
        {"insufficient_cash", insufficient_cash}, {"level_bounds", level_bounds},
        {"player_cash", player_cash}, {"money_for_property", money_for_property},
        {"property_for_money", property_for_money}, {"property_for_property", property_for_property},
        {"rejected_trade", rejected_trade}, {"roundtrip_trade", roundtrip_trade},
        {"unowned_unmortgage", unowned_unmortgage}, {"valid_unmortgage", valid_unmortgage}
    };
    int failures = 0, selected = 0;
    for (const auto &test : cases) {
        if (argc > 1 && test.first != argv[1]) continue;
        ++selected;
        std::ostringstream log;
        auto previous = std::cout.rdbuf(log.rdbuf());
        try {
            test.second();
            std::cout.rdbuf(previous);
            std::cout << "PASS " << test.first << '\n';
        } catch (const std::exception &error) {
            std::cout.rdbuf(previous);
            ++failures;
            std::cerr << "FAIL " << test.first << ": " << error.what() << '\n';
        }
    }
    std::cout << selected - failures << "/" << selected << " passed\n";
    return failures || selected == 0 ? 1 : 0;
}
