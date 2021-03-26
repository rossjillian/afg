#ifndef TICTACTOE_H
#define TICTACTOE_H

#include <vector>

using namespace std;
enum Player { human, computer };
using Grid = vector<vector<char>>;

class Board {
    public:
        bool isTerminal();
        Board(size_t size);
        void printBoard(bool instructions);
        void printBoard(const Grid& board, bool instructions);
        bool isValid(int move);
        void makeMove(int move, int player, Grid& board);
        void makeMove(int move, int player);
        bool isFull();
        vector<Grid> getMoves(int currentplayer);

    private:
        Grid board;
        size_t numTiles;
        bool checkColumns();
        bool checkRows();
        bool checkDiagonals();
};

class Game {
    public:
        Game(Player player1, Player player2, int size);
        void Play();
    private:
        Board board;
        /* Player p1; */
        /* Player p2; */
        int currentplayer;
};

#endif
