#include <iostream>

#include <vector>

#include "game.hpp"
#include "amazons.hpp"
#include "players.hpp"
#include "board.hpp"

using namespace afg::players;
using namespace afg::game;

int main(int argc, char **argv)
{
    HumanPlayer<Amazons> p1(0);
    HumanPlayer<Amazons> p2(0);
    Amazons amz;

    TPGame<Amazons, HumanPlayer<Amazons>, HumanPlayer<Amazons>> game(amz, p1, p2);

    game.play();

    return 0;
}
