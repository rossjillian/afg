#ifndef BOARD_HPP
#define BOARD_HPP

#include <vector>

using namespace std;

using Grid = vector<vector<char>>;

class Board {
    public:
        Board(size_t size);
        void print(bool instructions);
        void print(const Grid& board, bool instructions);
        bool isValid(int move) const;
        void makeMove(int move, int player, Grid& board);
        void makeMove(int move, int player);
        bool isFull();
        bool isTerminal();
        bool isWinner();
        vector<int> getAvailableMoves() const;

    private:
        Grid board;
        size_t numTiles;
        bool checkColumns();
        bool checkRows();
        bool checkDiagonals();
};

#endif
