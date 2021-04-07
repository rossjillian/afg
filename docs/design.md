Design Overview
===============
This document presents an in-depth design overview of the major components of afg. Here we explain our rationale behind implementing these features and how we went about it in C++.

A recurring theme throughout the library is that we chose to use templates as opposed to virtual base classes so we can have compile-time polymorphism. Templates allow us to have polymorphism like virtual classes, except the work needed to make them possible is done during compile-time. To improve typechecking, we employ C++20 Concepts to constrain our templates. Concepts are also great for documentation and present a clear interface to the library user.

Game
----

Artificial Intelligence
-----------------------
To employ a game player that uses AI algorithms like minimax, the game player needs to have a heuristic function that evaluates state. Thus, in order for the game dev to use minimax, we request a player that satisfies the constraints of the `IntelligentPlayer` concept:

    template <class T, class G>
    concept Player = requires(T player, G game) {
        Playable<G>;
        { player.getStrategy(game) } -> same_as<typename G::move_t>;
        { player.getTimeout() } -> same_as<double>;
        { player.getParity() } -> same_as<int>;
    };

    template <class T, class G>
    concept IntelligentPlayer = Player<T, G> && requires(T player, G game) {
        { player.heuristic(game) } -> same_as<int>;
    };

We employ template programming to specify to the game dev what functionality their player `T` needs to support in order to be hooked up to our AI framework. To use our AI algorithms, the game dev simply needs to add one additional function on top of the base three functions that any (intelligent or non-intelligent) player needs in order to be hooked into our game framework.

Note that a player is defined with respect to a constrained game that must be `Playable`. This means that a player can use any of the functions requested by `Playable` when implementing their strategy and heuristic functions:

    template <class G>
    concept Playable = requires(G m, G::move_t mv, ostream& os) {
        typename Config<G>;
        { m.isTerminal() } -> same_as<bool>;
        { m.isWinner() } -> same_as<bool>; 
        { m.getTurnCount() } -> same_as<int>;
        { m.getTurnParity() } -> same_as<int>;
        { m.getAvailableMoves() } -> same_as<vector<typename G::move_t>>;
        { m.makeMove(mv) } -> same_as<void>;
        { m.isValid(mv) } -> same_as<bool>;
        { m.setup() } -> same_as<void>;
        { os << m };
        { os << mv };
    };

We provide the game dev with the option for an `IntelligentPlayer` to use (1) minimax with alpha beta pruning or (2) minimax with alpha beta pruning and iterative deepening via timeout. Minimax with alpha beta pruning decreases the number of states that need to be evaluated while ensuring that the optimal state is found. Minimax with iterative deepening adds an additional time constraint to the search of all possible states, which is important for maintaining playability in games with a large number of possible states. 

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

    template <class Function, class Model>
    concept Predicate = Checkable<Model> && requires(Function f, Model m) {
        { f(m) } -> same_as<bool>;
    };

I originally used `std::function<bool(const Model&)>` but found that that didn't work too well
whenever I used lambdas. I suppose the phase of the compiler that does template computations
happens before the phase were lambdas are typechecked to see if they can be converted to an
equivalent type.
