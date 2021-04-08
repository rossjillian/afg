#ifndef STRATEGY_HPP
#define STRATEGY_HPP

#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

#include "game.hpp"
#include "ai.hpp"

using namespace afg::AI;

const int MAX_DEPTH = 9999;

template <Playable GameType>
typename GameType::move_t getRandomMove(const GameType& state) {
    vector<typename GameType::move_t> possibleMoves = state.getAvailableMoves();
    default_random_engine engine;
    engine.seed(chrono::system_clock::now().time_since_epoch().count());
	
    std::shuffle(possibleMoves.begin(), possibleMoves.end(), engine);
	
    return possibleMoves[0];
}

template <Playable GameType>
typename GameType::move_t getIOMove(const GameType& state) {
    vector<typename GameType::move_t> possibleMoves = state.getAvailableMoves();
    typename GameType::move_t mv;
    std::cin >> mv;

    return mv;
}

template <Playable GameType, IntelligentPlayer<GameType> P>
typename GameType::move_t getMinimaxMove(const GameType& state, P player) {
    return minimax(state, player, MAX_DEPTH);
}

template <Playable GameType, IntelligentPlayer<GameType> P>
typename GameType::move_t getIterativeMove(const GameType& state, P player) {
    return iterativeDeepening(state, player, MAX_DEPTH);
}

#endif
