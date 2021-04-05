#ifndef AI_HPP
#define AI_HPP

#include <vector>
#include "game.hpp"

const int WIN = 1;
const int LOSS = -1;
const int NEUTRAL = 0;

template<class T>
concept Intelligible = Playable<T> && requires(T m, T::move_t mv, Player<T> player) {
    { m.heuristic(player) } -> same_as<int>;
    { m.retractMove(mv, player) } -> same_as<void>;
    { m.isWinner(player) } -> same_as<bool>;
};

namespace AI {
    template<Intelligible GameType>
    int minimizer(GameType& state, int& bestMove, Player<GameType> player);
	
    template<Intelligible GameType>
    int maximizer(GameType& state, int& bestMove, Player<GameType> player) {
        //if (state.isWinner())
        //    return LOSS;
        //else if (state.isTerminal())
        //    return NEUTRAL;
	if (state.isTerminal())
            return state.heuristic(player);

        int val = -100;
        vector<typename GameType::move_t> possibleMoves = state.getAvailableMoves();
        for (typename GameType::move_t move : possibleMoves) {
            state.makeMove(move, 0);
            int newVal = minimizer(state, bestMove, player);
            if (newVal > val) {
                val = newVal;
                bestMove = move;
            }
           state.retractMove(move, 0);
        }
        return val;
    }

    template<Intelligible GameType>
    int minimizer(GameType& state, int& bestMove, Player<GameType> player) {
        //if (state.isWinner())
        //   return WIN;
        //else if (state.isTerminal())
        //   return NEUTRAL;
        if (state.isTerminal())
            return state.heuristic(player);

        int val = 100;
        vector<typename GameType::move_t> possibleMoves = state.getAvailableMoves();
        for (typename GameType::move_t move : possibleMoves) {
            state.makeMove(move, 1);
            int newVal = maximizer(state, bestMove, player);
            if (newVal < val) {
                val = newVal;
                bestMove = move;
            }
            state.retractMove(move, 1);
        }
        return val;
    }
    
    template<Intelligible GameType>
    GameType::move_t minimax(const GameType& state, Player<GameType> player) {
        int bestMove;
        GameType stateCopy = state;
        if (player.getTurnOrder() == 1) {
            maximizer(stateCopy, bestMove, player);
        }
        else {
            minimizer(stateCopy, bestMove, player);
        }
        return bestMove;
    }

}

#endif
