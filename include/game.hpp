#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>
#include <chrono>
#include "config.hpp"

using namespace std;
using namespace chrono;

template <class T>
concept Playable = requires(T m, T::move_t mv) {
        typename Config<T>;
        { m.isTerminal() } -> same_as<bool>;
        { m.isWinner() } -> same_as<bool>;
        { m.getTurnCount() } -> same_as<int>;
        { m.getCurrentTurn() } -> same_as<int>;
        { m.getAvailableMoves() } -> same_as<vector<typename T::move_t>>;
        { m.makeMove(mv) } -> same_as<void>;
        { m.isValid(mv) } -> same_as<bool>;
        { m.setup() } -> same_as<void>;
};

/*
template <class T, class G>
concept Player = requires(T player, G game) {
    Playable<G>;
    { player.getStrategy(game) } -> same_as<typename G::move_t>;
    { player.getTimeout() } -> same_as<double>;
    { player.getTurnOrder() } -> same_as<int>;
};
*/

template <class T>
class Player {
    public:
        Player(int o, double t = 0.0) : timeout(t), turnOrder(o) {} 
        typename T::move_t getStrategy(const T& state) { return state.getAvailableMoves()[0]; }
        double getTimeout() const { return timeout; }
        int getTurnOrder() const { return turnOrder; }
    private:
        double timeout;
        int turnOrder;
};

template <Playable GameType>
class TPGame {
    using game_t = GameType;
    using move_t = typename GameType::move_t;
    using p1_t = Player<GameType>;
    using p2_t = Player<GameType>;

    private:
        game_t state;
        Config<game_t> config;
        p1_t p1;
        p2_t p2;

    public:
        /* static_assert(has_config<gametype>); */
        TPGame(Config<game_t> config, p1_t player1, p2_t player2)
            : state(config),
              p1(player1),
              p2(player2)
        { }

        void play() {
            state.setup();

            while (!state.isTerminal())
            {
                cout << "[ Turn " << state.getTurnCount() << " ] Player " << state.getCurrentTurn() << " make a move!" << endl;
                state.print();
                double timeout = (state.getCurrentTurn()) ? p2.getTimeout() : p1.getTimeout();
                auto t0 = high_resolution_clock::now();
                move_t action = (state.getCurrentTurn()) ? p2.getStrategy(state) : p1.getStrategy(state);
                auto t1 = high_resolution_clock::now();

                if (timeout && duration_cast<seconds>(t1 - t0) > duration_cast<seconds>(duration<double>(timeout))) {
                    cout << "Player " << state.getCurrentTurn() << " exceeded their time limit!" << endl;
                    cout << "Player " << (state.getCurrentTurn() ^ 1) << " wins!" << endl;
                    return;
                }

                if (state.isValid(action))
                {
                    state.makeMove(action);
                } else {
                    cout << "Invalid move" << endl;
                }
            }

            state.print();
            if (state.isWinner())
            {
                cout << "Player " << state.getWinningTurn() << " wins!" << endl;
            } else {
                cout << "It's a draw!" << endl;
            }
        }

};

#endif
