#ifndef PLAYERS_HPP
#define PLAYERS_HPP

#include <iostream>
#include <vector>

#include "tictactoe.hpp"
#include "strategy.hpp"
#include "game.hpp"

using namespace std;

template <class Player>
class HumanPlayer {
    public:
        HumanPlayer(double t = 0.0)
            : timeout(t)
        {}	

        int getStrategy(const TicTacToe& state);

	double getTimeout() {
            return timeout;
        }

    private:
        double timeout;
};

template <class Player>
class StupidPlayer {
    public:
        StupidPlayer(double t = 0.0)
            : timeout(t)
        {}	
        
        int getStrategy(const TicTacToe& state);
	
        double getTimeout() {
            return timeout;
        }

    private:
        double timeout;
};

template <class Player>
class SmartPlayer {
    public:
        SmartPlayer(double t = 0.0)
            : timeout(t)
        {}	
        
        int getStrategy(const TicTacToe& state);
        
        double getTimeout() {
            return timeout;
        }

    private:
        double timeout;
};

#endif
