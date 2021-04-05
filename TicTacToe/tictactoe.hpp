#ifndef TICTACTOE_HPP
#define TICTACTOE_HPP

#include <vector>
#include "config.hpp"
#include "board.hpp"
#include "game.hpp"

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

    bool isTerminal() const {
        return (b.getWinningTurn() != -1) || b.isFull();
    }

    int getTurnCount() const { return turnCount; }

    int getTurnParity() const { return turnCount % 2; } 

    // getTurnPlayer

    bool isWinner() const {
        if (b.getWinningTurn() == -1)
            return false;
        return true;  
    }
    
    bool isWinner(Player<TicTacToe> p) const {
        if (b.getWinningTurn() == p.getTurnOrder())
            return true;
        return false;
    }

    int getWinningTurn() const {
        if (b.getWinningTurn() == -1) return false;
    
        return b.getWinningTurn();
    }

    void print() {
        b.print(false);
    }

    void makeMove(int tileNo) {
        b.makeMove(tileNo, turnCount++ % 2);
        // Check before incrementing
    }
    
    void makeMove(int tileNo, Player<TicTacToe> p) {
        b.makeMove(tileNo, p.getTurnOrder());
    }

    void retractMove(int tileNo) {
        b.retractMove(tileNo, turnCount++ % 2);
    }
    
    void retractMove(int tileNo, Player<TicTacToe> p) {
        b.retractMove(tileNo, p.getTurnOrder());
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
