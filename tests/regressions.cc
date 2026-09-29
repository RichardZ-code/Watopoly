#include "Watopoly.h"
#include <algorithm>
#include <functional>
#include <sstream>
#include <stdexcept>
#include <utility>
#include <cstdio>

void require(bool value, const char *message) {
    if (!value) throw std::runtime_error(message);
}

struct Input {
    std::istringstream text;
    std::streambuf *previous;
    explicit Input(const std::string &value) : text(value), previous(std::cin.rdbuf(text.rdbuf())) {
        std::cin.clear();
    }
    ~Input() { std::cin.rdbuf(previous); std::cin.clear(); }
};

struct Game {
    Watopoly game;
    std::shared_ptr<Player> a, b;
    explicit Game(bool initialize = true) {
        if (!initialize) return;
        Input input("G B");
        game.init(2);
        auto players = game.getPlayers();
        a = players[0]; b = players[1];
    }
    ~Game() {
        for (auto building : game.getBuildings()) building->setOwner(nullptr);
        for (auto player : game.getPlayers()) player->getProperties().clear();
    }
    void buy(int position, const std::shared_ptr<Player> &player) {
        game.buybuilding(position, player);
    }
    void trade(const std::string &give, const std::string &receive, const std::string &answer = "accept") {
        Input input(answer);
        game.trade(b->getname(), give, receive);
    }
};

Academic academic() { return Academic("AL", "Arts1", 40, 50, 2, 10, 30, 90, 160, 250); }

int main(int argc, char **argv) {
    using Case = std::pair<const char *, std::function<void()>>;
    const std::vector<Case> cases = {
        {"initial_improvements", [] {
            auto b = academic(); require(b.getImproveLevel() == 0, "new property must start at level zero");
        }},
        {"exact_price", [] {
            auto b = academic(); b.setImprovementLevel(0);
            require(b.improve(true, 50), "exact improvement price must be accepted");
            require(b.getImproveLevel() == 1, "purchase must add one level");
        }},
        {"insufficient_cash", [] {
            auto b = academic(); b.setImprovementLevel(2);
            require(!b.improve(true, 49), "unaffordable purchase must fail, not sell a level");
            require(b.getImproveLevel() == 2, "failed purchase must preserve the level");
        }},
        {"improvement_bounds", [] {
            auto b = academic(); b.setImprovementLevel(0);
            require(!b.improve(false, 0), "cannot sell below zero");
            b.setImprovementLevel(5);
            require(!b.improve(true, 1000), "cannot build above five");
            require(b.improve(false, 0), "valid sale must succeed");
            require(b.getImproveLevel() == 4, "sale must remove one level");
        }},
        {"money_for_property", [] {
            Game f; f.buy(1, f.b);
            int a = f.a->getCashAmount(), b = f.b->getCashAmount();
            f.trade("100", "AL");
            require(f.game.getproperty(1)->getOwner() == f.a, "building owner must change to buyer");
            require(f.a->checkProperty("AL") && !f.b->checkProperty("AL"), "property lists must agree");
            require(f.a->getCashAmount() == a - 100 && f.b->getCashAmount() == b + 100, "cash must transfer once");
        }},
        {"property_for_money", [] {
            Game f; f.buy(1, f.a); f.trade("AL", "100");
            require(f.game.getproperty(1)->getOwner() == f.b, "property-for-money must update owner");
            require(!f.a->checkProperty("AL") && f.b->checkProperty("AL"), "seller must lose property");
        }},
        {"property_swap", [] {
            Game f; f.buy(1, f.a); f.buy(3, f.b); f.trade("AL", "ML");
            require(f.game.getproperty(1)->getOwner() == f.b, "first swapped owner incorrect");
            require(f.game.getproperty(3)->getOwner() == f.a, "second swapped owner incorrect");
            require(f.a->checkProperty("ML") && !f.a->checkProperty("AL"), "first player list incorrect");
            require(f.b->checkProperty("AL") && !f.b->checkProperty("ML"), "second player list incorrect");
        }},
        {"rejected_trade", [] {
            Game f; f.buy(1, f.b); int cash = f.a->getCashAmount();
            f.trade("100", "AL", "reject");
            require(f.game.getproperty(1)->getOwner() == f.b && !f.a->checkProperty("AL"), "rejection must preserve ownership");
            require(f.a->getCashAmount() == cash, "rejection must preserve cash");
        }},
        {"unaffordable_trade", [] {
            Game f; f.buy(1, f.b); f.a->setMoney(50); f.trade("100", "AL");
            require(f.game.getproperty(1)->getOwner() == f.b, "unaffordable trade must not transfer");
            require(f.a->getCashAmount() == 50, "unaffordable trade must not charge");
        }},
        {"rent_after_trade", [] {
            Game f; f.buy(1, f.b); f.trade("100", "AL");
            f.game.getproperty(1)->action(*f.b);
            require(f.b->getCreditor().name == f.a->getname(), "rent must go to the new owner");
            require(f.b->getCreditor().amount == 2, "unimproved single-property rent incorrect");
        }},
        {"save_after_trade", [] {
            Game f; f.buy(1, f.b); f.trade("100", "AL");
            const std::string path = "test-trade-save.txt";
            f.game.save(path);
            Game loaded(false);
            require(loaded.game.load(path), "saved file must load");
            auto owner = loaded.game.getproperty(1)->getOwner();
            require(owner && owner->getname() == f.a->getname(), "save must serialize the new owner");
            std::remove(path.c_str());
        }},
        {"duplicate_add", [] {
            Game f; f.buy(1, f.a); f.a->addProperty(f.game.getproperty(1));
            require(f.a->getProperties().size() == 1, "repeated add must not duplicate a property");
        }}
    };
    int failures = 0, ran = 0;
    for (const auto &test : cases) {
        if (argc > 1 && std::string(argv[1]) != test.first) continue;
        ++ran;
        std::ostringstream captured;
        auto old = std::cout.rdbuf(captured.rdbuf());
        try {
            test.second();
            std::cout.rdbuf(old);
            std::cout << "PASS " << test.first << '\n';
        } catch (const std::exception &error) {
            std::cout.rdbuf(old);
            std::cerr << "FAIL " << test.first << ": " << error.what() << '\n';
            ++failures;
        }
    }
    if (!ran) { std::cerr << "Unknown test\n"; return 2; }
    std::cout << ran << " cases, " << failures << " failures\n";
    return failures ? 1 : 0;
}
