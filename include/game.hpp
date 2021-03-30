#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>
#include "config.hpp"

using namespace std;

/* template <class T> */
/* concept configurable = */
/*     requires { */
/*         typename Config<T>; */
/*     }; */


template <class GameType, class Player1Type, class Player2Type>
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
        /* } */

        void play() {
            /* initialize(); */
            while (!state.isTerminal())
            {
                cout << "[ Turn " << state.getTurnCount() << " ] Player " << state.getCurrentPlayer() << " make a move!" << endl;
                state.print();
                move_t action = (state.getCurrentPlayer()) ? p1.getStrategy(state) : p2.getStrategy(state);
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
