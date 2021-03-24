# AFG Notes and Psuedocode

## Objects in Minimax

There are several abstract objects in minimax:
1. Game
2. Game Manager
3. Player
4. Display

Game - the game itself. 

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

Game Manager - controls game, i.e. initializes game, enforces timing, etc. Interfaces with display.

    template <class game_type>
    class Manager {
        private:
            int time_limit; // Time limit for move
        
        public:
            game_type initialize_game(); // Initializes game		 
    }

Player - a player in the game who makes moves

    template <class player_type>
    class Player {
        public:
            player_type get_type(); // Maximizing or minimizing player
    }


Display - handles game "graphics"

    template <class display_type>
    class Display {
        public:
            void display_state(game_type state);
    }


## Minimax Algorithm

The minimax algorithm requires:
1. A game with moves that have some value (heuristic)
2. A notion of depth - this should respect the essence of the algorithm (traversing a tree)
3. Two players


    minimax(Game<game_type> game, int depth, player_type player) {
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

Can we extract pruning further away from the core minimax algorithm?


    minimax_ab(Game<game_type> game, int depth, int alpha, int beta, player_type player) {
        if game.game_over() { 
            return game.heuristic();
        }
        
        moves = get_possible_moves(); 
        if (player is max) {
            val = -infinity
            for (move : moves) {
                val = max(val, minimax(move, depth-1, min));
            }
	    alpha = max(alpha, val);
 	    if (alpha >= beta) {
	        break;
	    }
            return val;
        }		
        else {
            val = infinity;
            for (move : moves) {
                val = min(val, minimax(move, depth-1, max));
            }
            beta = min(beta, val);
	    if (beta <= alpha) {
	        break;
	    }
	    return val;
        }
    }
