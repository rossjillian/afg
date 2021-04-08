#ifndef TICTACTOE_HPP
#define TICTACTOE_HPP

#include <vector>
#include "config.hpp"
#include "board.hpp"
#include "game.hpp"

using namespace std;

struct TicTacToe;

struct TicTacToe {
    using move_t = int;

    Board b;
    int turnCount;

    TicTacToe(int width)
        : b(width),
          turnCount(0)
    {}

    bool isTerminal() const {
        return b.isWinner() || b.isFull();
    }

    int getTurnCount() const { return turnCount; }

    int getTurnParity() const { return turnCount % 2; }

    bool isWinner() const {
        return b.isWinner();
    }

    void print() {
        b.print(false);
    }

    void makeMove(int tileNo) {
        b.makeMove(tileNo, turnCount % 2);
        if (!b.isWinner())
            turnCount++;
    }

    bool isValid(int tileNo) {
        return b.isValid(tileNo);
    }

    void setup() {
        cout << "Refer to moves using the following chart: " << endl;
        b.print(true);
    }

    vector<int> getAvailableMoves() const {
        return b.getAvailableMoves();
    } 

    bool operator==(const TicTacToe& other_ttt) const
    {
        return b.board == other_ttt.b.board;
    }

    friend ostream& operator<<(ostream& os, const TicTacToe& t);
    friend ostream& operator<<(ostream& os, const move_t& mv);
    friend istream& operator>> (istream&in, move_t& mv);
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

ostream& operator<<(ostream& os, const TicTacToe& t) {
     os << t.b;
     return os;
}


ostream& operator<<(ostream& os, const TicTacToe::move_t& mv) {
     cout << "Tile #: ";
     os << mv;
     return os;
}

istream& operator>> (istream&in, TicTacToe::move_t& mv) {
    int m;
    if (in >> m)
    {
        mv = m;
    }
    return in;
}

#endif
