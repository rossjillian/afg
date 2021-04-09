Manual
======

Game
----
The `afg::game` namespace contains three concepts `Playable`, `Player`, and
`IntelligentPlayer` and one generic two player game class `TPGame`.

### Playable	
This concept specifies what is necessary for a game `G` to be playable in our
library. We require that the game `G` and the generic move of the game `G` needs
`operator<<` in order for the game to communicate with standard output.

     template <class G>
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

### Player
This concept specifies what is necessary for a player to participate in a game
that uses our library. We require that the player `T` has some sort of strategy
to  choose a move (it does not necessarily have to be a good strategy!), that
the player has a timeout, and that the player knows what order it plays.

    template <class T, class G>
    concept Player = requires(T player, G game) {
        Playable<G>;
        { player.getStrategy(game) } -> same_as<typename G::move_t>;
        { player.getTimeout() } -> same_as<double>;
        { player.getParity() } -> same_as<int>;
    };

### IntelligentPlayer
This concept builds upon our `Player` concept and also requires a heuristic
function. This is important if we want `getStrategy` to be intelligent and use
the algorithms given by `afg::AI`.

    template <class T, class G>
    concept IntelligentPlayer = Player<T, G> && requires(T player, G game) {
        { player.heuristic(game) } -> same_as<int>;
    };

### TPGame
The `TPGame` class is an abstraction of a two player game. We require the game
to be `Playable` and to have two `IntelligentPlayer`s. 

    template <Playable GameType, IntelligentPlayer<GameType> Player1Type, IntelligentPlayer<GameType> Player2Type>
    class TPGame 

In `TPGame`, we provide a `play` function. This function prints to standard
output instructions on whose player it is and execute their strategy. It also
enforces a timeout and ensures that the moves each player cast are valid. Once
there is a winner or draw in the game, the function prints the outcome to standard output and terminates. All of this functionality is built in by simply
enforcing the `Playable` and `IntelligentPlayer` concepts.

    void play();

Players
-------
The `afg::players` namespace contains two generic player classes `HumanPlayer`
and `SmartPlayer`. 

### Human Player
We provide a generic `HumanPlayer`, which accepts the player's move from
standard input. It contains all of the functions required by the `Player` and
`IntelligentPlayer` concepts defined in `afg::game`, which means that it can be
easily plugged into other parts of our library.

    template <Playable GameType>
    class HumanPlayer 

A `HumanPlayer` gets their move by calling `getIOMove()`, a function from
`afg::strategy` which we will describe in the Strategy section of this manual.

### Smart Player
We also provide a generic `SmartPlayer`, which determines the player's move from
the minimax algorithm. Like `HumanPlayer`, `SmartPlayer` contains all of the
functions required by the `Player` concept defined in `afg::game`, which means
that it can be easily plugged into other parts of our library. However, the
`heuristic` function required by the `IntelligentPlayer` concept defined in
`afg::game` still needs to be implemented by the game developer. We do this
because the choice of the heuristic function is game-specific.

    template <Playable GameType>
    class SmartPlayer 

A `SmartPlayer` gets their move by calling `getMinimaxMove()`, a function from
`afg::strategy` which we will describe in the Strategy and Artificial
Intellligence sections of this manual.

Strategy
--------
The `afg::strategy` namespace contains four utilities `getRandomMove()`, `getIOMove()`, `getMinimaxMove()`, and `getIterativeMove()`.

### Random Move
This function takes in a generic game state and picks a random valid move. The
function is seeded using `std::chrono:system_clock::now().time_since_epoch()`,
which ensures randomness between runs.

    template <Playable GameType>
    typename GameType::move_t getRandomMove(const GameType& state)

### IO Move
This function takes in a move from standard input and puts it into the generic
game move `GameType::move_t`.

    template <Playable GameType>
    typename GameType::move_t getIOMove(const GameType& state)

### Minimax Move
This function is a wrapper function that calls `minimax()` from `afg::AI`.

    template <Playable GameType, IntelligentPlayer<GameType> P>
    typename GameType::move_t getMinimaxMove(const GameType& state, P player)

### Iterative Move
This function is a wrapper function that calls `iterativeDeepening()` from `afg::AI`.

    template <Playable GameType, IntelligentPlayer<GameType> P>
    typename GameType::move_t getIterativeMove(const GameType& state, P player)

Artificial Intelligence
-----------------------
The `afg::AI` namespace contains two utilities `minimax()` and
`iterativeDeepening()`, in additoin to three helper utilities `minimizer()`,
`maximizer()`, and `minimaxIterative`.

### Minimax
This function is the foundation of our game AI code. The minimax algorithm is a
recursive algorithm that return the next best move for a player to make in a
game. 
    
    template<Playable GameType, IntelligentPlayer<GameType> P>
    GameType::move_t minimax(const GameType& state, P player, int depth) {

The algorithm requires the `IntelligentPlayer` concept.

We automatically include alpha beta pruning in our base minimax implementation.
This is because alpha beta pruning retains the optimality guarantee while
speeding up execution time.

### Iterative Deepening
This function extends the minimax code to include a time component: the
algorithm will iteratively search deeper and deeper down the search tree until
the time limit is up. This algorithm is useful to use instead of our base
minimax if the game's search space is large.

    template<Playable GameType, IntelligentPlayer<GameType> P>
    GameType::move_t iterativeDeepening(const GameType& state, P player, int depth, double limit=0.5)

Model
-----
The `afg::model` namespace contains two concepts (`Checkable` and `Predicate`)
along with two utilities `bfsFind()` and `pathExists()`.


### Checkable
This concepts specifies an interface for what constitutes a searchable state. In
addition to methods needed to expand the search space, we also need `operator==`
and `hash<T>` in order to hash the state object into data structures used in the
state traversal algorithms.

    template <class T>
    concept Checkable = requires(T m, T other, T::move_t mv) {
        { m.isTerminal() } -> same_as<bool>;
        { m.getTurnCount() } -> same_as<int>;
        { m.getAvailableMoves() } -> same_as<vector<typename T::move_t>>;
        { m.makeMove(mv) } -> same_as<void>;
        { m == other } -> same_as<bool>;
        { hash<T>{}(m) } -> same_as<size_t>;
    };

Here we see that the checkable class `T` must provide a typename `move_t`
representing the type of a move which, when passed to `makeMove()`, takes a
state and transforms it into one of its neighboring state.

`isTerminal(), getTurnCount(), getAvailableMoves()` are used to detect a leaf
node, the depth, and the neighbors in the search space, respectively.


### Predicate
This concept is meant to constrain a function object for typechecking purposes.
A predicate is a function object implemented by the user of the library that
takes in a state and says whether or not it's a goal that they were looking for.

    template <class Function, class Model>
    concept Predicate = Checkable<Model> && requires(Function f, Model m) {
        { f(m) } -> same_as<bool>;
    };

A lambda that takes in a `const Model&` and returns `bool` will sastisfy this
concept.

### SearchResult
A simple wrapper struct over a few fields that describe the results of a
goal-based BFS search.

    template<Checkable GameType>
    struct SearchResult {
        bool success;
        int explored;
        vector<GameType> matches;
    };

`success` indicates whether any state visted satisfied the predicate. `explored`
indicates how many state were visited. `matches` is a vector containing all
states that matched the predicate.

### bfsFind()
This is the fundamental function for performing model checking. It performs a
simple goal-based breadth-first search through the state space. For any state it
encounters that satisfies `isGoal()`, it will add the state to the
`SearchResult.matches`.

    template<Checkable GameType, Predicate<GameType> Function>
    SearchResult<GameType> bfsFind(GameType initState,
                                   Function isGoal,
                                   int depthLimit)

One additional note – `depthLimit` is here to enforce a bound on the search
space. Even for simple games, the space can quickly grow on the order of
`O(2^d)` which will bring down the runtime. Having a depth limit also helps
tests certain game scenarios (e.g. can we reach this move within `d` moves?).

### pathExists()
There are times where one desires to check the existence of several states in
sequence – a scenario. For this, we use `pathExists()`, which essentially chains
together calls to `bfsFind()` until the final predicate in `predicates` is
satisfied.


    template<Checkable GameType, Predicate<GameType> Function>
    bool pathExists(const GameType& initState,
                    const vector<Function>& predicates,
                    int depthLimit);

`depthLimit` is meant to be cumulative for the entire scenario search. That is,
if the first predicate is satisfied at depth `d`, then the remaining predicates
must be satisfied within `depthLimit - d` turns.  Unlike `bfsFind()`,
`pathExists()` is not necessarily an exhaustive search. It uses backtracking in
order to find the shallowest solution first. In other words, `pathExists()`
starts looking for `predicate[i + 1]` once `predicate[i]` is satisfied. It does
not wait until it finds all states that satisfy `predicates[i]` before searching
for all states that satisfy `predicates[i + 1]`.
