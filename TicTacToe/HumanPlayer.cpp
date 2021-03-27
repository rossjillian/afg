#include <iostream>

#include "tictactoe.h"

using namespace std;

HumanPlayer::HumanPlayer(int t) {
    timeout = t;
}

int HumanPlayer::getStrategy(const Board& board) {
    vector<int> possibleMoves = board.getAvailableMoves();
    for (int t : possibleMoves) {
        cout << t << ", " << endl;
    }

    int tileNo;
    cin >> tileNo;
    // Error check in while loop

    return tileNo;
}
