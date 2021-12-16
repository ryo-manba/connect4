#include "Board.hpp"
#include "Const.hpp"

#include <iostream>

Board::Board()
{
    this->_board[0]	= "-------";
    this->_board[1]	= "-------";
    this->_board[2]	= "-------";
    this->_board[3]	= "-------";
    this->_board[4]	= "-------";
    this->_board[5]	= "-------";
}

Board::~Board() {}

bool Board::isFourInARow(const char &piece) const
{
    for (int y = 0; y < COL_LEN; y++)
    {
        int cnt = 0;
        char before = '*';
        for (int x = 0; x < ROW_LEN; x++)
        {
            if (this->_board[y][x] == piece)
                cnt += 1;
            if (before != this->_board[y][x])
            {
                if (this->_board[y][x] == piece)
                    cnt = 1;
                else cnt = 0;
            }
            before = this->_board[y][x];
            if (cnt == 4) return true;
        }
    }
    return false;
}

bool Board::isFourInACol(const char &piece) const
{
    for (int x = 0; x < ROW_LEN; x++)
    {
        char before = '*';
        int cnt = 0;
        for (int y = 0; y < COL_LEN; y++)
        {
            if (this->_board[y][x] == piece)
                cnt += 1;
            if (before != this->_board[y][x])
            {
                if (this->_board[y][x] == piece)
                    cnt = 1;
                else cnt = 0;
            }
            before = this->_board[y][x];
            if (cnt == 4) return true;
        }
    }
    return false;
}

bool Board::isCheck4Pattern(const int &x,
                            const int &y,
                            const int &sign_x,
                            const int &sign_y) const
{
    int i = 1;
    int cnt = 1;
    char piece = this->_board[y][x];

    while (true)
    {
        if (sign_y == -1 && y - i == -1)      break;
        if (sign_x == -1 && x - i == -1)      break;
        if (sign_y == +1 && y + i == COL_LEN) break;
        if (sign_x == +1 && x + i == ROW_LEN) break;

        if (this->_board[y + (i * sign_y)][x + (i * sign_x)] != piece)
            break;
        cnt += 1;
        if (cnt == 4) return true;
        i += 1;
    }
    return false;
}

bool Board::isFourInaADiagonally(const char &piece) const
{
    for (int y = 0; y < COL_LEN; y++)
    {
        for (int x = 0; x < ROW_LEN; x++)
        {
            if (this->_board[y][x] == piece)
            {
                if (isCheck4Pattern(x, y, +1, +1)) return true; // [\]下
                if (isCheck4Pattern(x, y, +1, -1)) return true; // [/]上
                if (isCheck4Pattern(x, y, -1, +1)) return true; // [/]下
                if (isCheck4Pattern(x, y, -1, -1)) return true; // [\]上
            }
        }
    }
    return false;
}

bool Board::checkGame(const char &piece) const
{
    if (isFourInARow(piece))         return true;
    if (isFourInACol(piece))         return true;
    if (isFourInaADiagonally(piece)) return true;
    return false;
}

bool Board::isFull() const
{
    for (int y = 0; y < COL_LEN; y++)
    {
        for (int x = 0; x < ROW_LEN; x++)
        {
            if (this->_board[y][x] == '-') // 置ける場所があった時点でfalseを返す
            {
                return false;
            }
        }
    }
    return true; // 全てコマが置いてあったらtrue
}

void Board::showBoard() const
{
    for (int i = 0; i < COL_LEN; i++)
    {
        for (int j = 0; j < ROW_LEN; j++)
        {
            std::cout << _board[i][j];
            if (j == ROW_LEN - 1) std::cout << std::endl;
            else std::cout << " ";
        }
    }
    std::cout << "1 2 3 4 5 6 7\n" << std::endl;
}

bool Board::isValidInput(const std::string &inputNumber) const
{
    if (inputNumber.length() != 1) return false;
    if (!('1' <= inputNumber[0] && inputNumber[0] <= '7')) return false;

    int idx = inputNumber[0] - '0' - 1;
    for (int i = COL_LEN; i >= 0; i--) // コマが置けるかチェックする
    {
        if (this->_board[i][idx] == '-')
        {
            return true;
        }
    }
    return false;
}

void Board::setPiece(const int &idx, const char &piece)
{
    for (int i = COL_LEN; i >= 0; i--)
    {
        if (this->_board[i][idx] == '-')
        {
            this->_board[i][idx] = piece;
            break ;
        }
    }
}
