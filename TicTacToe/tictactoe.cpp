#include <iostream>
#include <vector>
#include <iomanip>

#include "game.hpp"
#include "tictactoe.hpp"
#include "players.hpp"
#include <utility>

#include <queue>
#include <unordered_set>

struct SearchResult {
    bool success;
    int explored;
    vector<TicTacToe> matches;
};



SearchResult bfsFind(TicTacToe init, function<bool(const TicTacToe&)> is_goal, int depth) {
    queue<TicTacToe> q;
    q.push(init);
    unordered_set<TicTacToe, TicTacToe::HashFunction> visited;
    visited.insert(init);

    SearchResult res;
    res.explored = 0;

    while (!q.empty()) {
        auto st = q.front();
        q.pop();
        res.explored++;

        if (is_goal(st)) {
            res.success = true;
            res.matches.push_back(st);
            continue;
            /* return res; */
        }

        if (st.isTerminal() || st.turnCount == depth) {
            continue;
        }

        for (auto mv : st.getAvailableMoves()) {
            TicTacToe neighbor(st);
            neighbor.makeMove(mv);
            if (visited.find(neighbor) != visited.end()) {
                continue;
            }

            visited.insert(neighbor);
            q.push(neighbor);
        }
    }

    res.success = !res.matches.empty();
    return res;
}

bool pathExists(TicTacToe init, vector<function<bool(const TicTacToe&)>> goals, int depth) {

    if (!goals.size()) {
        return true;
    }

    auto res = bfsFind(init, goals[0], depth);
    if (!res.success) {
        return false;
    }
    for (auto& match : res.matches) {
        if (pathExists(match, vector<function<bool(const TicTacToe&)>>(goals.begin() + 1, goals.end()), depth-match.getTurnCount())) {
            return true;
        }
    }
    return false;
}

int main(int argc, char **argv)
{
    HumanPlayer p1;
    StupidPlayer p2;
    Config<TicTacToe> config {3};
    TicTacToe ttt(config);
    vector<function<bool(const TicTacToe&)>> predicates;
    predicates.push_back([](const TicTacToe& st) { return st.b.board[0][0] == 'x' && st.b.board[0][1] == 'x' && st.b.board[1][1] == 'x'; });
    predicates.push_back([](const TicTacToe& st) { return st.b.isWinner() && (st.getWinner() == 1); });
    /* auto res = bfsFind(ttt, predicates[1], 10); */
    /* for (auto [ttt, _] : res.matches) { */
    /*     string repr; */
    /*     for (auto& row : ttt.b.board) { */
    /*         for (auto& c : row) { */
    /*             repr += c; */
    /*         } */
    /*     } */
    /*     cout << repr << endl; */
    /* } */

    /* cout << pathExists(ttt, predicates, 100) << endl; */

    Game<TicTacToe, HumanPlayer, StupidPlayer> game(config, p1, p2);
    game.play();
}
