#ifndef TICTACTOE_H
#define TICTACTOE_H

#include <vector>

using namespace std; 
enum Player { human, computer };

class Board {
    public:
        bool isTerminal();
        Board(size_t size);
        void printBoard(bool instructions);
        bool checkValid(int move);
        void makeMove(int move, int player);
        bool isFull();

    private:
        vector<vector<char>> board;
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
        Player p1;
        Player p2;
        int currentplayer;
};

#endif