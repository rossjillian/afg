#ifndef BOARD_HPP
#define BOARD_HPP

#include <vector>

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
        template<Player T>
        void makeMove(int move, T player, Grid& board);
        template<Player T>
        void makeMove(int move, T player);
        bool isFull() const;
        bool isWinner() const;
        vector<int> getAvailableMoves() const;

    private:
        int getTileTurn(char elem) const;
        int checkColumns() const;
        int checkRows() const;
        int checkDiagonals() const;
};

#endif
