#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>
#include "config.hpp"

using namespace std;

template <class T>
concept Playable = requires(T m, T::move_t mv) {
        typename Config<T>;
        { m.isTerminal() } -> same_as<bool>;
        { m.isWinner() } -> same_as<bool>;
        { m.getTurnCount() } -> same_as<int>;
        { m.getCurrentPlayer() } -> same_as<int>;
        { m.getAvailableMoves() } -> same_as<vector<typename T::move_t>>;
        { m.makeMove(mv) } -> same_as<void>;
};


template <Playable GameType, class Player1Type, class Player2Type>
class TPGame {

    using game_t = GameType;
    using move_t = typename GameType::move_t;
    using p1_t = Player1Type;
    using p2_t = Player2Type;

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

        /* void initialize() { */
        /*     state.apply(configs); */
                /* state.setup() */
        /* } */

        void play() {
            /* initialize(); */
            while (!state.isTerminal())
            {
                cout << "[ Turn " << state.getTurnCount() << " ] Player " << state.getCurrentPlayer() << " make a move!" << endl;
                state.print();
                move_t action = (state.getCurrentPlayer()) ? p2.getStrategy(state) : p1.getStrategy(state);
                state.makeMove(action);
            }

            state.print();
            if (state.isWinner())
            {
                cout << "Player " << state.getWinner() << " wins!" << endl;
            } else {
                cout << "It's a draw!" << endl;
            }
        }

};

#endif
