#include <functional>
#include "amazons.hpp"
#include "model.hpp"

using namespace afg::model;

int main() {
    Amazons azns;

    auto st_93_83_93 = [](const Amazons& a) {
        return (a.b.board[8][3] == 'w'
                && a.b.board[9][3] == 'x');
    };

    auto res = bfsFind(azns, st_93_83_93, 1);
    cout << res.success << endl;
    cout << res.explored << endl;
}
