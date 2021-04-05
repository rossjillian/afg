#ifndef PLAYERS_HPP
#define PLAYERS_HPP

#include <iostream>
#include <vector>

#include "tictactoe.hpp"
#include "strategy.hpp"
#include "game.hpp"

using namespace std;

template <class T>
class HumanPlayer : public Player<T> {
    public:
	HumanPlayer(int o, double t = 0.0) : Player<T>(o, t) {}
        typename T::move_t getStrategy(const T& state) { return io_tile(state); }

};

template <class T>
class StupidPlayer : public Player<T> {
    public:
	StupidPlayer(int o, double t = 0.0) : Player<T>(o, t) {}
        typename T::move_t getStrategy(const T& state) { return io_tile(state); }

};

template <class T>
class SmartPlayer : public Player<T> {
    public:
	SmartPlayer(int o, double t = 0.0) : Player<T>(o, t) {}
        typename T::move_t getStrategy(const T& state) { return io_tile(state); }

};

#endif
