#ifndef MODEL_HPP
#define MODEL_HPP

#include <queue>
#include <unordered_set>
#include <concepts>
#include <functional>
#include <vector>


namespace afg {
namespace model {

template <class T>
concept Checkable = requires(T m, T other, T::move_t mv) {
        { m.isTerminal() } -> std::same_as<bool>;
        { m.getTurnCount() } -> std::same_as<int>;
        { m.getAvailableMoves() } -> std::same_as<std::vector<typename T::move_t>>;
        { m.makeMove(mv) } -> std::same_as<void>;
        { m == other } -> std::same_as<bool>;
        { std::hash<T>{}(m) } -> std::same_as<size_t>;
};

template <class Function, class Model>
concept Predicate = Checkable<Model> && requires(Function f, Model m) {
    { f(m) } -> std::same_as<bool>;
};

template<Checkable GameType>
struct SearchResult {
    bool success;
    int explored;
    std::vector<GameType> matches;
};

template<Checkable GameType, Predicate<GameType> Function>
SearchResult<GameType> bfsFind(const GameType& initState,
                               Function isGoal,
                               int depthLimit) {
    std::queue<GameType> frontier;
    std::unordered_set<GameType> visited;

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
                const std::vector<Function>& predicates,
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
                       std::vector<std::function<bool(const GameType&)>>(predicates.begin() + 1, predicates.end()),
                       depthLimit - match.getTurnCount())) {
            return true;
        }
    }

    return false;
}

} // namespace model
} // namespace afg

#endif
