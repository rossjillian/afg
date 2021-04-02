#include <iostream>
#include <numeric>
#include <vector>
#include <cassert>

#include "model.hpp"

using namespace std;

struct CoinGame {
    int target;
    int currentSum;
    int turnCount;
    vector<int> coins;
    vector<int> coinsChosen;

    using move_t = int;

    CoinGame(int t, const vector<int>& coins)
        : target(t),
          currentSum(0),
          turnCount(0),
          coins(coins)
    {}

    int getSum() const {
        return accumulate(coinsChosen.begin(), coinsChosen.end(), 0);
    }
    bool isTerminal() {
        return getSum() >= target;
    }

    int getTurnCount() const {
        return turnCount;
    }

    vector<move_t> getAvailableMoves() {
        return coins;
    }

    void makeMove(int coin) {
      coinsChosen.push_back(coin);
      turnCount++;
    }

     bool operator==(const CoinGame& other) const
    {
        return getSum() == other.getSum() && coinsChosen == other.coinsChosen;
    }
};

template<>
struct std::hash<CoinGame> {
    /* https://stackoverflow.com/questions/2590677/how-do-i-combine-hash-values-in-c0x */
    size_t operator() (const CoinGame & cg) const
    {
        size_t seed = 0;
        for (const auto& coin : cg.coinsChosen) {
            seed ^= hash<int>()(coin) + 0x9e3779b9 + (seed<<6) + (seed>>2);
        }

        seed ^= hash<int>()(cg.target) + 0x9e3779b9 + (seed<<6) + (seed>>2);

        for (const auto& coin : cg.coins) {
            seed ^= hash<int>()(coin) + 0x9e3779b9 + (seed<<6) + (seed>>2);
        }

        return seed;
    }
};


void hash_test() {
    cout << "[unittest] Hash Function" << endl;
    CoinGame cg1(100, {1, 5, 10});
    CoinGame cg2(cg1);

    cout << "[1] Same initial state produces different hash.." << endl;
    assert(hash<CoinGame>()(cg1) == hash<CoinGame>()(cg2));

    cout << "[2] Changing state produces different hash.." << endl;
    cg2.makeMove(1);
    assert(hash<CoinGame>()(cg1) != hash<CoinGame>()(cg2));

    cout << "[3] States with same moves have same hash.." << endl;
    cg1.makeMove(1);
    assert(hash<CoinGame>()(cg1) == hash<CoinGame>()(cg2));

    cout << "[4] States with same value but different moves have different hashes.." << endl;
    cg1.makeMove(5);
    cg1.makeMove(5);
    cg2.makeMove(10);
    assert(cg1.getSum() == cg2.getSum());
    assert(hash<CoinGame>()(cg1) != hash<CoinGame>()(cg2));

    cout << "..OK!" << endl;
}

void bfs_test() {
    cout << "[unittest] BFS" << endl;
    CoinGame cg1(100, {1, 5, 10});

    cout << "[1] Only finds matches to predicate.." << endl;
    auto sumTen = [](const CoinGame& cg){return cg.getSum() == 10;};
    auto result1 = Model::bfsFind(cg1, sumTen, 10);
    assert(result1.success);
    assert(result1.matches.size() > 0);
    assert(all_of(result1.matches.begin(), result1.matches.end(), sumTen));

    cout << "[2] Finds shallowest match to predicate.." << endl;
    auto result2 = Model::bfsFind(cg1, sumTen, 1);
    assert(result2.success);
    assert(result2.matches.size() == 1);
    assert(sumTen(result2.matches[0]));

    cout << "[3] Enforces depth limit.." << endl;
    auto result3 = Model::bfsFind(cg1, sumTen, 7);
    assert(result3.success);
    assert(result3.matches.size() > 0);
    assert(all_of(result3.matches.begin(), result3.matches.end(),
                     [](const CoinGame& cg){ return cg.getTurnCount() < 7; }));

    cout << "[4] Doesn't find solution if depth limit too low.." << endl;

    auto sumTwenty = [](const CoinGame& cg){return cg.getSum() == 20;};
    auto result4 = Model::bfsFind(cg1, sumTwenty, 1);
    assert(!result4.success);
    assert(result4.matches.size() == 0);

    cout << "..OK!" << endl;
}

int main() {
    hash_test();
    bfs_test();

    return 0;
}
