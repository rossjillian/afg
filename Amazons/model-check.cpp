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

const int ROWCOUNT = 10;
const int NUMTILES = 100;

int main() {
    Amazons azns;

    vector<function<bool(const Amazons&)>> predicates;
    predicates.push_back([](const Amazons& as) {
            return as.b.board[4][5] == 'x';
    });

    predicates.push_back([](const Amazons& as) {
            return as.b.board[5][5] == 'x';
    });

    predicates.push_back([](const Amazons& as) {
            for (int i = ROWCOUNT * 4; i < ROWCOUNT * 6; i++) {
	        char t = as.getTile(i);
                if (t == 'w' || t == 'b') return true;
	    }

            return false;
    });

    auto t0 = high_resolution_clock::now();
    cout << "Found?: " << pathExists(azns, predicates, 2) << endl;
    auto t1 = high_resolution_clock::now();
    cout << "Staggered: " <<  duration_cast<seconds>(t1 - t0).count() << "s" << endl;


    vector<function<bool(const Amazons&)>> bigJump;
    bigJump.push_back([](const Amazons& as) {
            if (as.b.board[4][5] != 'x' || as.b.board[5][5] != 'x')
	        return false;

           for (int i = ROWCOUNT * 4; i < ROWCOUNT * 6; i++) {
	        char t = as.getTile(i);
                if (t == 'w' || t == 'b') return true;
	    }

            return false;
    });

    t0 = high_resolution_clock::now();
    cout << "Found?: " << pathExists(azns, bigJump, 2) << endl;
    t1 = high_resolution_clock::now();
    cout << "Big Jump: " <<  duration_cast<seconds>(t1 - t0).count() << "s" << endl;

    return 0;
}
