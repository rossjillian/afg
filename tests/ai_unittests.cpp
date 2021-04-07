#include <cassert>
#include <cmath>
#include <iostream>

#include "ai.hpp"
#include "board.hpp"
#include "tictactoe.hpp"
#include "strategy.hpp"
#include "game.hpp"

using namespace std;

const int GUARANTEED_DEPTH = 10000;
const int MINIMIZER = -1;
const int MAXIMIZER = 1;
const int NEUTRAL = 0;

template <Playable GameType>
class DumbPlayer {
    public:
        DumbPlayer(int i, double t = 0.0)
            : parity(i), timeout(t)
        {}

        typename GameType::move_t getStrategy(const GameType& state) {
            return getRandomTile(state);    
        }

        double getTimeout() {
            return timeout;
        }

        int getParity() {
            return parity;
        }

    private:
        int parity;
        double timeout;
};

template <Playable GameType>
class SmartPlayer {
    public:
        SmartPlayer(int i, double t = 0.0)
            : parity(i), timeout(t)
        {}

        typename GameType::move_t getStrategy(const GameType& state) {
            return AI::minimax(state, *this, GUARANTEED_DEPTH);    
        }

        double getTimeout() {
            return timeout;
        }

        int getParity() {
            return parity;
        }
  
        int heuristic(const GameType& state) {
            if (state.isWinner()) {
                if (this->getParity() == state.getTurnParity())
                    return MAXIMIZER;
                else
                    return MINIMIZER;
            }
            return NEUTRAL;
        }

    private:
        int parity;
        double timeout;
};

template <Playable GameType>
class TimedPlayer {
    public:
        TimedPlayer(int i, double t = 0.0, int d = GUARANTEED_DEPTH)
            : parity(i), timeout(t), depth(d)
        {}

        typename GameType::move_t getStrategy(const GameType& state) {
            return AI::iterativeDeepening(state, *this, depth, timeout);    
        }

        double getTimeout() {
            return timeout;
        }

        int getParity() {
            return parity;
        }
  
        int heuristic(const GameType& state) {
            if (state.isWinner()) {
                if (this->getParity() == state.getTurnParity())
                    return MAXIMIZER;
                else
                    return MINIMIZER;
            }
            return NEUTRAL;
        }

    private:
        int parity;
        double timeout;
        int depth;
};

void minimax_test() {
    cout << "[unittest] Minimax" << endl;
    Config<TicTacToe> config {3};
    SmartPlayer<TicTacToe> p0(0);
    DumbPlayer<TicTacToe> p1(1);
    
    cout << "[1] Minimax provides optimal solution and [2] Minimax does not cast an invalid move" << endl;
    for (int i = 0; i < 1000; i++) {
        TicTacToe state(config);
        while (!state.isTerminal()) {
            int action = (state.getTurnParity()) ? p1.getStrategy(state) : p0.getStrategy(state);
            if (state.getTurnParity() == 0)
                assert(state.isValid(action));
            state.makeMove(action);
            if (state.isWinner())
                assert(state.getTurnParity() == 0);
        }
    }
    cout << "..OK!" << endl;

}

void iterative_test() {
    cout << "[unittest] Iterative Deepening" << endl;
    Config<TicTacToe> config {3};
    TimedPlayer<TicTacToe> p0(0, pow(0.1, 10));
    DumbPlayer<TicTacToe> p1(1);
    cout << "[1] Iterative deepening finds optimal solution if time limit high enough" << endl;    
    
    for (int i = 0; i < 1000; i++) {
        TicTacToe state(config);
        while (!state.isTerminal()) {
            int action = (state.getTurnParity()) ? p1.getStrategy(state) : p0.getStrategy(state);
            if (state.getTurnParity() == 0) {
                assert(state.isValid(action));
            }
            state.makeMove(action);
            if (state.isWinner())
                assert(state.getTurnParity() == 0);
        }
    }

    cout << "..OK!" << endl;
}

int main() {
    minimax_test();
    iterative_test();
    return 0;
}
