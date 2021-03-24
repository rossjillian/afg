#include <iostream>
#include "tictactoe.h"

using namespace std; 

enum Player { human, computer };

class Board {
    public:
        Board(Player player1, Player player2) : p1(player1), p2(player2) {}
    private:
        Player p1;
        Player p2;
        Player currentplayer;
};

int main (int argc, char **argv)
{
    return 1;
}