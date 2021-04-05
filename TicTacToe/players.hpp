#ifndef PLAYERS_HPP
#define PLAYERS_HPP

#include <iostream>
#include <vector>

#include "tictactoe.hpp"
#include "strategy.hpp"
#include "game.hpp"

using namespace std;

template <Playble GameType>
class Human
    public:
        Human(double t = 0.0)
            : timeout(t)
        {}	

        typename GameType::move_t getStrategy(const GameType& state) {
            return getIOTile(state);
        }

	double getTimeout() {
            return timeout;
        }

        int getParity() {
            return parity;
        }

        int heuristic(const GameType& state) {
            return 0;
        }
       
    private:
        double timeout;
	int parity;	
};

template <Playable GameType>
class Smart {
    public:
        Smart(double t = 0.0)
            : timeout(t)
        {}	

        typename GameType::move_t getStrategy(const GameType& state) {
              return getMinimaxTile(state);
        }

	double getTimeout() {
            return timeout;
        }
        
        int getParity() {
            return parity;
        }
        
        int heuristic(const GameType& state) {
            return 0;
        }

    private:
        double timeout;
        int parity;
};

#endif
