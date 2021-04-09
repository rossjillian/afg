#include <iostream>
#include <vector>
#include <iomanip>
#include "board.hpp"
#include "game.hpp"

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

void Board::makeMove(int move, int turn, Grid& board){
    int row = move / board.size();
    int col = move % board.size();
    if (isValid(move))
        board[row][col] = turn ? 'x' : 'o';
}

void Board::makeMove(int move, int turn){
    makeMove(move, turn, board);
}

vector<int> Board::getAvailableMoves() const
{
    vector<int> moves;
    for (size_t i = 0; i < numTiles; i++)
    {
        if (isValid(i))
        {
            moves.push_back(i);
        }
    }

    return moves;
}

bool Board::isFull() const
{
    for (auto& row : board)
        if (any_of(row.begin(), row.end(), [](char t) { return t == ' '; }))
            return false;

    return true;
}

bool Board::isWinner() const
{
    return checkRows() || checkColumns() || checkDiagonals();
}

bool Board::checkDiagonals() const
{
    char elem1 = board[0][0];
    char elem2 = board[0][board.size() - 1];
    bool winner1 = true;
    bool winner2 = true;
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

bool Board::checkColumns() const
{
    for (size_t c = 0; c < board.size(); c++)
    {
        char elem = board[0][c];
        bool winner = true;
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
        char elem = *(row.begin());
        bool winner = true;
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

ostream& operator<<(ostream& os, const Board& board){
    int num = 0;
    const Grid& grid = board.board;
    for (auto row = grid.begin(); row != grid.end(); ++row)
    {
        string baseline;
        for (auto col = row->begin(); col != row->end(); ++col)
        {
            baseline += "----";
            os << setw(2) << *col << setw(2);
            if (col+1 != row->end())
            {
                os << "|";
            }
            num++;

        }
        cout << endl;
        if (row+1 != grid.end())
        {
            os << baseline << endl;
        }
    }
    return os;
}

void Board::print(bool instructions = false) const
{
    printBoard(board, instructions);
}

void printBoard(const Grid &board, bool instructions = false)
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
