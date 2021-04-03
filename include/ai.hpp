#ifndef AI_HPP
#define AI_HPP

#include <vector>
#include "game.hpp"

const int WIN = 1;
const int LOSS = -1;
const int NEUTRAL = 0;

namespace AI {
    template<Playable GameType>
    int min_move(GameType& state, int& best_move);

    template<Playable GameType>
    int max_move(GameType& state, int& best_move) {
        if (state.isWinner())
            return LOSS;
        else if (state.isTerminal())
            return NEUTRAL;

        int val = -100;
        vector<typename GameType::move_t> possibleMoves = state.getAvailableMoves();
        for (typename GameType::move_t move : possibleMoves) {
            state.makeMove(move, 0);
            int new_val = min_move(state, best_move);
            if (new_val > val) {
                val = new_val;
                best_move = move;
            }
           state.retractMove(move, 0);
        }
        return val;
    }

    template<Playable GameType>
    int min_move(GameType& state, int& best_move) {
        if (state.isWinner())
           return WIN;
        else if (state.isTerminal())
           return NEUTRAL;

        int val = 100;
        vector<typename GameType::move_t> possibleMoves = state.getAvailableMoves();
        for (typename GameType::move_t move : possibleMoves) {
            state.makeMove(move, 1);
            int new_val = max_move(state, best_move);
            if (new_val < val) {
                val = new_val;
                best_move = move;
            }
            state.retractMove(move, 1);
        }
        return val;
    }
    
    template<Playable GameType>
    GameType::move_t minimax(const GameType& state, int player) {
        int best_move;
        GameType state_copy = state;
        if (player == 1) {
            max_move(state_copy, best_move);
        }
        else {
            min_move(state_copy, best_move);
        }
        return best_move;
    }

}

#endif
