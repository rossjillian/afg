#include <iostream>

#include <vector>

#include "game.hpp"
#include "amazons.hpp"
#include "players.hpp"

//REMOVE: 
#include "board.hpp"

int main(int argc, char **argv)
{
    //HumanPlayer<Amazons> p1(0);
    //HumanPlayer<Amazons> p2(0);

    Board board;
    board.print(true);
    board.print(false);
    Move move = {1, 3, 14, 15};
    //cout << board.isValid(move) << endl;
    board.makeMove(move, 1);
    board.print(false);

    Move move1 = {1, 14, 44, 14};
    board.makeMove(move1, 1);
    board.print(false);

    vector<Move> moves = board.getAvailableMoves(1);
    /*for (Move move : moves)
    {
        cout << move.queenStartingPos << ", " << move.queenEndingPos << ", " << move.firePos << endl;
    }*/

    /*HumanPlayer<TicTacToe> p1(0);
    SmartPlayer<TicTacToe> p2(1);

    Config<TicTacToe> config {3};

    TPGame<TicTacToe, HumanPlayer<TicTacToe>, SmartPlayer<TicTacToe>> game(config, p1, p2);

    game.play();

    return 0;*/
}
