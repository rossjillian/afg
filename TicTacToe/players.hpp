#ifndef PLAYERS_HPP
#define PLAYERS_HPP

#include <iostream>
#include <vector>

#include "tictactoe.hpp"

using namespace std;

class HumanPlayer {
    public:
        HumanPlayer(double t = 0.0)
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

        double getTimeout() const {
            return timeout;
        }

    private:
        double timeout;
};

class StupidPlayer {
    public:
        StupidPlayer(double t = 0.0)
            : timeout(t)
        {}
        int getStrategy(const TicTacToe& state) {
            vector<int> possibleMoves = state.getAvailableMoves();
            return possibleMoves[0];
        }
         double getTimeout() const {
            return timeout;
        }
    private:
        double timeout;
};

#endif
