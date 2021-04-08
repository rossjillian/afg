#include <iostream>
#include <vector>
#include <iomanip>

#include "tictactoe.hpp"
#include "model.hpp"

using namespace std;
using namespace afg::model;

int main(int argc, char **argv) {
    TicTacToe ttt(3);

    vector<function<bool(const TicTacToe&)>> predicates;

    /* Predicate #1: Find TTT states that look like this:
     *   x | x |
     *  -----------
     *     | x |
     *  -----------
     *     |   |
     */
    predicates.push_back(
        [](const TicTacToe& st) {
            return (st.b.board[0][0] == 'x'
                    && st.b.board[0][1] == 'x'
                    && st.b.board[1][1] == 'x');
        }
    );

    /* Predicate #2: Find a TTT state where Player1 ('x') wins */
    predicates.push_back(
        [](const TicTacToe& st) {
            return st.b.isWinner() && (st.getTurnParity() == 0);
        }
    );

    /* Print all boards that match predicate #1 */
    auto res = bfsFind(ttt, predicates[0], 10);
    cout << res.success << endl;
    for (const auto& ttt : res.matches) {
        string repr;
        for (auto& row : ttt.b.board) {
            for (auto& c : row) {
                repr += c;
            }
        }
        cout << repr << endl;
    }

    /* Check if it's possible to satisfy predicate #1 and #2 in 7 moves */
    cout << pathExists(ttt, predicates, 7) << endl;
}
