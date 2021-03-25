#include <iostream>
#include "tictactoe.h"
#include <vector>
#include <iomanip>

using namespace std; 

Board::Board(size_t size)
{
    board.resize(size, vector<char>(size));
    for (size_t i = 0; i < size; i++)
    {
        for (size_t j = 0; j < size; j++)
        {
            board[i][j] = ' ';
        }
        
    }     
}

bool Board::checkValid(int move)
{
    int max = board.size() * board.size() - 1;
    if (move > max)
    {
        return false;
    }
    int row = move / board.size();
    int col = move % board.size();
    if (board[row][col] == ' ')
    {
        return true;
    }
    return false;
}

void Board::makeMove(int move, int player){
    //TODO: could remove repition from this calculation
    int row = move / board.size();
    int col = move % board.size();
    if (checkValid(move))
    {
        if (player)
        {
            board[row][col] = 'x';
        } else {
            board[row][col] = 'o';
        }
    }
}

bool Board::isFull()
{
    for (auto row = board.begin(); row != board.end(); ++row)
    {
        for (auto col = row->begin() + 1; col != row->end(); ++col)
        {
            if (*col == ' ')
            {
                return false;
            }
        }
    }
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
    for (size_t i = 1; i < static_cast<size_t>(board.size()); i++)
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
    for (size_t i = 0; i < static_cast<size_t>(board.size()); i++)
    {
        bool winner = true;
        char elem = board[0][i];
        for (size_t j = 0; j < static_cast<size_t>(board.size()); j++)
        {
            if (elem != board[j][i] || elem == ' ')
            {
                winner = false;
            }
        }
        if (winner)
        {
            return winner;
        }
    }
    return false;
}

bool Board::checkRows()
{
    for (auto row = board.begin(); row != board.end(); ++row)
    {
        bool winner = true;
        char elem = *(row -> begin());
        for (auto col = row->begin() + 1; col != row->end(); ++col)
        {
            if (elem != *col || elem == ' ')
            {
                winner = false;
            }
        }
        if (winner)
        {
            return winner;
        }
    }
    return false;
}

void Board::printBoard(bool instructions = false)
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

Game::Game(Player player1, Player player2, int size = 3) 
    : board(size), 
    p1(player1),
    p2(player2),
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
        int move;
        cin >> move;
        if (!board.checkValid(move))
        {
            cout << "Invalid move." << endl;
        } else {
            board.makeMove(move, currentplayer);
            currentplayer ^= 1;
        }
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
    Game game(Player::human, Player::human);
    game.Play();
}