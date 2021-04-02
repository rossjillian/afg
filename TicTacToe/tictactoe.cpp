#include <iostream>
#include <vector>

#include "game.hpp"
#include "tictactoe.hpp"
#include "players.hpp"
#include "model.hpp"


int main(int argc, char **argv)
{
    HumanPlayer p1(0);
    StupidPlayer p2;

    Config<TicTacToe> config {3};

    TPGame<TicTacToe, HumanPlayer, StupidPlayer> game(config, p1, p2);

    game.play();

    return 0;
}
