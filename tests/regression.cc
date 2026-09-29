#include "Watopoly.h"
#include <cstring>
#include <fstream>
#include <functional>
#include <map>
#include <new>
#include <sstream>
#include <stdexcept>

void require(bool condition, const char *message) {
    if (!condition) throw std::runtime_error(message);
}

struct Input {
    std::istringstream input;
    std::streambuf *previous;
    explicit Input(const std::string &text) : input(text), previous(std::cin.rdbuf(input.rdbuf())) { std::cin.clear(); }
    ~Input() { std::cin.rdbuf(previous); std::cin.clear(); }
};

void init(Watopoly &game) {
    Input input("G S\n");
    game.init(2);
    require(game.playerNum() == 2, "two players expected");
}

Academic academic() { return Academic("AL", "Arts1", 40, 50, 2, 10, 30, 90, 160, 250); }

int main(int argc, char **argv) {
    const std::map<std::string, std::function<void()>> tests = {
        {"initial_level", [] {
            // Poison raw storage so the test cannot pass merely because the allocator returned zeroes.
            alignas(Academic) unsigned char storage[sizeof(Academic)];
            std::memset(storage, 0x2a, sizeof storage);
            auto *property = new (storage) Academic("AL", "Arts1", 40, 50, 2, 10, 30, 90, 160, 250);
            const int level = property->getImproveLevel();
            property->~Academic();
            require(level == 0, "new academic property must start at zero improvements");
        }},
        {"exact_cash", [] {
            auto property = academic(); property.setImprovementLevel(0);
            require(property.improve(true, 50), "exact improvement price must be accepted");
            require(property.getImproveLevel() == 1, "purchase must add one improvement");
        }},
        {"insufficient_cash", [] {
            auto property = academic(); property.setImprovementLevel(2);
            require(!property.improve(true, 49), "insufficient cash must not count as a sale");
            require(property.getImproveLevel() == 2, "failed purchase must not change the level");
        }},
        {"improvement_bounds", [] {
            auto property = academic(); property.setImprovementLevel(0);
            require(!property.improve(false, 0), "cannot sell at zero");
            property.setImprovementLevel(5);
            require(!property.improve(true, 1000), "cannot buy above five");
            require(property.improve(false, 0) && property.getImproveLevel() == 4, "sale decreases level");
        }},
        {"cash_for_property", [] {
            Watopoly game; init(game); const auto p = game.getPlayers();
            game.buybuilding(1, p[1]); const int a = p[0]->getCashAmount(), b = p[1]->getCashAmount();
            { Input answer("accept\n"); game.trade(p[1]->getname(), "100", "AL"); }
            require(game.getproperty(1)->getOwner() == p[0], "cash purchase must update building owner");
            require(p[0]->checkProperty("AL") && !p[1]->checkProperty("AL"), "property lists must agree");
            require(p[0]->getCashAmount() == a - 100 && p[1]->getCashAmount() == b + 100, "cash must transfer once");
            game.getproperty(1)->action(*p[1]);
            require(p[1]->getCreditor().name == p[0]->getname(), "rent must go to new owner");
        }},
        {"property_for_cash", [] {
            Watopoly game; init(game); const auto p = game.getPlayers(); game.buybuilding(1, p[0]);
            { Input answer("accept\n"); game.trade(p[1]->getname(), "AL", "100"); }
            require(game.getproperty(1)->getOwner() == p[1], "sale must update building owner");
            require(p[1]->checkProperty("AL") && !p[0]->checkProperty("AL"), "sale lists must agree");
        }},
        {"property_for_property", [] {
            Watopoly game; init(game); const auto p = game.getPlayers();
            game.buybuilding(1, p[0]); game.buybuilding(3, p[1]);
            { Input answer("accept\n"); game.trade(p[1]->getname(), "AL", "ML"); }
            require(game.getproperty(1)->getOwner() == p[1] && game.getproperty(3)->getOwner() == p[0], "both owners must swap");
            require(p[0]->checkProperty("ML") && !p[0]->checkProperty("AL"), "first list must swap");
            require(p[1]->checkProperty("AL") && !p[1]->checkProperty("ML"), "second list must swap");
        }},
        {"rejected_trade", [] {
            Watopoly game; init(game); const auto p = game.getPlayers(); game.buybuilding(1, p[0]);
            const int cash = p[0]->getCashAmount();
            { Input answer("reject\n"); game.trade(p[1]->getname(), "AL", "100"); }
            require(game.getproperty(1)->getOwner() == p[0] && p[0]->getCashAmount() == cash, "rejected trade changes nothing");
        }},
        {"self_trade", [] {
            Watopoly game; init(game); const auto p = game.getPlayers(); game.buybuilding(1, p[0]);
            { Input answer("accept\n"); game.trade(p[0]->getname(), "AL", "AL"); }
            require(p[0]->getProperties().size() == 1 && p[0]->checkProperty("AL"), "self trade must not corrupt inventory");
        }},
        {"invalid_trade_amount", [] {
            Watopoly game; init(game); const auto p = game.getPlayers(); game.buybuilding(1, p[1]);
            { Input answer("accept\n"); game.trade(p[1]->getname(), "100oops", "AL"); }
            require(game.getproperty(1)->getOwner() == p[1] && !p[0]->checkProperty("AL"), "malformed amount must be rejected");
            { Input answer("accept\n"); game.trade(p[1]->getname(), "9999999999999999999999999", "AL"); }
            require(!p[0]->checkProperty("AL"), "overflow amount must be rejected");
        }},
        {"unowned_gym", [] { auto player = std::make_shared<Player>("test", 'G'); Gym property("PAC", 150); property.action(*player); require(!player->if_owe_money(), "unowned gym cannot charge"); }},
        {"unowned_residence", [] { auto player = std::make_shared<Player>("test", 'G'); Residence property("V1", 200); property.action(*player); require(!player->if_owe_money(), "unowned residence cannot charge"); }},
        {"mortgaged_rent", [] {
            Watopoly game; init(game); const auto p = game.getPlayers();
            for (int position : {1, 5, 12}) {
                game.buybuilding(position, p[0]); game.getproperty(position)->setMortgaged(true);
                game.getproperty(position)->action(*p[1]);
                require(!p[1]->if_owe_money(), "mortgaged property cannot charge rent");
            }
        }},
        {"unowned_unmortgage", [] { Watopoly game; init(game); game.unmortgagebuilding("AL", game.getCurPlayer()); require(!game.getproperty(1)->getMortgaged(), "unowned property unchanged"); }},
        {"backward_wrap", [] { Player player("test", 'G'); player.setPosition(2); player.move(-3); require(player.getPosition() == 39 && player.getCashAmount() == 1500, "backward movement wraps without OSAP award"); }},
        {"net_worth", [] {
            auto player = std::make_shared<Player>("test", 'G'); auto property = std::make_shared<Residence>("V1", 200);
            player->addProperty(property); require(player->netWorth() == 1700, "sentinel values cannot inflate net worth");
        }},
        {"zero_player_save", [] {
            { std::ofstream file("invalid-save.txt"); file << "0\n"; }
            Watopoly game; require(!game.load("invalid-save.txt"), "zero-player save rejected"); std::remove("invalid-save.txt");
        }},
        {"save_load", [] {
            Watopoly game; init(game); auto p = game.getPlayers(); game.buybuilding(1, p[0]);
            { Input answer("accept\n"); game.trade(p[1]->getname(), "AL", "100"); }
            game.save("test-save.txt"); Watopoly restored; require(restored.load("test-save.txt"), "load must succeed");
            require(restored.playerNum() == 2 && restored.getproperty(1)->getOwner()->getname() == "Student", "saved ownership must match trade");
            std::remove("test-save.txt");
        }}
    };
    if (argc != 2 || !tests.count(argv[1])) { for (const auto &entry : tests) std::cout << entry.first << '\n'; return 2; }
    try { tests.at(argv[1])(); std::cout << "PASS " << argv[1] << '\n'; return 0; }
    catch (const std::exception &error) { std::cerr << "FAIL " << argv[1] << ": " << error.what() << '\n'; return 1; }
}
