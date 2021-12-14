#ifndef BOARD_HPP
#define BOARD_HPP

#include <iostream>

class Board
{
public:
	Board();
	~Board();
	void showBoard();
	bool checkGame();
	bool isValidInput(std::string inputNumber, char piece);

private:
	std::string _board[6];
	bool isFourInARow();
	bool isFourInACol();
	bool isFourInaADiagonally();
	bool isCheck4Pattern(int x, int y, int sign_x, int sign_y);
};

#endif
