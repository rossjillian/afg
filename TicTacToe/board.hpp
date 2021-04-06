#ifndef BOARD_HPP
#define BOARD_HPP

#include <vector>
#include "game.hpp"

using namespace std;

using Grid = vector<vector<char>>;

void printBoard(const Grid& board, bool instructions);

class Board {
    public:
        Grid board;
        size_t numTiles;
        Board(size_t size);
        
        void print(bool instructions) const;
        friend ostream& operator<<(ostream& os, const Board& board);
        bool isValid(int move) const;
        void makeMove(int move, int turn, Grid& board);
        void makeMove(int move, int turn);
        bool isFull() const;
        bool isWinner() const;
        vector<int> getAvailableMoves() const;

    private:
        bool checkColumns() const;
        bool checkRows() const;
        bool checkDiagonals() const;
};

#endif
