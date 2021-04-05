#include <iostream>

#include <vector>

#include "game.hpp"
#include "tictactoe.hpp"
#include "players.hpp"
#include "model.hpp"

int main(int argc, char **argv)
{
    Player<TicTacToe> Human(0);
    Player<TicTacToe> Smart(1);

    Config<TicTacToe> config {3};

    TPGame<TicTacToe> game(config, p1, p2);

    game.play();

    return 0;
}
