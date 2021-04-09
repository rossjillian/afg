#include <iostream>
#include <vector>

#include "game.hpp"
#include "amazons.hpp"
#include "players.hpp"
#include "board.hpp"

using namespace afg::players;
using namespace afg::game;

template<>
int QuickPlayer<Amazons>::heuristic(const Amazons& state) {
    vector<Move> playerMoves = state.getAvailableMoves(this->getParity()); 
    vector<Move> opponentMoves = state.getAvailableMoves(this->getParity() ^ 1);
    return playerMoves.size() - opponentMoves.size();
}

int main(int argc, char **argv)
{
    HumanPlayer<Amazons> p1(0);
    QuickPlayer<Amazons> p2(0, 3);
    Amazons amz;

    TPGame<Amazons, HumanPlayer<Amazons>, QuickPlayer<Amazons>> game(amz, p1, p2);

    game.play();

    return 0;
}
