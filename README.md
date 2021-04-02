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
  - [Quick Guide](#quick-guide)
  - [Examples](#examples)
  - [Benchmarks](#benchmarks)
  - [Contributors](#contributors)

Overview
--------
afg aims to make game development in C++ more enjoyable and feasible. By
offering powerful code abstractions from the fields of game development,
adversarial AI, and model checking, afg enables game devs to write games from
scratch faster with rich functionality.

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

Quick Guide
-----------
todo

Examples
--------
todo: Walkthrough of TTT

Benchmarks
----------
todo

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
