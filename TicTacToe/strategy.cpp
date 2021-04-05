#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

#include "strategy.hpp"
#include "tictactoe.hpp"
#include "ai.hpp"

using namespace std;

/*
int random_tile(const TicTacToe& state) {
    vector<int> possibleMoves = state.getAvailableMoves();
    auto rng = std::default_random_engine {};
	
    std::shuffle(possibleMoves.begin(), possibleMoves.end(), rng);
	
    return possibleMoves[0];
}
*/

template <class T>
typename T::move_t io_tile(const T& state) {
    vector<typename T::move_t> possibleMoves = state.getAvailableMoves();
    cout << "[ ";
    for (typename T::move_t t : possibleMoves) {
        cout << t << ", ";
    }
    cout << "]" << endl;

    cout << "Tile #: ";
    int tileNo;
    cin >> tileNo;

    return tileNo;
}

/*
int minimax_tile(const TicTacToe& state, Player<TicTacToe> player) {
    return AI::minimax(state, player);
}
*/

