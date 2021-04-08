#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>
#include <chrono>
#include "config.hpp"

using namespace std;
using namespace chrono;

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

template <Playable GameType, IntelligentPlayer<GameType> Player1Type, IntelligentPlayer<GameType> Player2Type>
class TPGame {
    using game_t = GameType;
    using move_t = typename GameType::move_t;
    using p1_t = Player1Type;
    using p2_t = Player2Type;

    private:
        game_t state;
        p1_t p1;
        p2_t p2;

    public:
        /* static_assert(has_config<gametype>); */
        TPGame(game_t game, p1_t player1, p2_t player2)
            : state(game),
              p1(player1),
              p2(player2)
        { }

        void play() {
            state.setup();

            while (!state.isTerminal())
            {
                cout << "[ Turn " << state.getTurnCount() << " ] Player " << state.getTurnParity() << " make a move!" << endl;
                cout << state << endl;
                double timeout = (state.getTurnParity()) ? p2.getTimeout() : p1.getTimeout();
                auto t0 = high_resolution_clock::now();
                move_t action = (state.getTurnParity()) ? p2.getStrategy(state) : p1.getStrategy(state);
                auto t1 = high_resolution_clock::now();

                if (timeout && duration_cast<seconds>(t1 - t0) > duration_cast<seconds>(duration<double>(timeout))) {
                    cout << "Player " << state.getTurnParity() << " exceeded their time limit!" << endl;
                    cout << "Player " << (state.getTurnParity() ^ 1) << " wins!" << endl;
                    return;
                }

                if (state.isValid(action))
                {
                    state.makeMove(action);
                } else {
                    cout << "Invalid move" << endl;
                }
            }

            cout << state << endl;
            if (state.isWinner())
            {
                cout << "Player " << state.getTurnParity() << " wins!" << endl;
            } else {
                cout << "It's a draw!" << endl;
            }
        }

};

#endif
