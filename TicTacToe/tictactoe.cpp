#include <iostream>
#include <vector>
#include <iomanip>
#include "tictactoe.h"

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
    for (auto i = 0; i < numTiles; i++)
    {
        if (isValid(i))
        {
            moves.push_back(i);
        }
    }
    /* remove, for testing
    
    for (auto it = boards.begin(); it != boards.end(); ++it)
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
bool Board::isTerminal()
{
    return checkRows() || checkColumns() || checkDiagonals();
}

bool Board::checkDiagonals()
{
    bool winner1 = true;
    bool winner2 = true;
    char elem1 = board[0][0];
    char elem2 = board[0][board.size() - 1];
    for (auto i = 1; i < board.size(); i++)
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
bool Board::checkColumns()
{
    for (auto c = 0; c < board.size(); c++)
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

bool Board::checkRows()
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

void Board::printBoard(bool instructions = false)
{
    printBoard(board, instructions);
}

void Board::printBoard(const Grid &board, bool instructions = false)
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

Game::Game(HumanPlayer player1, HumanPlayer player2, int size = 3)
    : board(size),
    /* p1(player1), */
    /* p2(player2), */
    currentplayer(0)
{

}

void Game::Play()
{
    int size = 0;
    do {
        cout << "How big would you like the board to be (? x ?)" << endl;
        cin >> size;
    } while (size <= 0);
    Board board(size);
    cout << "Refer to moves using the following chart: " << endl;
    board.printBoard(true);
    cout << endl;
    while (!board.isTerminal() && !board.isFull())
    {
        cout << "Player " << currentplayer << " make a move!" << endl;
        board.printBoard();
        int tileNo = (currentplayer) ? p1.getStrategy(board) : p2.getStrategy(board);
        /* int move; */
        /* cin >> move; */
        board.makeMove(tileNo, currentplayer);
        currentplayer ^= 1;
        /* if (!board.isValid(move)) */
        /* { */
        /*     cout << "Invalid move." << endl; */
        /* } else { */
        /*     board.makeMove(move, currentplayer); */
        /*     currentplayer ^= 1; */
        /* } */
    }
    board.printBoard();
    if (board.isTerminal())
    {
        currentplayer ^= 1;
        cout << "Player " << currentplayer << " wins!" << endl;
    } else {
        cout << "It's a draw!" << endl;
    }


}

int main (int argc, char **argv)
{
    HumanPlayer p1;
    HumanPlayer p2;
    Game game(p1, p2);
    game.Play();
}
