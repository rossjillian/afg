#include <iostream>
#include <vector>
#include <iomanip>
#include <chrono>

#include "tictactoe.hpp"
#include "model.hpp"

using namespace std;
using namespace chrono;
using namespace afg::model;

int main(int argc, char **argv) {
    TicTacToe ttt(3);

    vector<function<bool(const TicTacToe&)>> predicates;

    predicates.push_back(
        [](const TicTacToe& st) {
            return st.b.board[0][0] == 'o';
        }
    );

    predicates.push_back(
        [](const TicTacToe& st) {
            return st.b.board[0][1] == 'o';
        }
    );

    predicates.push_back(
        [](const TicTacToe& st) {
            return st.b.board[1][1] == 'o';
        }
    );

    predicates.push_back(
        [](const TicTacToe& st) {
            return st.b.isWinner() && (st.getTurnParity() == 0);
        }
    );

    /* Find a winning state
     * Note that we include intermediate steps */
    auto t0 = high_resolution_clock::now();
    cout << "Found?: " << pathExists(ttt, predicates, 7) << endl;
    auto t1 = high_resolution_clock::now();

    cout << "Staggered: " << duration_cast<milliseconds>(t1 - t0).count() << endl;

    vector<function<bool(const TicTacToe&)>> predicatesSingleton;
    predicatesSingleton.push_back(predicates[3]);

    /* Find a winning state
     * Note the lack of the intermediate steps */
    t0 = high_resolution_clock::now();
    cout << "Found?: " << pathExists(ttt, predicatesSingleton, 7) << endl;
    t1 = high_resolution_clock::now();

    cout << "Direct: " << duration_cast<milliseconds>(t1 - t0).count() << endl;
}
