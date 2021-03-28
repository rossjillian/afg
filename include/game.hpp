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
class Game {

    using game_t = GameType;
    using p1_t = Player1Type;
    using p2_t = Player2Type;

    private:
        game_t state;
        Config<game_t> config;
        p1_t p1;
        p2_t p2;
        int currentPlayer;

    public:
        /* static_assert(has_config<gametype>); */
        Game(Config<game_t> config, p1_t player1, p2_t player2)
            : state(config),
              p1(player1),
              p2(player2),
              currentPlayer(0)
        { }

        void initialize() {
            /* state.apply(configs); */
        }

        void play() {
            /* initialize(); */
            while (!state.isTerminal())
            {
                cout << "Player " << currentPlayer << " make a move!" << endl;
                state.print();
                int action = (currentPlayer) ? p1.getStrategy(state) : p2.getStrategy(state);
                state.makeMove(action, currentPlayer);
                currentPlayer ^= 1;
            }

            state.print();
            if (state.isWinner())
            {
                currentPlayer ^= 1;
                cout << "Player " << currentPlayer << " wins!" << endl;
            } else {
                cout << "It's a draw!" << endl;
            }
        }

};

#endif
