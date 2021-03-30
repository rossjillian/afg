#include <iostream>
#include <vector>
#include <iomanip>
#include "board.hpp"

using namespace std;

Board::Board(size_t size)
{
    numTiles = size * size;
    board.resize(size, vector<char>(size));
    for (auto& row : board)
        fill(row.begin(), row.end(), ' ');
}

bool Board::isValid(int move) const
{
    int max = numTiles - 1;
    if (move > max)
        return false;

    int row = move / board.size();
    int col = move % board.size();

    return board[row][col] == ' ';
}

void Board::makeMove(int move, int player, Grid& board){
    //TODO: could remove repition from this calculation
    int row = move / board.size();
    int col = move % board.size();
    if (isValid(move))
        board[row][col] = player ? 'x' : 'o';
}

void Board::makeMove(int move, int player){
    makeMove(move, player, board);
}

vector<int> Board::getAvailableMoves() const
{
    vector<int> moves; // vector<Move> moves;
    for (size_t i = 0; i < numTiles; i++)
    {
        if (isValid(i))
        {
            moves.push_back(i);
        }
    }
    /* remove, for testing

    for (size_t it = boards.begin(); it != boards.end(); ++it)
    {
        printBoard(*it, false);
        cout << endl;
    }*/
    return moves;
}

bool Board::isFull()
{
    for (auto& row : board)
        if (any_of(row.begin(), row.end(), [](char t) { return t == ' '; }))
            return false;

    return true;
}

// We will know who just went, so we just need to return whether there's a winner or not
bool Board::isWinner() const
{
    return checkRows() || checkColumns() || checkDiagonals();
}



bool Board::checkDiagonals() const
{
    bool winner1 = true;
    bool winner2 = true;
    char elem1 = board[0][0];
    char elem2 = board[0][board.size() - 1];
    for (size_t i = 1; i < board.size(); i++)
    {
        if (elem2 != board[i][board.size() - 1 - i] || elem2 == ' ')
        {
            winner2 = false;
        }
        if (elem1 != board[i][i] || elem1 == ' ')
        {
            winner1 = false;
        }
    }
    return winner1 || winner2;
}

//TODO: maybe some way to reuse code?
bool Board::checkColumns() const
{
    for (size_t c = 0; c < board.size(); c++)
    {
        bool winner = true;
        char elem = board[0][c];
        for (const auto& row : board)
        {
            if (elem != row[c] || elem == ' ')
            {
                winner = false;
                break;
            }
        }

        if (winner)
            return winner;
    }
    return false;
}

bool Board::checkRows() const
{
    for (const auto& row : board)
    {
        bool winner = true;
        char elem = *(row.begin());
        for (auto col = row.begin() + 1; col != row.end(); ++col)
        {
            if (elem != *col || elem == ' ')
            {
                winner = false;
                break;
            }
        }

        if (winner)
            return winner;
    }
    return false;
}

void Board::print(bool instructions = false)
{
    print(board, instructions);
}

void Board::print(const Grid &board, bool instructions = false)
{
    int num = 0;
    for (auto row = board.begin(); row != board.end(); ++row)
    {
        string baseline;
        for (auto col = row->begin(); col != row->end(); ++col)
        {
            baseline += "----";
            if (!instructions)
            {
                cout << setw(2) << *col << setw(2);
            } else {
                cout << setw(2) << num << setw(2);
            }
            if (col+1 != row->end())
            {
                cout << "|";
            }
            num++;

        }
        cout << endl;
        if (row+1 != board.end())
        {
            cout << baseline << endl;
        }
    }
}
