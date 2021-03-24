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

int main (int argc, char **argv)
{
    Board board(4);
    board.printBoard(true);
    cout << endl;
    board.printBoard();
    cout << board.checkValid(14);
    board.makeMove(3, 1);
    board.makeMove(3, 0);
    board.makeMove(2, 0);
    board.makeMove(15, 0);
    board.printBoard();
}