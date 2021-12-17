#include "Board.hpp"
#include "Const.hpp"

#include <iostream>

#define DUMMY '*'
#define EMPTY '-'
#define MAX_CNT 4

Board::Board()
{
    std::string rowBoard = "";
    for (int x = 0; x < ROW_LEN; x += 1)
        rowBoard += EMPTY;
    for (int y = 0; y < COL_LEN; y += 1)
        this->_board[y] = rowBoard;
    for (int x = 0; x < ROW_LEN; x += 1)
    {
        this->_rowIndex += std::to_string(x+1);
        if (x != ROW_LEN - 1) this->_rowIndex += " ";
    }
    this->_maxNumber = std::to_string(ROW_LEN);
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

bool Board::isCheck4Pattern(const int &y,
                            const int &x,
                            const int &sign_y,
                            const int &sign_x) const
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
                if (isCheck4Pattern(y, x, +1, +1)) return true; // [\]下
                if (isCheck4Pattern(y, x, -1, +1)) return true; // [/]上
                if (isCheck4Pattern(y, x, +1, -1)) return true; // [/]下
                if (isCheck4Pattern(y, x, -1, -1)) return true; // [\]上
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
    std::cout << this->_rowIndex << std::endl;
}

// 数字以外が入力された場合,
// コマが置けなかった場合にfalseを返す
bool Board::isValidInput(const std::string &inputNumber) const
{
    if (!("1" <= inputNumber || inputNumber <= this->_maxNumber))
        return false;
    int idx;
    try
    {
        idx = std::stoi(inputNumber) - 1;
    }
    catch (std::invalid_argument &e)
    {
        return false;
    }
    catch (std::out_of_range &e)
    {
        return false;
    }

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
