#ifndef PLAYERS_HPP
#define PLAYERS_HPP

#include <iostream>
#include <vector>

#include "strategy.hpp"
#include "game.hpp"

using namespace std;
using namespace afg::strategy;

namespace afg {
namespace players {

template <Playable GameType>
class HumanPlayer {
    public:
        HumanPlayer(int i, double t = 0.0)
            : parity(i), timeout(t)
        {}	
       
        typename GameType::move_t getStrategy(const GameType& state) {
            return getIOMove(state);
        }

	    double getTimeout() {
            return timeout;
        }

        int getParity() {
            return parity;
        }
        
        int heuristic(const GameType& state);

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
              return getMinimaxMove(state, *this);
        }

	double getTimeout() {
            return timeout;
        }
        
        int getParity() {
            return parity;
        }

        int heuristic(const GameType& state);

    private:
	int parity;	
        double timeout;
};

} // namespace players
} // namespace afg

#endif
