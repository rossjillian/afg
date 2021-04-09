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

bool Board::isValid(Move move, int turn) const 
{
    int max = BOARDSIZE * BOARDSIZE - 1;
    //No move can be outside the bounds of the board
    if (move.queenStartingPos > max || move.queenEndingPos > max || move.firePos > max)
    {
        return false;
    }

    //The queen starting position must indeed be occupied by a queen
    int qspRow = move.queenStartingPos / BOARDSIZE;
    int qspCol = move.queenStartingPos % BOARDSIZE;
    if (board[qspRow][qspCol] != 'w' && board[qspRow][qspCol] != 'b')
    {
        return false;
    }

    //white cannot move black's queen and visa versa
    if (board[qspRow][qspCol] == 'w' && turn == 1)
    {
        return false;
    }

    if (board[qspRow][qspCol] == 'b' && turn == 0)
    {
        return false;
    }

    //end and firing positions must be empty except if firing equal to starting pos
    int qepRow = move.queenEndingPos / BOARDSIZE;
    int qepCol = move.queenEndingPos % BOARDSIZE;

    int fpRow = move.firePos / BOARDSIZE;
    int fpCol = move.firePos % BOARDSIZE;
    if (board[qepRow][qepCol] != ' ')
    {
        return false;
    }

    if (board[fpRow][fpCol] != ' ' && move.queenStartingPos != move.firePos)
    {
        return false;
    }

    //starting and ending positions cannot be equal, queen cannot fire on a spot she's on */
    if (move.queenStartingPos == move.queenEndingPos || move.queenEndingPos == move.firePos)
    {
        return false;
    }

    //Check that the queen move is valid
    if (!isValidMovement(move.queenStartingPos, move.queenEndingPos))
    {
        return false;
    }

    if (!isValidMovement(move.queenEndingPos, move.firePos))
    {
        return false;
    }

    return true;
}

ostream& operator<<(ostream& os, const Board& board)
{
    const Grid& grid = board.board;
    for (auto row = grid.begin(); row != grid.end(); ++row)
    {
        string baseline;
        for (auto col = row->begin(); col != row->end(); ++col)
        {
            baseline += "----";
        }
        os << baseline << endl;
        os << "|";
        for (auto col = row->begin(); col != row->end(); ++col)
        {

            if (*col == 'w')
            {
                os << setw(CELLWIDTH) << " \U00002655" << setw(CELLWIDTH);
            } else if (*col == 'b')
            {
                os << setw(CELLWIDTH) << " \U0000265B" << setw(CELLWIDTH);
            } 
            else {
                os << setw(CELLWIDTH) << *col << setw(CELLWIDTH);
            }

            os << "|";

        }
        os << endl;
        if (row+1 == grid.end())
        {
            os << baseline << endl;
        }
    }
    return os;
}

vector<Move> Board::getAvailableMoves(int turn) const
{
    vector<Move> moves;
    //iterate through all possible queen positions, all possible firing positions for the player

    for (int qstart = 0; qstart < BOARDSIZE * BOARDSIZE; qstart++)
    {
        int qspRow = qstart / BOARDSIZE;
        int qspCol = qstart % BOARDSIZE;

        if ((board[qspRow][qspCol] != 'w' && board[qspRow][qspCol] != 'b')
            || (board[qspRow][qspCol] == 'w' && turn == 1)
            || (board[qspRow][qspCol] == 'b' && turn == 0))
            continue;

        for (int qend = 0; qend < BOARDSIZE * BOARDSIZE; qend++)
        {
            int qepRow = qend / BOARDSIZE;
            int qepCol = qend % BOARDSIZE;

            if (board[qepRow][qepCol] != ' ')
                continue;

            if (qstart == qend)
                continue;


            for (int firing = 0; firing < BOARDSIZE * BOARDSIZE; firing++)
            {

                int fpRow = firing / BOARDSIZE;
                int fpCol = firing % BOARDSIZE;


                if (board[fpRow][fpCol] != ' ' && qstart != firing)
                    continue;

                if (qend == firing)
                    continue;

                Move move = {qstart, qend, firing};
                if (isValid(move, turn))
                {
                    moves.push_back(move);
                }
            }
        }
    }
    return moves;
}

bool Board::isWinner(int turn) const
{
    turn ^= 1;
    /* if (getAvailableMoves(turn).size() == 0) */
    /* { */
    /*     return true; */
    /* } else { */
    /*     return false; */
    /* } */

    for (int qstart = 0; qstart < BOARDSIZE * BOARDSIZE; qstart++)
    {
        for (int qend = 0; qend < BOARDSIZE * BOARDSIZE; qend++)
        {
            for (int firing = 0; firing < BOARDSIZE * BOARDSIZE; firing++)
            {
                Move move = {qstart, qend, firing};
                if (isValid(move, turn))
                {
                    /* moves.push_back(move); */
                    return false;
                }
            }
        }
    }

    return true;
}

void Board::makeMove(Move move, int turn)
{
    if (isValid(move, turn))
    {
        //add the correct colored queen to the ending spot
        int qerow = move.queenEndingPos / board.size();
        int qecol = move.queenEndingPos % board.size();
        board[qerow][qecol] = turn ? 'b' : 'w';

        //clear the starting square
        int qsrow = move.queenStartingPos / board.size();
        int qscol = move.queenStartingPos % board.size();

        board[qsrow][qscol] = ' ';

        int frow = move.firePos / board.size();
        int fcol = move.firePos % board.size();
        board[frow][fcol] = 'x';
    }
}

bool Board::isValidMovement(int start, int end) const
{
    if (isOnColumn(start, end))
    {
        if (obstructedColumn(start, end))
        {
            return false;
        }

    } else if (isOnRow(start, end))
    {
        if (obstructedRow(start,end))
        {
            return false;
        }
    } else if (isOnDiagonalUp(start, end))
    {
        if (obstructedDiagonalUp(start, end))
        {
            return false;
        }
    } else if (isOnDiagonalDown(start, end))
    {
        if (obstructedDiagonalDown(start, end))
        {
            return false;
        }
    } else {
        return false;
    }

    return true;
}

bool Board::isOnRow(int start, int end) const
{
    return (start / BOARDSIZE == end / BOARDSIZE);
}

bool Board::isOnColumn(int start, int end) const
{
    return (start % BOARDSIZE == end % BOARDSIZE);
}

bool Board::isOnDiagonalUp(int start, int end) const
{
    if (start > end){
        int temp = end;
        end = start;
        start = temp;
    }

    int startRow = start / BOARDSIZE;
    int startCol = start % BOARDSIZE;

    int endRow = end / BOARDSIZE;
    int endCol = end % BOARDSIZE;
    return startRow + startCol == endRow + endCol;
}

bool Board::isOnDiagonalDown(int start, int end) const
{
    if (start > end){
        int temp = end;
        end = start;
        start = temp;
    }

    int startRow = start / BOARDSIZE;
    int startCol = start % BOARDSIZE;

    int endRow = end / BOARDSIZE;
    int endCol = end % BOARDSIZE;
    return abs(startRow - startCol) == abs(endRow - endCol);
}

bool Board::obstructedDiagonalDown(int start, int end) const
{
    if (start > end){
        int temp = end;
        end = start;
        start = temp;
    }

    int startRow = start / BOARDSIZE;
    int startCol = start % BOARDSIZE;

    int endRow = end / BOARDSIZE;

    for (int i = 1; i < endRow - startRow; i++)
    {
        /* cout << startRow + i; */
        /* cout << startCol + i; */
        if (board[startRow + i][startCol + i] != ' '){
            return true;
        }
    }
    return false;
}

bool Board::obstructedDiagonalUp(int start, int end) const
{
    if (start > end){
        int temp = end;
        end = start;
        start = temp;
    }

    int startRow = start / BOARDSIZE;
    int startCol = start % BOARDSIZE;

    int endRow = end / BOARDSIZE;

    for (int i = 1; i < endRow - startRow; i++)
    {
        if (board[startRow + i][startCol - i] != ' '){
            return true;
        }
    }
    return false;
}

bool Board::obstructedRow(int start, int end) const
{
    int colstart = 0;
    int colend = 0;
    int row = start / BOARDSIZE;
    if (start < end)
    {
        colstart = start % BOARDSIZE;
        colend = end % BOARDSIZE;
    } else {
        colstart = end % BOARDSIZE;
        colend = start % BOARDSIZE;
    }
    for (int i = colstart + 1; i < colend; i++)
    {
        if (board[row][i] != ' ')
        {
            return true;
        }
    }
    return false;
}

bool Board::obstructedColumn(int start, int end) const
{
    int rowstart = 0;
    int rowend = 0;
    int col = start % BOARDSIZE;
    if (start < end)
    {
        rowstart = start / BOARDSIZE;
        rowend = end / BOARDSIZE;
    } else {
        rowstart = end / BOARDSIZE;
        rowend = start / BOARDSIZE;
    }
    for (int i = rowstart + 1; i < rowend; i++)
    {
        if (board[i][col] != ' ')
        {
            return true;
        }
    }
    return false;
}
