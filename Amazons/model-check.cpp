#include <functional>
#include <ranges>
#include <array>
#include <algorithm>
#include "amazons.hpp"
#include "model.hpp"

using namespace std;
using namespace afg::model;

const int ROWS = 10;
const int NUMTILES = 100;



/* int whiteSurroundedByArrows(const Amazons& azns) { */
/*     auto board = views::iota(0, NUMTILES); */
/*    return count_if(board.begin(), board.end(), */
/*                    [&azns](int tileNo) { */
/*                        if (azns.getTile(tileNo) != 'w') return false; */
/*                        array<int, 8> neighbors{{tileNo + 1, tileNo - 1, */
/*                              tileNo - ROW, tileNo - ROW - 1, tileNo - ROW + 1, */
/*                              tileNo + ROW, tileNo + ROW - 1, tileNo + ROW + 1}}; */
/*                        return all_of(neighbors.begin(), neighbors.end(), */
/*                                      [&azns](int n) { */
/*                                        int t = azns.getTile(n); */
/*                                        return (t == 0 // Out of bounds */
/*                                                || t == 'x'); // Arrow */
/*                                        }); */
/*                    }); */
/* } */

int main() {
    Amazons azns;

    vector<function<bool(const Amazons&)>> predicates;
    predicates.push_back([](const Amazons& as) {
            /* return whiteSurroundedByArrows(as) == 1; */
            return as.b.board[0][5] == 'x';
    });

    predicates.push_back([](const Amazons& as) {
            /* return whiteSurroundedByArrows(as) == 1; */
            return as.b.board[1][5] == 'x';
    });

    predicates.push_back([](const Amazons& as) {
            /* return whiteSurroundedByArrows(as) == 1; */
            return as.b.board[2][5] == 'x';
    });

    cout << pathExists(azns, predicates, 3) << endl;

    return 0;
}
