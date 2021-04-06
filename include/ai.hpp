#ifndef AI_HPP
#define AI_HPP

#include <vector>
#include <limits>
#include <chrono>
#include "game.hpp"

namespace AI {
    template<Playable GameType, IntelligentPlayer<GameType> P>
    int minimizer(GameType& state, typename GameType::move_t& bestMove, P player, int alpha, int beta, int depth);
	
    template<Playable GameType, IntelligentPlayer<GameType> P>
    int maximizer(GameType& state, typename GameType::move_t& bestMove, P player, int alpha, int beta, int depth) {
	if (state.isTerminal() || depth == 0)
            return player.heuristic(state);

        int val = std::numeric_limits<int>::min();
        vector<typename GameType::move_t> possibleMoves = state.getAvailableMoves();
        for (auto move : possibleMoves) {
            GameType stateCopy = state;
            stateCopy.makeMove(move);
            int newVal = minimizer(stateCopy, bestMove, player, alpha, beta, depth-1);
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
    int minimizer(GameType& state, typename GameType::move_t& bestMove, P player, int alpha, int beta, int depth) {
        if (state.isTerminal() || depth == 0)
            return player.heuristic(state);

        int val = std::numeric_limits<int>::max();
        vector<typename GameType::move_t> possibleMoves = state.getAvailableMoves();
        for (auto move : possibleMoves) {
            GameType stateCopy = state;
            stateCopy.makeMove(move);
            int newVal = maximizer(stateCopy, bestMove, player, alpha, beta, depth-1);
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
    GameType::move_t minimax(const GameType& state, P player, int depth) {
        typename GameType::move_t bestMove;
        int alpha = std::numeric_limits<int>::min(); 
        int beta = std::numeric_limits<int>::max();
        GameType stateCopy = state;
        if (player.getParity() == 1) {
            maximizer(stateCopy, bestMove, player, alpha, beta, depth);
        }
        else {
            minimizer(stateCopy, bestMove, player, alpha, beta, depth);
        }
        return bestMove;
    }

    template<Playable GameType, IntelligentPlayer<GameType> P>
    GameType::move_t minimaxIterative(const GameType& state, P player, int depth, typename GameType::move_t& bestMove) {
        int alpha = std::numeric_limits<int>::min(); 
        int beta = std::numeric_limits<int>::max();
        GameType stateCopy = state;
        if (player.getParity() == 1) {
            maximizer(stateCopy, bestMove, player, alpha, beta, depth);
        }
        else {
            minimizer(stateCopy, bestMove, player, alpha, beta, depth);
        }
        return bestMove;
    }

    template<Playable GameType, IntelligentPlayer<GameType> P>
    GameType::move_t iterativeDeepening(const GameType& state, P player) {
        auto startTime = std::chrono::high_resolution_clock::now();
        typename GameType::move_t bestMove;
        for (int i = 1; ((state.isWinner() == false) || (state.getTurnParity() != player.getParity())); i++) {
            minimaxIterative(state, player, i, bestMove);
            auto finishTime = std::chrono::high_resolution_clock::now();
            std::chrono::duration<float> elapsed = finishTime - startTime;
            if (elapsed.count() > 0.5) 
                break;
        }
        return bestMove;
    }

}

#endif
