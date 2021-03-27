#ifndef TICTACTOE_H
#define TICTACTOE_H

#include <vector>

using namespace std;
enum PlayerType { human, computer };
using Grid = vector<vector<char>>;

class Board {
    public:
        bool isTerminal();
        Board(size_t size);
        void printBoard(bool instructions);
        void printBoard(const Grid& board, bool instructions);
        bool isValid(int move) const;
        void makeMove(int move, int player, Grid& board);
        void makeMove(int move, int player);
        bool isFull();
        vector<int> getAvailableMoves() const;

    private:
        Grid board;
        size_t numTiles;
        bool checkColumns();
        bool checkRows();
        bool checkDiagonals();
};

class HumanPlayer {
    public:
        HumanPlayer(int t = 0);
        int getStrategy(const Board& board);
    private:
        int timeout;
};

class Game {
    public:
        Game(HumanPlayer player1, HumanPlayer player2, int size);
        void Play();
    private:
        Board board;
        HumanPlayer p1;
        HumanPlayer p2;
        int currentplayer;
};

#endif
