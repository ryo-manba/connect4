#include "Board.hpp"
#include "Const.hpp"

#include <iostream>

#define DUMMY '*'
#define EMPTY '-'
#define MAX_CNT 4

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

bool Board::isCheckRow(const char &piece) const
{
    for (int y = 0; y < COL_LEN; y += 1)
    {
        int cnt = 0;
        char before = DUMMY;
        for (int x = 0; x < ROW_LEN; x += 1)
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
            if (cnt == MAX_CNT) return true;
        }
    }
    return false;
}

bool Board::isCheckCol(const char &piece) const
{
    for (int x = 0; x < ROW_LEN; x += 1)
    {
        char before = DUMMY;
        int cnt = 0;
        for (int y = 0; y < COL_LEN; y += 1)
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
            if (cnt == MAX_CNT) return true;
        }
    }
    return false;
}

// 斜め右上,右下,左上,左下に進む4パターンをチェックする
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
        if (cnt == MAX_CNT) return true;
        i += 1;
    }
    return false;
}

bool Board::isCheckDiagonal(const char &piece) const
{
    for (int y = 0; y < COL_LEN; y += 1)
    {
        for (int x = 0; x < ROW_LEN; x += 1)
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
    if (isCheckRow(piece))      return true;
    if (isCheckCol(piece))      return true;
    if (isCheckDiagonal(piece)) return true;
    return false;
}

bool Board::isFull() const
{
    for (int y = 0; y < COL_LEN; y += 1)
    {
        for (int x = 0; x < ROW_LEN; x += 1)
        {
            if (this->_board[y][x] == EMPTY)
            {
                return false;
            }
        }
    }
    return true;
}

void Board::showBoard() const
{
    for (int y = 0; y < COL_LEN; y += 1)
    {
        for (int x = 0; x < ROW_LEN; x += 1)
        {
            std::cout << _board[y][x];
            if (x == ROW_LEN - 1) std::cout << std::endl;
            else std::cout << " ";
        }
    }
    std::cout << "1 2 3 4 5 6 7\n" << std::endl;
}

// 数字以外が入力された場合,
// コマが置けなかった場合にfalseを返す
bool Board::isValidInput(const std::string &inputNumber) const
{
    if (inputNumber.length() != 1) return false;
    if (!('1' <= inputNumber[0] && inputNumber[0] <= '7')) return false;

    int idx = inputNumber[0] - '0' - 1;
    for (int y = COL_LEN; y >= 0; y -= 1)
    {
        if (this->_board[y][idx] == EMPTY)
            return true;
    }
    return false;
}

void Board::setPiece(const int &idx, const char &piece)
{
    for (int y = COL_LEN; y >= 0; y -= 1)
    {
        if (this->_board[y][idx] == EMPTY)
        {
            this->_board[y][idx] = piece;
            break ;
        }
    }
}
