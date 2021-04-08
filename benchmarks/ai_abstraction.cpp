#include <iostream>

#include <chrono>

#include "ai.hpp"
#include "players.hpp"
#include "board.hpp"
#include "tictactoe.hpp"

using namespace std;
using namespace chrono;

class SmartPlayerTTT;
int minimaxTTT(const TicTacToe& state, SmartPlayerTTT player, int depth);

class SmartPlayerTTT {
    public:
        SmartPlayerTTT(int i, double t = 0.0)
            : parity(i), timeout(t)
        {}	

        int getStrategy(const TicTacToe& state) {
              return minimaxTTT(state, *this, MAX_DEPTH);
        }

	double getTimeout() {
            return timeout;
        }
        
        int getParity() {
            return parity;
        }

        int heuristic(const TicTacToe& state) {
            if (state.isWinner()) {
                if (this->getParity() == state.getTurnParity())
                    return MAXIMIZER;
                else
                    return MINIMIZER;    
            }
            return NEUTRAL;
        }
        
    private:
	int parity;	
        double timeout;
};

int minimizerTTT(TicTacToe& state, int& bestMove, SmartPlayerTTT player, int alpha, int beta, int depth);

int maximizerTTT(TicTacToe& state, int& bestMove, SmartPlayerTTT player, int alpha, int beta, int depth) {
    if (state.isTerminal() || depth == 0) 
        return player.heuristic(state);

    int val = numeric_limits<int>::min();
    vector<int> possibleMoves = state.getAvailableMoves();
    for (auto move : possibleMoves) {
        TicTacToe stateCopy = state;
        stateCopy.makeMove(move);
        int minimizerBestMove;
        int newVal = minimizerTTT(stateCopy, minimizerBestMove, player, alpha, beta, depth-1);
        if (newVal > val) {
	    val = newVal;
	    bestMove = move;
        }
        alpha = max(alpha, val);
        if (alpha >= beta)
	    break;
    }
    return val;
}

int minimizerTTT(TicTacToe& state, int& bestMove, SmartPlayerTTT player, int alpha, int beta, int depth) {
    if (state.isTerminal() || depth == 0) 
        return player.heuristic(state);

    int val = numeric_limits<int>::max();
    vector<int> possibleMoves = state.getAvailableMoves();
    for (auto move : possibleMoves) {
        TicTacToe stateCopy = state;
        stateCopy.makeMove(move);
        int maximizerBestMove;
        int newVal = maximizerTTT(stateCopy, maximizerBestMove, player, alpha, beta, depth-1);
        if (newVal < val) {
	    val = newVal;
	    bestMove = move;
        }
        beta = min(beta, val);
        if (beta <= alpha)
	    break;
    }
    return val;
}

int minimaxTTT(const TicTacToe& state, SmartPlayerTTT player, int depth) {
    int bestMove;
    int alpha = numeric_limits<int>::min(); 
    int beta = numeric_limits<int>::max();
    TicTacToe stateCopy = state;
    if (player.getParity() == 1) {
        maximizerTTT(stateCopy, bestMove, player, alpha, beta, depth);
    }
    else {
        minimizerTTT(stateCopy, bestMove, player, alpha, beta, depth);
    }
    return bestMove;
}
 
int main(int argc, char** argv) {
    int gameIterations = atoi(argv[1]);

    SmartPlayer<TicTacToe> p0(0);
    SmartPlayer<TicTacToe> p1(1);

    Config<TicTacToe> config {3};

    double totalElapsed = 0.0;
    for (int i = 0; i < gameIterations; i++) {
        TicTacToe state(config);
        while(!state.isTerminal()) {
            int action = (state.getTurnParity()) ? p1.getStrategy(state) : p0.getStrategy(state);
            auto t0 = high_resolution_clock::now();
            state.makeMove(action);
            auto t1 = high_resolution_clock::now();
            duration<float> elapsed = t1 - t0;
            totalElapsed += elapsed.count();
        }
    }

    cout << "Templated: " << totalElapsed << endl;

    SmartPlayerTTT p2(0);
    SmartPlayerTTT p3(1);

    double totalElapsedExplicit = 0.0;
    for (int i = 0; i < gameIterations; i++) {
        TicTacToe state(config);
        while(!state.isTerminal()) {
            int action = (state.getTurnParity()) ? p3.getStrategy(state) : p2.getStrategy(state);
            auto t0 = high_resolution_clock::now();
            state.makeMove(action);
            auto t1 = high_resolution_clock::now();
            duration<float> elapsed = t1 - t0;
            totalElapsedExplicit += elapsed.count();
        }
    }

    cout << "Explicit: " << totalElapsedExplicit << endl;
}

