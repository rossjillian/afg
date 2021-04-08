#include <iostream>

#include "game.hpp"

const int MINIMIZER = -1;
const int MAXIMIZER = 1;
const int NEUTRAL = 0;

template <Playable GameType>
class HumanPlayer {
    public:
        HumanPlayer(int i, double t = 0.0)
            : parity(i), timeout(t)
        {}	
       
        typename GameType::move_t getStrategy(const GameType& state) {
            //TODO
            return ;
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
                    return MINIMIZER;
                else
                    return MAXIMIZER;    
            }
            return NEUTRAL;
        }

    private:
	int parity;	
        double timeout;
};
