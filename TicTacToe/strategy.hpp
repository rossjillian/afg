#ifndef STRATEGY_HPP
#define STRATEGY_HPP

#include "tictactoe.hpp"

int random_tile(const TicTacToe& state);

template <class T>
typename T::move_t io_tile(const T& state);

int minimax_tile(const TicTacToe& state, Player<TicTacToe> player);

#endif
