#include <iostream>
#include <vector>
#include <iomanip>
#include "board.hpp"
#include "game.hpp"

using namespace std;
const int CELLWIDTH = 2;
const int BOARDSIZE = 10;

Board::Board()
{
    board.resize(BOARDSIZE, vector<char>(BOARDSIZE));
    for (auto& row : board)
        fill(row.begin(), row.end(), ' ');
    board[0][3] = 'b';
    board[0][6] = 'b';
    board[3][0] = 'b';
    board[3][9] = 'b';

    board[6][0] = 'w';
    board[9][6] = 'w';
    board[9][3] = 'w';
    board[6][9] = 'w';
}

void printBoard(const Grid &board, bool instructions)
{
    int num = 0;
    for (auto row = board.begin(); row != board.end(); ++row)
    {
        string baseline;
        for (auto col = row->begin(); col != row->end(); ++col)
        {
            baseline += "----";
        }
        cout << baseline << endl;
        cout << "|";
        for (auto col = row->begin(); col != row->end(); ++col)
        {

            if (!instructions)
            {
                if (*col == 'w')
                {
                    cout << setw(CELLWIDTH) << " \U00002655" << setw(CELLWIDTH);
                } else if (*col == 'b')
                {
                    cout << setw(CELLWIDTH) << " \U0000265B" << setw(CELLWIDTH);
                } 
                else {
                   cout << setw(CELLWIDTH) << *col << setw(CELLWIDTH);
                }
            } else {
                cout << setw(CELLWIDTH) << num << setw(CELLWIDTH);
            }

            cout << "|";
            num++;

        }
        cout << endl;
        if (row+1 == board.end())
        {
            cout << baseline << endl;
        }
    }
}

void Board::print(bool instructions) const
{
    printBoard(board, instructions);
}

bool Board::isValid(Move move) const 
{
    int max = BOARDSIZE * BOARDSIZE - 1;
    //No move can be outside the bounds of the board
    if (move.queenStartingPos > max || move.queenEndingPos > max || move.firePos > max)
        return false;

    //The queen starting position must indeed be occupied by a queen
    int qspRow = move.queenStartingPos / BOARDSIZE;
    int qspCol = move.queenStartingPos % BOARDSIZE;
    if (board[qspRow][qspCol] != 'w' && board[qspRow][qspCol] != 'b')
    {
        return false;
    }

    /*if (!isOnColumn(move.queenStartingPos, move.queenEndingPos))
    {
        cout << "col" << endl;
    }
    
    if (!isOnRow(move.queenStartingPos, move.queenEndingPos))
    {
        cout << "row" << endl;
    }*/

    if (!isOnColumn(move.queenStartingPos, move.queenEndingPos) 
        && !isOnRow(move.queenStartingPos, move.queenEndingPos) 
        && !isOnDiagonals(move.queenStartingPos, move.queenEndingPos))
    {
        return false;
    }
    //
    return true;
}

bool Board::isOnColumn(int start, int end) const
{
    return (start / BOARDSIZE == end / BOARDSIZE);
}

bool Board::isOnRow(int start, int end) const
{
    return (start % BOARDSIZE == end % BOARDSIZE);
}

bool Board::isOnDiagonals(int start, int end) const
{
    return false;
}