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

void Board::makeMove(int move, int player, Grid& board){
    //TODO: could remove repetition from this calculation
    int row = move / board.size();
    int col = move % board.size();
    if (isValid(move))
        board[row][col] = player ? 'x' : 'o';
}

void Board::makeMove(int move, int player){
    makeMove(move, player, board);
}

void Board::retractMove(int move, int player, Grid& board) {
    int row = move / board.size();
    int col = move % board.size();
    board[row][col] = ' ';
}

void Board::retractMove(int move, int player) {
    retractMove(move, player, board);
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

    return moves;
}

bool Board::isFull() const
{
    for (auto& row : board)
        if (any_of(row.begin(), row.end(), [](char t) { return t == ' '; }))
            return false;

    return true;
}

int Board::getWinningTurn() const
{
    int rows = checkRows();
    int columns = checkColumns();
    int diagonals = checkDiagonals();
    if (rows != -1)
        return rows;
    else if (columns != -1)
        return columns;
    else if (diagonals != -1)
        return diagonals;
    return -1;
}

int Board::getTileTurn(char elem) const
{
    if (elem == 'x')
        return 1;
    else if (elem == 'o')
        return 0;
    return -1;
}

int Board::checkDiagonals() const
{
    char elem1 = board[0][0];
    char elem2 = board[0][board.size() - 1];
    int winner1 = getTileTurn(elem1);
    int winner2 = getTileTurn(elem2);
    for (size_t i = 1; i < board.size(); i++)
    {
        if (elem2 != board[i][board.size() - 1 - i] || elem2 == ' ')
        {
            winner2 = -1;
        }
        if (elem1 != board[i][i] || elem1 == ' ')
        {
            winner1 = -1;
        }
    }
    if (winner1 != -1)
        return winner1;
    else if (winner2 != -1)
        return winner2;
    return -1;
}

//TODO: maybe some way to reuse code?
int Board::checkColumns() const
{
    for (size_t c = 0; c < board.size(); c++)
    {
        char elem = board[0][c];
        int winner = getTileTurn(elem);
        for (const auto& row : board)
        {
            if (elem != row[c] || elem == ' ')
            {
                winner = -1;
                break;
            }
        }

        if (winner != -1)
            return winner;
    }
    return -1;
}

int Board::checkRows() const
{
    for (const auto& row : board)
    {
        char elem = *(row.begin());
        int winner = getTileTurn(elem);
        for (auto col = row.begin() + 1; col != row.end(); ++col)
        {
            if (elem != *col || elem == ' ')
            {
                winner = -1;
                break;
            }
        }

        if (winner != -1)
            return winner;
    }
    return -1;
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
