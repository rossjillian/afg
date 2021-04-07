Manual
======
todo

Game
----

Artificial Intelligence
-----------------------

Model
-----
The `afg::model` namespace contains two concepts (`Checkable` and `Predicate`) along with two utilities `bfsFind()` and `pathExists()`.


### Checkable
This concepts specifies an interface for what constitutes a searchable state. In addition to methods needed to expand the search space, we also need `operator==` and `hash<T>` in order to hash the state object into data structures used in the state traversal algorithms.


    template <class T>
    concept Checkable = requires(T m, T other, T::move_t mv) {
        { m.isTerminal() } -> same_as<bool>;
        { m.getTurnCount() } -> same_as<int>;
        { m.getAvailableMoves() } -> same_as<vector<typename T::move_t>>;
        { m.makeMove(mv) } -> same_as<void>;
        { m == other } -> same_as<bool>;
        { hash<T>{}(m) } -> same_as<size_t>;
    };

Here we see that the checkable class `T` must provide a typename `move_t` representing the type of a move which, when passed to `makeMove()`, takes a state and transforms it into one of its neighboring state.

`isTerminal(), getTurnCount(), getAvailableMoves()` are used to detect a leaf node, the depth, and the neighbors in the search space, respectively.


### Predicate
This concept is meant to constrain a function object for typechecking purposes. A predicate is a function object implemented by the user of the library that takes in a state and says whether or not it's a goal that they were looking for.

    template <class Function, class Model>
    concept Predicate = Checkable<Model> && requires(Function f, Model m) {
        { f(m) } -> same_as<bool>;
    };

A lambda that takes in a `const Model&` and returns `bool` will sastisfy this concept.

### SearchResult
A simple wrapper struct over a few fields that describe the results of a goal-based BFS search.

    template<Checkable GameType>
    struct SearchResult {
        bool success;
        int explored;
        vector<GameType> matches;
    };

`success` indicates whether any state visted satisfied the predicate. `explored` indicates how many state were visited. `matches` is a vector containing all states that matched the predicate.

### bfsFind()
This is the fundamental function for performing model checking. It performs a simple goal-based breadth-first search through the state space. For any state it encounters that satisfies `isGoal()`, it will add the state to the `SearchResult.matches`.

    template<Checkable GameType, Predicate<GameType> Function>
    SearchResult<GameType> bfsFind(GameType initState,
                                   Function isGoal,
                                   int depthLimit)

One additional note – `depthLimit` is here to enforce a bound on the search space. Even for simple games, the space can quickly grow on the order of `O(2^d)` which will bring down the runtime. Having a depth limit also helps tests certain game scenarios (e.g. can we reach this move within `d` moves?).

### pathExists()
There are times where one desires to check the existence of several states in sequence – a scenario. For this, we use `pathExists()`, which essentially chains together calls to `bfsFind()` until the final predicate in `predicates` is satisfied.


    template<Checkable GameType, Predicate<GameType> Function>
    bool pathExists(const GameType& initState,
                    const vector<Function>& predicates,
                    int depthLimit);

`depthLimit` is meant to be cumulative for the entire scenario search. That is, if the first predicate is satisfied at depth `d`, then the remaining predicates must be satisfied within `depthLimit - d` turns.