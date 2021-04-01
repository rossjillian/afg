#include "players.hpp"
#include "strategy.hpp"

Player::Player(double t)
    : timeout(t)
{}

double Player::getTimeout() const {
    return timeout;
}

int HumanPlayer::getStrategy(const TicTacToe& state) 
{
    return io_tile(state);
}

int StupidPlayer::getStrategy(const TicTacToe& state)
{
    return random_tile(state);
}
