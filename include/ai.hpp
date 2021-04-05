#ifndef AI_HPP
#define AI_HPP

#include <vector>
#include "game.hpp"

namespace AI {
    template<Playable GameType>
    int minimizer(GameType& state, int& bestMove, Player<GameType> player);
	
    template<Playable GameType>
    int maximizer(GameType& state, int& bestMove, Player<GameType> player) {
	if (state.isTerminal())
            return player.heuristic(state);

        // TODO: change to generic minimum heuristic
        int val = -100;
        vector<typename GameType::move_t> possibleMoves = state.getAvailableMoves();
        for (typename GameType::move_t move : possibleMoves) {
            GameType stateCopy = state;
            stateCopy.makeMove(move, 0);
            int newVal = minimizer(stateCopy, bestMove, player);
            if (newVal > val) {
                val = newVal;
                bestMove = move;
            }
        }
        return val;
    }

    template<Playable GameType>
    int minimizer(GameType& state, int& bestMove, Player<GameType> player) {
        if (state.isTerminal())
            return player.heuristic(state);

        // TODO: change to generic maximum heuristic
        int val = 100;
        vector<typename GameType::move_t> possibleMoves = state.getAvailableMoves();
        for (typename GameType::move_t move : possibleMoves) {
            GameType stateCopy = state;
            stateCopy.makeMove(move, 1);
            int newVal = maximizer(stateCopy, bestMove, player);
            if (newVal < val) {
                val = newVal;
                bestMove = move;
            }
        }
        return val;
    }
    
    template<Playable GameType>
    GameType::move_t minimax(const GameType& state, Player<GameType> player) {
        int bestMove;
        GameType stateCopy = state;
        if (player.getParity() == 1) {
            maximizer(stateCopy, bestMove, player);
        }
        else {
            minimizer(stateCopy, bestMove, player);
        }
        return bestMove;
    }

}

#endif
