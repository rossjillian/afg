#include <iostream>
#include <vector>

#include "game.hpp"
#include "tictactoe.hpp"
#include "players.hpp"
#include "model.hpp"

using namespace afg::game;
using namespace afg::players;

const int MINIMIZER = -1;
const int MAXIMIZER = 1;
const int NEUTRAL = 0;

template<>
int SmartPlayer<TicTacToe>::heuristic(const TicTacToe& state) {
    if (state.isWinner()) {
	if (this->getParity() == state.getTurnParity())
	    return MAXIMIZER;
	else
	    return MINIMIZER;    
    }
    return NEUTRAL;
}

template<>
int HumanPlayer<TicTacToe>::heuristic(const TicTacToe& state) {
    if (state.isWinner()) {
	if (this->getParity() == state.getTurnParity())
	    return MINIMIZER;
	else
	    return MAXIMIZER;    
    }
    return NEUTRAL;
}

int main(int argc, char **argv)
{
    HumanPlayer<TicTacToe> p1(0);
    SmartPlayer<TicTacToe> p2(1);

    TicTacToe ttt(3);

    TPGame<TicTacToe, HumanPlayer<TicTacToe>, SmartPlayer<TicTacToe>> game(ttt, p1, p2);

    game.play();

    return 0;
}
