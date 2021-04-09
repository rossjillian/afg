Design Overview
===============
This document presents an in-depth design overview of the major components of
afg. Here we explain our rationale behind implementing these features and how we
went about it in C++.

A recurring theme throughout the library is that we chose to use templates as
opposed to virtual base classes so we can have compile-time polymorphism.
Templates allow us to have polymorphism like virtual classes, except the work
needed to make them possible is done during compile-time. To improve
typechecking, we employ C++20 Concepts to constrain our templates. Concepts are
also great for documentation and present a clear interface to the library user.

Game
----
We supply boilerplate code for a game programmer that will setup the game, run the main
game loop, and keep track of game state, player turns, etc. For this, we require
that the game satisfy the `Playable` concept: 

```
concept Playable = requires(G m, typename G::move_t mv, ostream& os) {
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
```
The programmer defines these functions, and we use them to run the game logic.
Once the user has defined a struct that meets these requirements, the code to
actually play the game will look like:

```
    // Create two players for the game
    HumanPlayer<GameType> p1(0);
    SmartPlayer<GameType> p2(0);
    GameType gameType;

    TPGame<GameType, HumanPlayer<GameType>, SmartPlayer<GameType>> game(gameType, p1, p2);

    game.play();

    return 0;
```
The game programmer creates a concrete instance of their game struct to create a TPGame. Running
`game.play()` will run the game loop and will use the functions they implemented
to keep track of game state, interate across player turns and stop when the game
is over. 

The `play()` function first calls the `setup()` function defined by the game
programmer, and then begins a loop that terminates if the `isTerminal()`
function returns true - in other words whenever the game is over.

Within this loop, we prompt players to choose a move. We keep track of the time
allotted for both players and end the game if a player runs out of time. We keep
track of time using the chrono library:

```
double timeout = (state.getTurnParity()) ? p2.getTimeout() : p1.getTimeout();
auto t0 = high_resolution_clock::now();
move_t action = (state.getTurnParity()) ? p2.getStrategy(state) : p1.getStrategy(state);
auto t1 = high_resolution_clock::now();

if (timeout && duration_cast<seconds>(t1 - t0) > duration_cast<seconds>(duration<double>(timeout))) {
    cout << "Player " << state.getTurnParity() << " exceeded their time limit!" << endl;
    cout << "Player " << (state.getTurnParity() ^ 1) << " wins!" << endl;
    return;
}
```

We check the validity of a players' move using the `isValid()` function supplied
by the game programmer, and then make the move using the `makeMove()` function.
If we ever reach a terminal state, we check if there is a winner using
`isWinner()` and announce the winner if so. 

We found that adversarial games tend to follow a similar structure. Players make
moves on their turns, and as long as a move is valid, the state changes and the
turns are switched. When a state is reached such that someone has won or a tie
occurs, the game ends. With our library, players do not have to write this
repetitive code themselves, and can simply plug in the functions that they would
most likely write otherwise. We tried only to require functions that were
necessary for our boilerplate - only the most fundamental aspects of an
adversarial game. Input and output can be customized by the game programmer's
implementation of put-to and get-from operators. 

Using concepts rather than inheritance allows us to avoid run-time polymorphism,
so that we can upfront to compilation what might otherwise be done during
runtime. 

Artificial Intelligence
-----------------------
To employ a game player that uses AI algorithms like minimax, the game player
needs to have a heuristic function that evaluates state. Thus, in order for the
game dev to use minimax, we request a player that satisfies the constraints of
the `IntelligentPlayer` concept:

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

We employ template programming to specify to the game dev what functionality
their player `T` needs to support in order to be hooked up to our AI framework.
To use our AI algorithms, the game dev simply needs to add one additional
function on top of the base three functions that any (intelligent or
non-intelligent) player needs in order to be hooked into our game framework.

Note that a player is defined with respect to a constrained game that must be
`Playable`. This means that a player can use any of the functions requested by
`Playable` when implementing their strategy and heuristic functions:

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

We provide the game dev with the option for an `IntelligentPlayer` to use (1)
minimax with alpha beta pruning or (2) minimax with alpha beta pruning and
iterative deepening via timeout. Minimax with alpha beta pruning decreases the
number of states that need to be evaluated while ensuring that the optimal state
is found. Minimax with iterative deepening adds an additional time constraint to
the search of all possible states, which is important for maintaining
playability in games with a large number of possible states. 

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
    SearchResult<GameType> bfsFind(const GameType& initState,
                                   Function isGoal,
                                   int depthLimit);

`bfsFind()` is a depth-limited BFS search that traverses the state space. We
return a templatized `SearchResult` which contains some information about the
search – success, number of states explored, and a vector of matches. It's
important to enforce a depth limit for these kinds of searches given that
they're undirected.  The state space can, at times, expand exponentially every
turn which will slow down the run time. `depthLimit` is there to encourage the
programmar to think about what could be the shallowest depth they'll find their
solution at.


    template<Checkable GameType, Predicate<GameType> Function>
    bool pathExists(const GameType& initState,
                    const vector<Function>& predicates,
                    int depthLimit);

`pathExists()` essentially chains several `bfsFind()`s together by going through
the vector of predicates and successively applying them in a backtracking
search.  We would've liked to implement `bfsFind()` as a generator using
coroutines, but it seems that compiler support for coroutines is still very
experimental. Since `bfsFind()` is an exhaustive search, it is infeasible to use
directly in `pathExists()`, as we would like to greedily find states that satisfy
all the predicates instead of slowly finding all states that satisfy each
predicate. As such `pathExists()` is implemented similarly to `bfsFind()`,
except that it recurses once it finds a match in order to search searching for a
state that satisfies the next predicate.

Both `bfsFind()` and `pathExists()` are available as simple templated functions
in the `Model` namespace. No extra object creation required to use these
powerful functions.

The `Function` template parameter is constrained using the `Predicate` concept,
just for the sake of adding better typechecking to the function. It has to take
a state and return a bool, so that's what we mandate:

    template <class Function, class Model>
    concept Predicate = Checkable<Model> && requires(Function f, Model m) {
        { f(m) } -> same_as<bool>;
    };

We originally used `std::function<bool(const Model&)>` but found that that didn't
work too well whenever we used lambdas. I suppose the phase of the compiler that
does template computations happens before the phase were lambdas are typechecked
to see if they can be converted to an equivalent type.
