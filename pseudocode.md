# AFG Notes and Psuedocode

## Objects in Minimax

There are several abstract objects in minimax/game abstract:
1. Game State
   - Representation of the game (e.g. matrix, bitstring, etc)
   - Given the current state, you should be able to tell who won/who is winning/game over
   - There should be a concept of neighbors. Given the state, what are all possible moves that can come next? (Dependent on player)
2. Game Manager
   - Main driver for the program
   - Handles state creation, switching turns, calling display stuff
3. Player
   - Given a the game state and some internal player logic, we should be able to compute ALL possible moves
4. Display
   - Straightforward, probably not something we need to concern ourselves with.

The classes we define should serve as a model that game devs can easily plug into. With these classes, we can define what we, the library devs, need in order to implement minimax for them.

GameState - the internal representation of the game

    template <class game_type>
    class GameState {
        private:
            game_type state; // Could be array (TTT), bitstrings (Connect 4), etc.
        
        public:
            //bool is_terminal() {
            //    return state.is_terminal();
            //}
        
            // Let's instead use concepts to enforce that game_type is comparable(?), and has a function 
            // is_terminal()

            game_type get_state() {
                return state
            }

            // int heuristic(); // Heuristic evaluation of game state
            // I don't think the heuristic should be attached to the state. It'd be more
            // interesting if it could be something that could be plugged in and swapped out as
            // needed.
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

    template <class game_type>
    class Player {
        private:
            vector<game_type> get_moves(game_type state); // This gets passed in via the
            player_type ty; // Enum? MIN/MAX
            // constructor

        public:
            player_type get_type(); // Maximizing or minimizing player, define player_type as //// min or max
            vector<game_type> valid_moves(game_type state) {
                return get_moves(state);
            }
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

Some code
   
    template <class game_type>
    class Minimax {
        private:
            game_type initial_state;
            // Player<game_type> max; // Can this just be reduced to a function object?
            // Player<game_type> min; // Don't we just care about these players' possible moves
            vector<game_type> get_moves_max(game_type state);
            vector<game_type> get_moves_max(game_type state);
            Comparable eval(game_type state);

            int depth; // We should implement IDS with a timeout
        public:
            do_minimax(game_type state, int current_depth, player_type player) {
                if state.is_terminal() { 
                    return eval(state);
                }
                
                if (player is max) {
                    moves = get_moves_max(state)
                    val = -infinity
                    for (move : moves) {
                        val = max(val, minimax(move, depth-1, min));
                    }
                    return val;
                }		
                else {
                    moves = get_moves_min(state)
                    val = infinity;
                    for (move : moves) {
                        val = min(val, minimax(move, depth-1, max));
                    }
                    return val;
                }
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
