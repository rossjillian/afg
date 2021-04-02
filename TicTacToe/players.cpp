#include "players.hpp"
#include "strategy.hpp"

template<>
int HumanPlayer<TicTacToe>::getStrategy(const TicTacToe& state) 
{
    return io_tile(state);
}

template<>
int StupidPlayer<TicTacToe>::getStrategy(const TicTacToe& state)
{
    return random_tile(state);
}

template<>
int SmartPlayer<TicTacToe>::getStrategy(const TicTacToe& state)
{
    return minimax_tile(state);
}
