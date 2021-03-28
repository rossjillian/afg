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
    Board b;

    TicTacToe(Config<TicTacToe> c)
        : b(c.width)
    {}

    bool isTerminal() {
        return b.isWinner() || b.isFull();
    }

    bool isWinner() {
        return b.isWinner();
    }

    void print() {
        b.print(false);
    }

    void makeMove(int tileNo, int currentPlayer) {
        b.makeMove(tileNo, currentPlayer);
    }
};

#endif
