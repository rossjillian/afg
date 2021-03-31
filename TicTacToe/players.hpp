#ifndef PLAYERS_HPP
#define PLAYERS_HPP

#include <iostream>
#include <vector>

#include "tictactoe.hpp"

using namespace std;

class HumanPlayer {
    public:
        HumanPlayer(int t = 0)
            : timeout(t)
        {}

        int getStrategy(const TicTacToe& state) {
            vector<int> possibleMoves = state.getAvailableMoves();
            cout << "[ ";
            for (int t : possibleMoves) {
                cout << t << ", ";
            }
            cout << "]" << endl;


            cout << "Tile #: ";
            int tileNo;
            cin >> tileNo;

            return tileNo;
        }

    private:
        int timeout;
};

class StupidPlayer {
    public:
        StupidPlayer(int t = 0)
            : timeout(t)
        {}
        int getStrategy(const TicTacToe& state) {
            vector<int> possibleMoves = state.getAvailableMoves();
            return possibleMoves[0];
        }
    private:
        int timeout;
};

#endif
