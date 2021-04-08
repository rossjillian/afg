#ifndef PLAYERS_HPP
#define PLAYERS_HPP

#include <iostream>
#include <vector>

#include "amazons.hpp"
#include "strategy.hpp"
#include "game.hpp"

using namespace std;
/*

template <Playable GameType>
class HumanPlayer {
    public: 
        HumanPlayer(int i, double t = 0.0) 
            : parity(i), timemout(t)
        {}

        typename GameType::move_t getStrategy(const GameType& state)
        {
            return getIOTile(state);
        }

        double getTimeout(){
            return timeout;
        }

        int getParity() {
            return parity;
        }

        int heuristic(const GameType& state) {
            if (state.isWinner()) {
                if (this->getParity() == state.getTurnParity())
                    return MINIMIZER;
                else 
                    return MAXIMIZER;
            }
        }
};

*/
#endif