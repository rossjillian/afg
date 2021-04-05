#include <iostream>

#include <vector>

#include "game.hpp"
#include "tictactoe.hpp"
#include "players.hpp"
#include "model.hpp"

int main(int argc, char **argv)
{
    Human<TicTacToe> p1(0);
    Smart<TicTacToe> p2(1);

    Config<TicTacToe> config {3};

    TPGame<TicTacToe, Human<TicTacToe>, Smart<TicTacToe>> game(config, p1, p2);

    game.play();

    return 0;
}
