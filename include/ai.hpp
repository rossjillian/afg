#ifndef AI_HPP
#define AI_HPP

#include <stdexcept>
#include <iostream>
#include <vector>
#include <limits>
#include <chrono>
#include <sys/time.h>

#include "game.hpp"

bool DONE = false;

using namespace afg::game;

namespace afg {
namespace AI {

    template<Playable GameType, IntelligentPlayer<GameType> P>
    int minimizer(GameType& state, typename GameType::move_t& bestMove, P player, int alpha, int beta, int depth);
	
    template<Playable GameType, IntelligentPlayer<GameType> P>
    int maximizer(GameType& state, typename GameType::move_t& bestMove, P player, int alpha, int beta, int depth) {
	if (state.isTerminal() || depth == 0 || DONE) 
            return player.heuristic(state);

        int val = std::numeric_limits<int>::min();
        vector<typename GameType::move_t> possibleMoves = state.getAvailableMoves();
        for (auto move : possibleMoves) {
            GameType stateCopy = state;
            stateCopy.makeMove(move);
            typename GameType::move_t minimizerBestMove;
            int newVal = minimizer(stateCopy, minimizerBestMove, player, alpha, beta, depth-1);
            if (newVal > val) {
                val = newVal;
                bestMove = move;
            }
            alpha = std::max(alpha, val);
            if ((alpha >= beta) || DONE)
                break;
        }
        return val;
    }

    template<Playable GameType, IntelligentPlayer<GameType> P>
    int minimizer(GameType& state, typename GameType::move_t& bestMove, P player, int alpha, int beta, int depth) {
        if (state.isTerminal() || depth == 0 || DONE) 
            return player.heuristic(state);

        int val = std::numeric_limits<int>::max();
        vector<typename GameType::move_t> possibleMoves = state.getAvailableMoves();
        for (auto move : possibleMoves) {
            GameType stateCopy = state;
            stateCopy.makeMove(move);
            typename GameType::move_t maximizerBestMove;
            int newVal = maximizer(stateCopy, maximizerBestMove, player, alpha, beta, depth-1);
            if (newVal < val) {
                val = newVal;
                bestMove = move;
            }
            beta = std::min(beta, val);
            if ((beta <= alpha) || DONE)
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

    void alarmHandler(int sig) { 
        DONE = true;    
    }

    template<Playable GameType, IntelligentPlayer<GameType> P>
    GameType::move_t iterativeDeepening(const GameType& state, P player, int depth, double limit=0.5) {
        struct itimerval it_val;
        signal(SIGALRM, alarmHandler);
        it_val.it_value.tv_sec = 1;
        it_val.it_value.tv_usec = 0;  
        it_val.it_interval = it_val.it_value;        
        setitimer(ITIMER_REAL, &it_val, NULL);
        typename GameType::move_t bestMove;
        DONE = false;
        for (int i = 1; i < depth; i++) {
	    minimaxIterative(state, player, i, bestMove);
            if (DONE) {
                break;
            }
        }
        return bestMove;
    }

} // namespace AI
} // namespace afg

#endif
