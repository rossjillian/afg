#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

#include "strategy.hpp"
#include "ai.hpp"

using namespace std;

template <class T>
typename T::move_t getRandomTile(const T& state) {
    vector<typename T::move_t> possibleMoves = state.getAvailableMoves();
    auto rng = std::default_random_engine {};
	
    std::shuffle(possibleMoves.begin(), possibleMoves.end(), rng);
	
    return possibleMoves[0];
}

template <class T>
typename T::move_t getIOTile(const T& state) {
    vector<typename T::move_t> possibleMoves = state.getAvailableMoves();
    cout << "[ ";
    for (typename T::move_t t : possibleMoves) {
        cout << t << ", ";
    }
    cout << "]" << endl;

    cout << "Tile #: ";
    int tileNo;
    cin >> tileNo;

    return tileNo;
}

template <class T>
typename T::move_t getMinimaxTile(const T& state, Player<T> player) {
    return AI::minimax(state, player);
}


