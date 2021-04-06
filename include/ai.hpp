#ifndef AI_HPP
#define AI_HPP

#include <vector>
#include <limits>
#include "game.hpp"

namespace AI {
    template<Playable GameType, IntelligentPlayer<GameType> P>
    int minimizer(GameType& state, int& bestMove, P player, int alpha, int beta);
	
    template<Playable GameType, IntelligentPlayer<GameType> P>
    int maximizer(GameType& state, int& bestMove, P player, int alpha, int beta) {
	if (state.isTerminal())
            return player.heuristic(state);

        int val = std::numeric_limits<int>::min();
        vector<typename GameType::move_t> possibleMoves = state.getAvailableMoves();
        for (auto move : possibleMoves) {
            GameType stateCopy = state;
            stateCopy.makeMove(move);
            int newVal = minimizer(stateCopy, bestMove, player, alpha, beta);
            if (newVal > val) {
                val = newVal;
                bestMove = move;
            }
            alpha = std::max(alpha, val);
            if (alpha >= beta)
                break;
        }
        return val;
    }

    template<Playable GameType, IntelligentPlayer<GameType> P>
    int minimizer(GameType& state, int& bestMove, P player, int alpha, int beta) {
        if (state.isTerminal())
            return player.heuristic(state);

        int val = std::numeric_limits<int>::max();
        vector<typename GameType::move_t> possibleMoves = state.getAvailableMoves();
        for (auto move : possibleMoves) {
            GameType stateCopy = state;
            stateCopy.makeMove(move);
            int newVal = maximizer(stateCopy, bestMove, player, alpha, beta);
            if (newVal < val) {
                val = newVal;
                bestMove = move;
            }
            beta = std::min(beta, val);
            if (beta <= alpha)
                break;
        }
        return val;
    }
    
    template<Playable GameType, IntelligentPlayer<GameType> P>
    GameType::move_t minimax(const GameType& state, P player) {
        int bestMove;
        int alpha = std::numeric_limits<int>::min(); 
        int beta = std::numeric_limits<int>::max();
        GameType stateCopy = state;
        if (player.getParity() == 1) {
            maximizer(stateCopy, bestMove, player, alpha, beta);
        }
        else {
            minimizer(stateCopy, bestMove, player, alpha, beta);
        }
        return bestMove;
    }

}

#endif
