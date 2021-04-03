#include <iostream>
#include <numeric>
#include <vector>
#include <cassert>
#include <functional>
#include <chrono>

#include "model.hpp"

using namespace std;
using namespace chrono;

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


template<Checkable GameType>
Model::SearchResult<GameType> bfsFindFP(GameType initState,
                                        bool(*isGoal)(const GameType&),
                                        int depthLimit) {
    queue<GameType> frontier;
    unordered_set<GameType> visited;

    frontier.push(initState);
    visited.insert(initState);

    Model::SearchResult<GameType> result;
    result.explored = 0;

    while(!frontier.empty()) {
        GameType st = frontier.front();
        frontier.pop();
        result.explored++;

        if (isGoal(st)) {
            result.success = true;
            result.matches.push_back(st);
            continue;
        }

        if (st.isTerminal() || st.getTurnCount() == depthLimit) {
            continue;
        }

        for (const auto& mv : st.getAvailableMoves()) {
            GameType neighbor(st);
            neighbor.makeMove(mv);

            if (visited.find(neighbor) != visited.end()) {
                continue;
            }

            visited.insert(neighbor);
            frontier.push(neighbor);
        }
    }

    result.success = !result.matches.empty();
    return result;
}

bool sum50FP(const CoinGame& cg) {
    return cg.getSum() >= 50;
}

int main(int argc, char **argv) {
    CoinGame cg1(100, {1, 5});

    int depth = atoi(argv[1]);
    auto sum50 = [](const CoinGame& cg){return cg.getSum() >= 50;};
    auto t0 = high_resolution_clock::now();
    auto result1 = Model::bfsFind(cg1, sum50, depth);
    auto t1 = high_resolution_clock::now();

    cout << "Lambda: " << duration_cast<milliseconds>(t1 - t0).count() << endl;

    t0 = high_resolution_clock::now();
    auto result2 = bfsFindFP(cg1, &sum50FP, depth);
    t1 = high_resolution_clock::now();

    cout << "Function pointer: " << duration_cast<milliseconds>(t1 - t0).count() << endl;
    cout << "Nodes explored: " << result1.explored << endl;

    return 0;
}
