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
    std::string _board[COL_LEN];

private:
    bool isFourInARow(const char &piece) const;
    bool isFourInACol(const char &piece) const;
    bool isFourInaADiagonally(const char &piece) const;
    bool isCheck4Pattern(const int &x,
                         const int &y,
                         const int &sign_x,
                         const int &sign_y) const;
};

#endif
