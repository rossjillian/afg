#include <iostream>

#include <vector>

#include "game.hpp"
#include "amazons.hpp"
#include "players.hpp"

//REMOVE: 
#include "board.hpp"

int main(int argc, char **argv)
{
    Board board;
    board.print(false);
    Move move = {3, 12, 3};
    cout << board.isValid(move) << endl;

    /*HumanPlayer<TicTacToe> p1(0);
    SmartPlayer<TicTacToe> p2(1);

    Config<TicTacToe> config {3};

    TPGame<TicTacToe, HumanPlayer<TicTacToe>, SmartPlayer<TicTacToe>> game(config, p1, p2);

    game.play();

    return 0;*/
}
