#ifndef PLAYERS_HPP
#define PLAYERS_HPP

#include <iostream>
#include <vector>

#include "tictactoe.hpp"
#include "strategy.hpp"

using namespace std;

class Player {
    public:
        Player(double t = 0.0);
        int getStrategy(const TicTacToe& state);
        double getTimeout() const;
    private:
        double timeout;
};

class HumanPlayer : public Player {
    public:
        int getStrategy(const TicTacToe& state);
};

class StupidPlayer : public Player {
    public:
        int getStrategy(const TicTacToe& state);
};

class SmartPlayer : public Player {
    public:
        int getStrategy(const TicTacToe& state);
};

#endif
