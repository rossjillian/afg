#ifndef STRATEGY_HPP
#define STRATEGY_HPP

template <class T>
int getRandomTile(const T& state);

template <class T>
int getIOTile(const T& state);

template <class T>
int getMinimaxTile(const T& state, Player<T> player);

#endif
