#ifndef BOARD_HPP
#define BOARD_HPP

#include <iostream>

class Board
{
public:
	Board();
	~Board();
	void showBoard();
	bool checkGame(char piece);
	bool isValidInput(std::string inputNumber);
	void setPiece(int idx, char piece);

private:
	std::string _board[6];
	bool isFourInARow(char piece);
	bool isFourInACol(char piece);
	bool isFourInaADiagonally(char piece);
	bool isCheck4Pattern(int x, int y, int sign_x, int sign_y);
};

#endif
