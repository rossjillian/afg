#include <iostream>
#include <vector>
#include <iomanip>

#include "tictactoe.hpp"
#include "model.hpp"

int main(int argc, char **argv) {
    Config<TicTacToe> config {3};
    TicTacToe ttt(config);

    vector<function<bool(const TicTacToe&)>> predicates;
    predicates.push_back([](const TicTacToe& st) { return st.b.board[0][0] == 'x' && st.b.board[0][1] == 'x' && st.b.board[1][1] == 'x'; });
    predicates.push_back([](const TicTacToe& st) { return st.b.isWinner() && (st.getWinner() == 1); });
    /* gcauto res = Model::bfsFind(ttt, predicates[1], 10); */
    /* for (const auto& ttt : res.matches) { */
    /*     string repr; */
    /*     for (auto& row : ttt.b.board) { */
    /*         for (auto& c : row) { */
    /*             repr += c; */
    /*         } */
    /*     } */
    /*     cout << repr << endl; */
    /* } */

    cout << Model::pathExists(ttt, predicates, 3) << endl;
}
