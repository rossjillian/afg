#include <iostream>
#include <numeric>
#include <vector>
#include <cassert>
#include <functional>
#include <chrono>

#include "model.hpp"

using namespace std;
using namespace chrono;
using namespace afg::model;

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

struct CGSearchResult {
    bool success;
    int explored;
    vector<CoinGame> matches;
};

CGSearchResult cgBfsFind(CoinGame initState,
                         std::function<bool(const CoinGame&)> isGoal,
                         int depthLimit) {
        queue<CoinGame> frontier;
        unordered_set<CoinGame> visited;

        frontier.push(initState);
        visited.insert(initState);

        CGSearchResult result;
        result.explored = 0;

        while(!frontier.empty()) {
            CoinGame st = frontier.front();
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

            for (int mv : st.getAvailableMoves()) {
                CoinGame neighbor(st);
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


int main(int argc, char **argv) {

     if (argc != 2) {
        cout << "usage: " << argv[0] << " <depth>" << endl;
        exit(1);
    }

    int depth = atoi(argv[1]);
    CoinGame cg1(100, {1, 5});
    auto sum50 = [](const CoinGame& cg){return cg.getSum() >= 50;};
    auto t0 = high_resolution_clock::now();
    auto result1 = bfsFind(cg1, sum50, depth);
    auto t1 = high_resolution_clock::now();

    cout << "Templated: " << duration_cast<milliseconds>(t1 - t0).count() << endl;

    t0 = high_resolution_clock::now();
    auto result2 = cgBfsFind(cg1, sum50, depth);
    t1 = high_resolution_clock::now();

    cout << "Explicit: " << duration_cast<milliseconds>(t1 - t0).count() << endl;
    cout << "Nodes explored: " << result1.explored << endl;

    return 0;
}
