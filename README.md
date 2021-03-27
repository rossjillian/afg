# afg: AI for Games

The minimax algorithm can be used to implement an AI that plays basic multi-agent games like chess, checkers, and tic-tac-toe. We are looking to provide a library that allows game developers to easily incorporate the minimax algorithm and its adjacent algorithms into their games. Much like ML libraries such as OpenAI Gym, we hope to abstract away the gritty computations involved in implementing the minimax algorithm by providing a set of abstract classes and tools for game developers to work with. If all of these virtual classes can be implemented, then they will have access to AI algorithms without having to implement them themselves. Furthermore, our library will offer simple model-checking capabilities to the game developer for asserting the correctness of their game logic and testing the reachability of given game states.


TODO
====

- TicTacToe string representation and put-to operator
- Implement MinimaxPlayer for TTT
- Be more constsious of const&
- Game::PrintInstructions
- Abstract away need for terminal
- Implement abstract Game and Player 
