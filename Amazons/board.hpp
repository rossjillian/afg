#ifndef BOARD_HPP
#define BOARD_HPP

#include <vector>
#include "game.hpp"

using namespace std;

using Grid = vector<vector<char>>;

void printBoard(const Grid& board, bool instructions);

struct Move {
    int turn;
    int queenStartingPos;
    int queenEndingPos;
    int firePos;
};

class Board {
    public:
        Grid board;
        Board();

        void print(bool instructions) const;
        bool isValid(Move move) const;
        void makeMove(Move move, int turn);
        bool isWinner(int turn) const;
        vector<Move> getAvailableMoves(int turn) const;
        friend ostream& operator<<(ostream& os, const Board& board);

    private:
        bool isValidMovement(int start, int end) const;
        bool isOnRow(int start, int end) const;
        bool isOnColumn(int start, int end) const;
        bool isOnDiagonalUp(int start, int end) const;
        bool isOnDiagonalDown(int start, int end) const;
        bool obstructedColumn(int start, int end) const;
        bool obstructedRow(int start, int end) const;
        bool obstructedDiagonalUp(int start, int end) const;
        bool obstructedDiagonalDown(int start, int end) const;
};

#endif