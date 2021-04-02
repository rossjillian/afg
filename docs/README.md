Design Overview
===============
This document presents an in-depth design overview of the major components of afg. Here we explain our rationale behind implementing these features and how we went about it in C++.

Game
----

Artificial Intelligence
-----------------------

Model Checking
--------------
Model checking involves employing a search agent to traverse the state space in
order to find states that satisfy a set of predicates. In order to abstract away
the search logic, we instead request from the game dev a state that satisfies
the constraints of the `Checkable` concept:

    template <class T>
    concept Checkable = requires(T m, T other, T::move_t mv) {
            { m.isTerminal() } -> same_as<bool>;
            { m.getTurnCount() } -> same_as<int>;
            { m.getAvailableMoves() } -> same_as<vector<typename T::move_t>>;
            { m.makeMove(mv) } -> same_as<void>;
            { m == other } -> same_as<bool>;
            { hash<T>{}(m) } -> same_as<size_t>;
    };

Here, we employ template programming to specify to the user what functionality
their state `T` needs to support in order to be hooked into our model checking
framework. With only these five functions implemented, the game dev can use our
search agent methods to validate their system.

One quick note on the `hash` constraint – we need this in order to use the state
`T` in hashable containers, like `unordered_set`. Search agents need to maintain
a `visited` set, so the state `T` must be hashable so that it can be inserted in
a set. We must also implement `operator==()`, but that's not too interesting.

Hash can be supported through the use of explicit specialization. `hash<T>` is a
templatized struct from the standard library that needs to be instantiated for
whatever `T` you're trying to use with the model checker. See below for an
example of explicit specialization when we implemented `hash` for `TicTacToe`:

    template<>
    struct std::hash<TicTacToe> // Explicit specialization of std::hash<T>
    {
        size_t operator() (const TicTacToe& ttt) const {
                string repr;
                for (auto& row : ttt.b.board) {
                    for (auto& c : row) {
                        repr += c;
                    }
                }

                return hash<string>()(repr);
        }
    };

Finally, here are the two main model checking utilities.

    template<Checkable GameType, Predicate<GameType> Function>
    SearchResult<GameType> bfsFind(GameType initState,
                                   Function isGoal,
                                   int depthLimit);

`bfsFind()` is a depth-limited BFS search that traverses the state space. We return a
templatized `SearchResult` which contains some information about the search –
success, number of states explored, and a vector of matches.


    template<Checkable GameType, Predicate<GameType> Function>
    bool pathExists(const GameType& initState,
                    vector<Function> predicates,
                    int depthLimit);

`pathExists()` is meant to chain several `bfsFind()`s together by going through
the vector of predicates and successively applying them.

Both `bfsFind()` and `pathExists()` are available as simple templated functions
in the `Model` namespace. No extra object creation required to use these
powerful functions.

The `Function` template parameter is constrained using the `Predicate` concept,
just for the sake of adding better typechecking to the function. It has to take a state
and return a bool, so that's what we mandate:

    template <class Function, checkable Model>
    concept Predicate = requires(Function f, Model m) {
        { f(m) } -> same_as<bool>;
    };

I originally used `std::function<bool(const Model&)>` but found that that didn't work too well
whenever I used lambdas. I suppose the phase of the compiler that does template computations
happens before the phase were lambdas are typechecked to see if they can be converted to an
equivalent type.