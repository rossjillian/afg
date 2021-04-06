#ifndef STRATEGY_HPP
#define STRATEGY_HPP

#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

#include "strategy.hpp"
#include "game.hpp"
#include "ai.hpp"

using namespace std;

template <Playable GameType>
typename GameType::move_t getRandomTile(const GameType& state) {
    vector<typename GameType::move_t> possibleMoves = state.getAvailableMoves();
    auto rng = std::default_random_engine {};
	
    std::shuffle(possibleMoves.begin(), possibleMoves.end(), rng);
	
    return possibleMoves[0];
}

template <Playable GameType>
typename GameType::move_t getIOTile(const GameType& state) {
    vector<typename GameType::move_t> possibleMoves = state.getAvailableMoves();
    cout << "[ ";
    for (auto t : possibleMoves) {
        cout << t << ", ";
    }
    cout << "]" << endl;

    cout << "Tile #: ";
    typename GameType::move_t tileNo;
    cin >> tileNo;

    return tileNo;
}

template <Playable GameType, IntelligentPlayer<GameType> P>
typename GameType::move_t getMinimaxTile(const GameType& state, P player) {
    return AI::minimax(state, player);
}

#endif
