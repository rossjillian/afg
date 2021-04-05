#ifndef AI_HPP
#define AI_HPP

#include <vector>
#include "game.hpp"

namespace AI {
    template<Playable GameType, Player<GameType> P>
    int minimizer(GameType& state, int& bestMove, P player);
	
    template<Playable GameType, Player<GameType> P>
    int maximizer(GameType& state, int& bestMove, P player) {
	if (state.isTerminal())
            return player.heuristic(state);

        // TODO: change to generic minimum heuristic
        int val = -100;
        vector<typename GameType::move_t> possibleMoves = state.getAvailableMoves();
        for (typename GameType::move_t move : possibleMoves) {
            GameType stateCopy = state;
            stateCopy.makeMove(move);
            int newVal = minimizer(stateCopy, bestMove, player);
            if (newVal > val) {
                val = newVal;
                bestMove = move;
            }
        }
        return val;
    }

    template<Playable GameType, Player<GameType> P>
    int minimizer(GameType& state, int& bestMove, P player) {
        if (state.isTerminal())
            return player.heuristic(state);

        // TODO: change to generic maximum heuristic
        int val = 100;
        vector<typename GameType::move_t> possibleMoves = state.getAvailableMoves();
        for (typename GameType::move_t move : possibleMoves) {
            GameType stateCopy = state;
            stateCopy.makeMove(move);
            int newVal = maximizer(stateCopy, bestMove, player);
            if (newVal < val) {
                val = newVal;
                bestMove = move;
            }
        }
        return val;
    }
    
    template<Playable GameType, Player<GameType> P>
    GameType::move_t minimax(const GameType& state, P player) {
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
