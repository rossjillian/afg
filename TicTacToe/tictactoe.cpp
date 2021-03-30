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
    vector<pair<TicTacToe, int>> matches;
};



SearchResult bfsFind(TicTacToe init, function<bool(const TicTacToe&, int)> is_goal, int depth) {
    queue<pair<TicTacToe, int>> q;
    q.push(make_pair(init, 0));
    unordered_set<TicTacToe, TicTacToe::HashFunction> visited;
    visited.insert(init);

    SearchResult res;
    res.explored = 0;

    while (!q.empty()) {
        auto [st, turn] = q.front();
        q.pop();
        res.explored++;

        if (is_goal(st, turn)) {
            res.success = true;
            res.matches.push_back(make_pair(st, turn));
            continue;
            /* return res; */
        }

        if (st.isTerminal() || turn == depth) {
            continue;
        }

        for (auto mv : st.b.getAvailableMoves()) {
            TicTacToe neighbor(st);
            neighbor.makeMove(mv, turn % 2);
            if (visited.find(neighbor) != visited.end()) {
                continue;
            }

            visited.insert(neighbor);
            q.push(make_pair(neighbor, turn + 1));
        }
    }

    res.success = !res.matches.empty();
    return res;
}

bool pathExists(TicTacToe init, vector<function<bool(const TicTacToe&, int)>> goals, int depth) {

    if (!goals.size()) {
        return true;
    }

    auto res = bfsFind(init, goals[0], depth);
    if (!res.success) {
        return false;
    }
    for (auto& [match, matchDepth] : res.matches) {
        if (pathExists(match, vector<function<bool(const TicTacToe&, int)>>(goals.begin() + 1, goals.end()), depth-matchDepth)) {
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
    vector<function<bool(const TicTacToe&, int)>> predicates;
    predicates.push_back([](const TicTacToe& st, int depth) { return st.b.board[0][0] == 'x' && st.b.board[0][1] == 'x' && st.b.board[1][1] == 'x'; });
    predicates.push_back([](const TicTacToe& st, int depth) { return st.b.isWinner() && ((depth - 1) % 2 == 1); });
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

    cout << pathExists(ttt, predicates, 100) << endl;

    /* Game<TicTacToe, HumanPlayer, StupidPlayer> game(config, p1, p2); */
    /* game.play(); */
}
