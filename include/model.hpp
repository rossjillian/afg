#ifndef MODEL_HPP
#define MODEL_HPP

#include <queue>
#include <unordered_set>
#include <concepts>
#include <functional>

using namespace std;

template <class T>
concept Checkable = requires(T m, T other, T::move_t mv) {
        { m.isTerminal() } -> same_as<bool>;
        { m.getTurnCount() } -> same_as<int>;
        { m.getAvailableMoves() } -> same_as<vector<typename T::move_t>>;
        { m.makeMove(mv) } -> same_as<void>;
        { m == other } -> same_as<bool>;
        { hash<T>{}(m) } -> same_as<size_t>;
};

template <class Function, class Model>
concept Predicate = requires(Function f, Model m) {
    Checkable<Model>;
    { f(m) } -> same_as<bool>;
};

namespace Model {
    template<Checkable GameType>
    struct SearchResult {
        bool success;
        int explored;
        vector<GameType> matches;
    };

    template<Checkable GameType, Predicate<GameType> Function>
    SearchResult<GameType> bfsFind(GameType initState,
                                   Function isGoal,
                                   int depthLimit) {
        queue<GameType> frontier;
        unordered_set<GameType> visited;

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


    template<Checkable GameType, Predicate<GameType> Function>
    bool pathExists(const GameType& initState,
                    vector<Function> predicates,
                    int depthLimit) {

        if (depthLimit <= 0)
            return false;

        if (!predicates.size())
            return true;

        auto result = bfsFind(initState, predicates[0], depthLimit);
        if (!result.success)
            return false;

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
