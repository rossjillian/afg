#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

#include "strategy.hpp"
#include "tictactoe.hpp"

using namespace std;

int random_tile(const TicTacToe& state) {
    vector<int> possibleMoves = state.getAvailableMoves();
    auto rng = std::default_random_engine {};
	
    for (std::vector<int>::const_iterator i = possibleMoves.begin(); i != possibleMoves.end(); ++i)
        cout << *i << endl;
	
    std::shuffle(possibleMoves.begin(), possibleMoves.end(), rng);
	
    for (std::vector<int>::const_iterator i = possibleMoves.begin(); i != possibleMoves.end(); ++i)
        cout << *i << endl;
	
    return possibleMoves[0];
}

int io_tile(const TicTacToe& state) {
    vector<int> possibleMoves = state.getAvailableMoves();
    cout << "[ ";
    for (int t : possibleMoves) {
        cout << t << ", ";
    }
    cout << "]" << endl;

    cout << "Tile #: ";
    int tileNo;
    cin >> tileNo;

    return tileNo;
}

int minimax_tile() {
    return 0;
}

