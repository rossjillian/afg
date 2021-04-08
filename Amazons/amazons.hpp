#ifndef AMAZONS_HPP
#define AMAZONS_HPP

#include <vector>
#include "board.hpp"
#include "game.hpp"

using namespace std;

struct Amazons;

struct Amazons {
    using move_t = Move;
    Board b;
    int turnCount;

    Amazons()
        : b(),
        turnCount(0)
    {};

    bool isTerminal() const {
        return b.isWinner(getTurnParity());
    }

    int getTurnCount() const { return turnCount; }

    int getTurnParity() const { return turnCount % 2; }

    bool isWinner() const {
        return b.isWinner(getTurnParity());
    }

    void print() {
        b.print(false);
    }

    void makeMove(Move move)
    {
        b.makeMove(move, turnCount % 2);
        if (!b.isWinner(turnCount % 2 ))
            turnCount += 1;
    }

    bool isValid(Move move) {
        return b.isValid(move, getTurnParity());
    }

    void setup() {
        cout << "Refer to moves using the following chart: " << endl;
        b.print(true);
        cout << "Please specify the square of the queen you would like to move, "
        << "followed by the square you would like to move it to, followed by the square to shoot" << endl;
    }

    vector<Move> getAvailableMoves() const {
        return b.getAvailableMoves( turnCount % 2 );
    }

    friend ostream& operator<<(ostream&os, const Amazons& a);

    friend ostream& operator<<(ostream&os, const move_t& mv);

    friend istream& operator>> (istream&in, move_t& mv);

    bool operator==(const Amazons& other_amazons) const
    {
        return b.board == other_amazons.b.board;
    }
};

ostream& operator<<(ostream&os, const Amazons& a)
{
    os << a.b;
    return os;
}

ostream& operator<<(ostream&os, const Amazons::move_t& mv)
{
    os << "{ " << ", " << mv.queenStartingPos << ", " << mv.queenEndingPos << ", " << mv.firePos << " }";
    return os;
}


istream& operator>> (istream&in, Amazons::move_t& mv) {
    int qs, qe, f;
    cout << "<start> <end> <fire-pos>: ";
    if (in >> qs >> qe >> f)
    {
        mv.queenStartingPos = qs;
        mv.queenEndingPos = qe;
        mv.firePos = f;
    }
    return in;
}

template<> // Explicit specialization of std::hash<T>
struct std::hash<Amazons> {
    size_t operator() (const Amazons& azns) const
        {
            string repr;
            for (auto& row : azns.b.board) {
                for (auto& c : row) {
                    repr += c;
                }
            }

            return hash<string>()(repr);
        }
};

#endif
