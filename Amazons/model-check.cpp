#include <functional>
#include <ranges>
#include <array>
#include <algorithm>
#include <chrono>
#include "amazons.hpp"
#include "model.hpp"

using namespace std;
using namespace chrono;
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
            return as.b.board[4][5] == 'x';
    });

    predicates.push_back([](const Amazons& as) {
            /* return whiteSurroundedByArrows(as) == 1; */
            return as.b.board[5][5] == 'x';
    });

    predicates.push_back([](const Amazons& as) {
            for (int i = ROWS * 4; i < ROWS * 6; i++) {
	        char t = as.getTile(i);
                if (t == 'w' || t == 'b') return true;
	    }

            return false;
    });

    auto t0 = high_resolution_clock::now();
    cout << "Found?: " << pathExists(azns, predicates, 2) << endl;
    auto t1 = high_resolution_clock::now();
    cout << "Staggered: " <<  duration_cast<milliseconds>(t1 - t0).count() << "ms" << endl;


    vector<function<bool(const Amazons&)>> bigJump;
    bigJump.push_back([](const Amazons& as) {
            /* return whiteSurroundedByArrows(as) == 1; */
            if (as.b.board[4][5] != 'x' || as.b.board[5][5] != 'x')
	        return false;

           for (int i = ROWS * 4; i < ROWS * 6; i++) {
	        char t = as.getTile(i);
                if (t == 'w' || t == 'b') return true;
	    }

            return false;
    });

    t0 = high_resolution_clock::now();
    cout << "Found?: " << pathExists(azns, bigJump, 2) << endl;
    t1 = high_resolution_clock::now();
    cout << "Big Jump: " <<  duration_cast<milliseconds>(t1 - t0).count() << "ms" << endl;

    return 0;
}
