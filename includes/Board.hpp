#ifndef BOARD_HPP
#define BOARD_HPP

#include <iostream>
#include "Const.hpp"

class Board
{
public:
    Board();
    ~Board();
    void showBoard() const;
    bool checkGame(const char &piece) const;
    bool isValidInput(const std::string &inputNumber) const;
    void setPiece(const int &idx, const char &piece);
    bool isFull() const;

private:
    std::string _board[COL_LEN];
    std::string _rowIndex;
    std::string _maxNumber;
    bool isCheckRow(const char &piece) const;
    bool isCheckCol(const char &piece) const;
    bool isCheckDiagonal(const char &piece) const;
    bool isCheck4Pattern(const int &y,
                         const int &x,
                         const int &sign_y,
                         const int &sign_x) const;
};

#endif
