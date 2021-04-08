#include <iostream>

#include <vector>

#include "game.hpp"
#include "tictactoe.hpp"
#include "players.hpp"
#include "model.hpp"

int main(int argc, char **argv)
{
    HumanPlayer<TicTacToe> p1(0);
    SmartPlayer<TicTacToe> p2(1);

    TicTacToe ttt(3);

    TPGame<TicTacToe, HumanPlayer<TicTacToe>, SmartPlayer<TicTacToe>> game(ttt, p1, p2);

    game.play();

    return 0;
}
