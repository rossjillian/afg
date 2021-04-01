#ifndef BOARD_HPP
#define BOARD_HPP

#include <vector>

using namespace std;

using Grid = vector<vector<char>>;

class Board {
    public:
        Grid board;
        size_t numTiles;
        Board(size_t size);
        void print(bool instructions);
        void print(const Grid& board, bool instructions);
        bool isValid(int move) const;
        void makeMove(int move, int player, Grid& board);
        void makeMove(int move, int player);
        void retractMove(int move, int player, Grid& board);
        void retractMove(int move, int player);
        bool isFull() const;
        bool isTerminal() const;
        bool isWinner() const;
        vector<int> getAvailableMoves() const;

    private:
        bool checkColumns() const;
        bool checkRows() const;
        bool checkDiagonals() const;
};

#endif
