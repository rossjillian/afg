#ifndef STRATEGY_HPP
#define STRATEGY_HPP

#include "tictactoe.hpp"

int random_tile(const TicTacToe& state);
int io_tile(const TicTacToe& state);
int minimax_tile(const TicTacToe& state, int player = 0);
int max(TicTacToe& state, int& best_move);
int min(TicTacToe& state, int& best_move);

#endif
