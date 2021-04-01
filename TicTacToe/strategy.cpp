#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

#include "strategy.hpp"
#include "tictactoe.hpp"

using namespace std;

const int WIN = 1;
const int LOSS = -1;
const int NEUTRAL = 0;

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

int minimax_tile(const TicTacToe& state, int player) {
    int best_move;
    TicTacToe state_copy = state;
    if (player == 1) {    
        max(state_copy, best_move);
    }
    else {
        min(state_copy, best_move);
    }

    return best_move;
}

int max(TicTacToe& state, int& best_move) {
    if (state.isWinner())
        return LOSS;
    else if (state.isTerminal())
        return NEUTRAL;
    
    int val = -100;
    vector<int> possibleMoves = state.getAvailableMoves();
    for (int move : possibleMoves) {
        state.makeMove(move, 0);
	int new_val = min(state, best_move);
        if (new_val > val) {
            val = new_val;
            best_move = move;
        }
        state.retractMove(move, 0);
    } 
    return val;
}

int min(TicTacToe& state, int& best_move) {
    if (state.isWinner())
        return WIN;
    else if (state.isTerminal())
        return NEUTRAL;
    
    int val = 100;
    vector<int> possibleMoves = state.getAvailableMoves();
    for (int move : possibleMoves) {
        state.makeMove(move, 1);
        int new_val = max(state, best_move);
        if (new_val < val) {
            val = new_val;
            best_move = move;
        }
        state.retractMove(move, 1);
    }
    return val;
}    
