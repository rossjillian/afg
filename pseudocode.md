# AFG Notes and Psuedocode

## Objects in Minimax

There are several abstract objects in minimax:
1. Game
2. Game Manager
3. Player
4. Display

Game - the game itself

    template <class game_type>
    class Game {
        private:
            game_type state; // Could be array (TTT), bitstrings (Connect 4), etc.
    
        public:
            game_type get_state(); // Gets current game state
            bool check_move(); // Checks if move is valid
            bool play_move(); // Plays move and updates state
            bool check_winner(); // Checks if state is a winner
            bool game_over(); // Checks if game is over
            int heuristic(); // Heuristic evaluation of game state
            
    }

Game Manager - controls game, i.e. initializes game, enforces timing, etc.

    class Manager {
        
    }

Player - a player in the game who makes moves

    class Player {
    
    }


Display - handles game "graphics"

    class Display {
    
    }


## Minimax Algorithm

The minimax algorithm requires:
1. a game with moves that have some value (heuristic)
2. a notion of depth
3. two players


    minimax(Game<game_type> game, int depth, player) {
        if game.game_over() { 
            return game.heuristic();
        }
        
        moves = get_possible_moves(); 
        if (player is max) {
            val = -infinity
            for (move : moves) {
                val = max(val, minimax(move, depth-1, min));
            }
            return val;
        }		
        else {
            val = infinity;
            for (move : moves) {
                val = min(val, minimax(move, depth-1, max));
            }
            return val;
        }
    }


Based on this psuedocode, we need a generic notion of:
1. The base case - when the game is over
2. Moves in a game
3. Heuristic value - does not necessarily need to be an int; should be comparable (need concepts)

## Optimizations

Alpha-Beta Pruning
