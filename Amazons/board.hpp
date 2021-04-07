#ifndef BOARD_HPP
#define BOARD_HPP

#include <vector>
#include "game.hpp"

using namespace std;

using Grid = vector<vector<char>>;

void printBoard(const Grid& board, bool instructions);

struct Move {
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

    private:
        bool isOnRow(int start, int end) const;
        bool isOnColumn(int start, int end) const;
        bool isOnDiagonals(int start, int end) const;

};

#endif