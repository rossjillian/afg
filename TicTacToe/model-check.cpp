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
     *   o | o |
     *  -----------
     *     | o |
     *  -----------
     *     |   |
     */
    predicates.push_back(
        [](const TicTacToe& st) {
            return (st.b.board[0][0] == 'o'
                    && st.b.board[0][1] == 'o'
                    && st.b.board[1][1] == 'o');
        }
    );

    /* Predicate #2: Find a TTT state where Player1 ('o') wins */
    predicates.push_back(
        [](const TicTacToe& st) {
            return st.b.isWinner() && (st.getTurnParity() == 0);
        }
    );

    /* Print all boards that match predicate #1 */
    auto res = bfsFind(ttt, predicates[0], 10);
    for (const auto& ttt : res.matches) {
        string repr;
        for (auto& row : ttt.b.board) {
            for (auto& c : row) {
                repr += c;
            }
        }
        cout << repr << endl;
    }

    cout << "Count: " << res.matches.size() << endl;

    /* Check if it's possible to satisfy predicate #1 and #2 in 7 moves */
    cout << "Reachable?: " << pathExists(ttt, predicates, 7) << endl;
}
