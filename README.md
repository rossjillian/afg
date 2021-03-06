afg: AI for Games
=================

Table of Contents
-----------------
- [afg: AI for Games](#afg-ai-for-games)
  - [Table of Contents](#table-of-contents)
  - [Overview](#overview)
    - [Game Abstractions](#game-abstractions)
    - [Adversarial Artificial Intelligence](#adversarial-artificial-intelligence)
    - [Model Checking](#model-checking)
  - [Design Choices](#design-choices)
    - [Intuitive Components](#intuitive-components)
    - [Compile-time Polymorphism](#compile-time-polymorphism)
  - [Installation](#installation)
  - [Tutorial](#tutorial)
    - [Game](#game)
    - [AI](#ai)
    - [Model Checking](#model-checking-1)
  - [Benchmarks](#benchmarks)
  - [Manual](#manual)
  - [Contributors](#contributors)

Overview
--------
afg is a template library that aims to make game development in C++ more
enjoyable and feasible. It offers powerful code abstractions from the fields of
game development, adversarial AI, and model checking to enable game devs to
write games from scratch faster with rich player and testing functionality. afg
embraces compile-time polymorphism and presents a range of concepts for users to
satisfy as opposed to offering abstract base classes for run-time polymorphism.
Combined with modern C++ features, these design principles are meant to
encourage developers to learn and try to use these elegant C++ constructs in
their own implementations!

### Game Abstractions
Game devs should simply focus on implementing their own game-specific mechanics
and not waste time on boilerplate code. All simple two-player adversarial games
share the same mechanics in the end – there is a notion of moves, players, and
updating the game state based on the results of the moves those players make.
afg acts as the game driver and simply asks the game dev to provide the game
mechanics.

### Adversarial Artificial Intelligence
Not all games involve human players. afg wants to impower game devs to offer
interesting game mechanics by providing the necessary functionality to have AI
players to compete against. Of course, we can't expect all game devs to be
familiar with adversarial AI, so we instead offer implementations of these
algorithms for the game dev to seamlessly plug into their game implemenation! We
mainly focused on implementing Minimax and some of its variations.

### Model Checking
Finally, game devs need a way to assert the validity of their implementation.
Have they covered all edge cases and winning conditions? It would be infeasible
for the game dev to have to manually play out the game to reach all of these
cases to see if they implementated them correctly. afg solves this issue by
providing simple model checking tools for the game dev to use! Through simple
predicate-based BFS, game devs will be able to concisely write validity test for
their game mechanics.

Design Choices
--------------
### Intuitive Components
After implementing a few games ourselves, we studied the code and figured out
what pieces of the games can be considered as "boilerplate" and therefore
abstracted away. We also studied the components that make up a game and used
them to implement concepts for Game and Player.

### Compile-time Polymorphism
When abstracting away functionality, one may choose to use virtual classes to
offer a sort of "skeleton" code for the user to extend. While the OO approach
certainly has its use-cases, the penalty of run-time polymorphism is noticable.
In afg, we chose to avoid virtual classes in favor of templates, as to validate
the polymorphism during compile-time. This yields faster runtime and also means
we can take advantage of C++20's Concepts for better type-checking!

Installation
------------
Since afg is a header-only template library, there isn't anything to build! Just
pass the compiler flag `-I<path>` when building your game to include the path to
`afg/include`.

afg requires some C++20 support (mainly for concepts). See
[here](https://en.cppreference.com/w/cpp/compiler_support) if you are unsure if
your system's compiler will support afg. `clang++-10` or `g++-10` are
sufficient.

Tutorial
--------

### Game
Let's say we wanted to use afg's game abstractions to implement a simple
command-line TicTacToe. We'll first create a TicTacToe struct that complies with
the requirements of an afg game. That is we must have the functions:
* `bool isTerminal()` - this function should return whether the game has reached
  a terminal state - for example if someone has won or a tie was reached.
* `bool isWinner()` - similar, but only for winners
* `int getTurnCount()` - this function should return how many turns into the
  game we are
* `int getTurnParity()` - should simply return which player's turn it is
* `void makeMove(mv)` - this function should change whatever internal state you
  are using to keep track of the game and make the given move
* `void isValid(mv)` - this function should check whether a given move is valid
* `void setup()` - whatever you want to run at the beginning of the game
  (potentially instructions, etc) should go here

The implementations of most of these functions are straightforward. We'll focus
on `isValid()`, `makeMove()` and `isWinner()`. For the sake of our TicTacToe
game, we will create a data structure called a board, which is a wrapper on a
vector of vectors of chars which we'll refer to as a grid. In
[TicTacToe/board.cpp](TicTacToe/board.cpp) we implemented a bunch of functions
We'll need like some functions to print a TicTacToe board on the command line.
We also implement the `isValid()` function:

```
bool Board::isValid(int move) const
{
   int max = numTiles - 1;
   if (move > max)
      return false;

   int row = move / board.size();
   int col = move % board.size();

   return board[row][col] == ' ';
}
```

which just checks that a proposed move is within the bounds of the board and is
on an empty square. 

And we implement the `makeMove()` function:

```
void Board::makeMove(int move, int turn, Grid& board){
   int row = move / board.size();
   int col = move % board.size();
   if (isValid(move))
      board[row][col] = turn ? 'x' : 'o';
}
```

which checks if a move is valid, and if so, changes the symbol in that square to
the appropriate one given which player's turn it is. 

Finally, we implement an `isWinner()` function:

```
bool Board::isWinner() const
{
   return checkRows() || checkColumns() || checkDiagonals();
}
```

which employs three helper function to check if someone has won on the rows,
columns or diagonals. 

Once we've written these functions, we simply wrap them in functions in our
TicTacToe struct, and we satisfy the constraints of an afg game. Then our
TicTacToe game looks very simple:

```
int main(int argc, char **argv)
{
   HumanPlayer<TicTacToe> p1(0);
   HumanPlayer<TicTacToe> p2(1);

   TicTacToe ttt(3);

   TPGame<TicTacToe, HumanPlayer<TicTacToe>, HumanPlayer<TicTacToe>> game(ttt, p1, p2);

   game.play();

   return 0;
}
```

Note that we provide two basic players, `HumanPlayer` and `IntelligentPlayer`.
`HumanPlayer` can be used out-of-the-box and does not require any additional
coding on the part of the game developer. Using `HumanPlayer`, the game accepts
moves from standard input on the command line. All of the looping and setup for
the game itself is done by afg (using the functions we wrote). The final game
looks like:

```
Refer to moves using the following chart: 
0 | 1 | 2
------------
3 | 4 | 5
------------
6 | 7 | 8
   |   |  
------------
   |   |  
------------
   |   |  

[ Turn 0 ] Player 0 make a move!
Tile #: 4
   |   |  
------------
   | o |  
------------
   |   |  

[ Turn 1 ] Player 1 make a move!
Tile #: 3
   |   |  
------------
 x | o |  
------------
   |   |  

[ Turn 2 ] Player 0 make a move!
Tile #: 5
   |   |  
------------
 x | o | o
------------
   |   |  

[ Turn 3 ] Player 1 make a move!
Tile #: 7
   |   |  
------------
 x | o | o
------------
   | x |  

[ Turn 4 ] Player 0 make a move!
Tile #:
```

And so on...

The full code for TicTacToe can be found [here](TicTacToe/).
We implemented this game for grids of all sizes, too!

### AI

Now that you have your game set up, you probably want to make it a bit more
interesting! This is where our AI library comes in. We provide you with a
minimax implementation with alpha-beta pruning and a minimax implementation with
alpha-beta pruning and iterative deepening. You should consider using our
implementation with iterative deepning if the state space of your game is
particularly large.  

      afg::AI::minimax(state, player, depth);

Here, `state` is just a `const GameType&`, which is the `GameType` you
implemented previously.

In Game, you have to enforce the `Player` concept; this is alreay done for you
in the provided `HumanPlayer` and `SmartPlayer`. To use our AI functions, you
have to additionally enforce the `IntelligentPlayer` concept, which requires an
additional function called the `heuristic` function. The heuristic function is
game-specific and is the evaluation of a state; it is up to you as the game
developer to define. All that we require is that the heuristic function should
return an integer.

In our TicTacToe implementation, you can see that we have implemented a very
simple heuristic function. This heuristic function takes advantage of the zero
sum nature of TicTacToe (so each player can maximize its own score).
  
      template<>
      int SmartPlayer<TicTacToe>::heuristic(const TicTacToe& state) {
          if (state.isWinner()) {
              if (this->getParity() == state.getTurnParity())
                  return MAXIMIZER;
              else
                  return MINIMIZER;    
          }
          return NEUTRAL;
      }

### Model Checking
With TicTacToe pretty much implemented, you may now wish to write
code that will verify your implementation. You may also wish to explore some
scenarios in the game but don't want to sit down and manually play the game to
reach those scenarios. For testing and playing out scenarios, we now arrive to
the final component of afg – model checking!

See [TicTacToe/model-check.cpp](TicTacToe/model-check.cpp) for the full code.

We must first make sure that TicTacToe satisfies the `afg::model::Checkable`
concept. There's a lot of overlap with `afg::game::Playable`, except we'll also
have to implement `std::hash<TicTacToe>` and `operator==` for TicTacToe. This is
so the game state can be hashed into data structures used by the model checking
algorithms.

Once that's out of the way, we're ready to implement some simple model checking
for TicTacToe! Let's choose two simple scenarios (predicates) to search for.

First, let's find a game board that looks like this:

      o | o | ?
    -------------
      ? | o | ?
    -------------
      ? | ? | ?

That is, there must be `o`'s in those three slots, but all the other slots don't
matter. We can verify that at least one state like this exists by running

      auto res = afg::model::bfsFind(ttt, threeOs, 10);

Here, `ttt` is the initial state for TicTacToe, `10` is the depth limit, and
`threeOs` is a lambda that returns `true` if it sees a state that matches the
one above.

      auto threeOs = [](const TicTacToe& st) {
          return (st.b.board[0][0] == 'o'
                  && st.b.board[0][1] == 'o'
                  && st.b.board[1][1] == 'o');
      }

We now define one more predicate to test if the `o`-player won:

      auto oWon = [](const TicTacToe& st) {
          return st.b.isWinner() && (st.getTurnParity() == 0); 
      }

With these two predicates, we can define a search to see if a path exists where
we first reach a board configuration specified by `threeOs` and then go on to
see the `o`-player win the game. By specifying a depth limit, we can find the
minimum number of turns required to see this scenario happen. After putting the
two predicates in a vector, we then call

      bool exists = afg::model::pathExists(ttt, predicates, 7);

This line of code will see if the two predicates can happen within 7 moves.

The goal-based BFS searches are simple, but powerful tools when it comes to
model checking complex game states. They make for great testing too!

Benchmarks
----------
See [here](docs/benchmarks.md) for more details. At a high-level, we made sure
that we were not incurring overhead by mandating that a user hook in with our
abstractions instead of just implementing everything themselves. Surely enough,
afg follows through with the C++ principle of "Zero Cost Abstraction"!

Manual
------
For in-depth documentation of afg, see [here](docs/manual.md)

Contributors
------------
- [Hollis Lehv](https://github.com/hlehv)
- [Hans Montero](https://github.com/hmontero1205)
- [Jillian Ross](https://github.com/rossjillian)
  
We made this for our final project in [Bjarne
Stroustrup](https://www.stroustrup.com/)'s Design Using C++ course at Columbia
University.

We drew inspriation from some of our previous coursework at Columbia, including:
- cs4701 Artificial Intelligence – for our implementations of adversarial AI
  (Minimax algorithm)
- cs4113 Distributed Systems – for our use of model checking in asserting
  correctness of game mechanics
