#ifndef AMAZONS_HPP
#define AMAZONS_HPP

#include <vector>
#include "board.hpp"
#include "game.hpp"

using namespace std;

struct Amazons;

template<>
struct Config<Amazons>
{
    int width;
};

struct Amazons {
    using move_t = int;
};


#endif