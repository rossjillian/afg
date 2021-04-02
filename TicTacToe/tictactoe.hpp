#ifndef TICTACTOE_HPP
#define TICTACTOE_HPP

#include <vector>
#include "config.hpp"
#include "board.hpp"

using namespace std;


struct TicTacToe;

template <>
struct Config<TicTacToe>
{
    int width;
};

struct TicTacToe {
    using move_t = int;

    Board b;
    int turnCount;

    TicTacToe(Config<TicTacToe> c)
        : b(c.width),
          turnCount(0)
    {}

    bool isTerminal() {
        return b.isWinner() || b.isFull();
    }

    int getTurnCount() const { return turnCount; }

    int getCurrentPlayer() const { return turnCount % 2; }

    bool isWinner() const {
        return b.isWinner();
    }

    int getWinner() const {
        if (!isWinner()) return false;

        return (turnCount - 1) % 2;
    }

    void print() {
        b.print(false);
    }

    void makeMove(int tileNo) {
        b.makeMove(tileNo, turnCount++ % 2);
    }

    bool isValid(int tileNo) {
        return b.isValid(tileNo);
    }

    void setup() {
        cout << "Refer to moves using the following chart: " << endl;
        b.print(true);
    }

    vector<move_t> getAvailableMoves() const {
        return b.getAvailableMoves();
    }

    bool operator==(const TicTacToe& other_ttt) const
    {
        return b.board == other_ttt.b.board;
    }
};

template<> // Explicit specialization of std::hash<T>
struct std::hash<TicTacToe> {
    size_t operator() (const TicTacToe& ttt) const
        {
            string repr;
            for (auto& row : ttt.b.board) {
                for (auto& c : row) {
                    repr += c;
                }
            }

            return hash<string>()(repr);
        }
};

#endif
