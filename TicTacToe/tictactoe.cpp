#include <iostream>
#include <vector>

#include "game.hpp"
#include "tictactoe.hpp"
#include "players.hpp"
#include "model.hpp"


int main(int argc, char **argv)
{
    HumanPlayer p1(0);
    SmartPlayer p2;

    Config<TicTacToe> config {3};

    TPGame<TicTacToe, HumanPlayer, SmartPlayer> game(config, p1, p2);

    game.play();

    return 0;
}
