#ifndef MODEL_HPP
#define MODEL_HPP

/* #include <iostream> */
/* #include "config.hpp" */
#include <queue>
#include <unordered_set>
#include <concepts>

using namespace std;

template <class T>
concept Checkable = requires(T a) {
        { a.meme() } -> same_as<void>;
};

namespace Model {
    template<class GameType>
    struct SearchResult {
        bool success;
        int explored;
        vector<GameType> matches;
    };

    template<class GameType>
    SearchResult<GameType> bfsFind(GameType initState,
                                   function<bool(const GameType&)> isGoal,
                                   int depthLimit) {
        queue<GameType> frontier;
        unordered_set<GameType, typename GameType::HashFunction> visited;

        frontier.push(initState);
        visited.insert(initState);

        SearchResult<GameType> result;
        result.explored = 0;

        while(!frontier.empty()) {
            GameType st = frontier.front();
            frontier.pop();
            result.explored++;

            if (isGoal(st)) {
                result.success = true;
                result.matches.push_back(st);
                continue;
            }

            if (st.isTerminal() || st.getTurnCount() == depthLimit) {
                continue;
            }

            for (const auto& mv : st.getAvailableMoves()) {
                GameType neighbor(st);
                neighbor.makeMove(mv);

                if (visited.find(neighbor) != visited.end()) {
                    continue;
                }

                visited.insert(neighbor);
                frontier.push(neighbor);
            }
        }

        result.success = !result.matches.empty();
        return result;
    }


    template<class GameType>
    bool pathExists(const GameType& initState,
                    vector<function<bool(const GameType&)>> predicates,
                    int depthLimit) {

        if (!predicates.size()) {
            return true;
        }

        auto result = bfsFind(initState, predicates[0], depthLimit);
        if (!result.success) {
            return false;
        }

        for (const auto& match : result.matches) {
            if (pathExists(match,
                           vector<function<bool(const GameType&)>>(predicates.begin() + 1, predicates.end()), 
                           depthLimit - match.getTurnCount())) {
                return true;
            }
        }

        return false;
    }
}


#endif
