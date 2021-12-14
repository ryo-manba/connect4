#include "Board.hpp"

#include <iostream>
using namespace std;
#define COL_LEN 6
#define ROW_LEN 7
#define PLAYER1 'O'
#define PLAYER2 'X'

// Create Board
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

void Board::showBoard()
{
	for (int i = 0; i < COL_LEN; i++)
	{
		for (int j = 0; j < ROW_LEN; j++)
		{
			cout << _board[i][j];
			if (j == ROW_LEN - 1) cout << endl;
			else cout << " ";
		}
	}
	cout << "1 2 3 4 5 6 7\n" << endl;
}

bool Board::isFourInARow(char piece)
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

bool Board::isFourInACol(char piece)
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

bool Board::isCheck4Pattern(int x, int y, int sign_x, int sign_y)
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

bool Board::isFourInaADiagonally(char piece)
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

bool Board::checkGame(char piece)
{
	if (isFourInARow(piece))         return true;
	if (isFourInACol(piece))         return true;
	if (isFourInaADiagonally(piece)) return true;
	return false;
}

bool Board::isValidInput(std::string inputNumber)
{
	if (inputNumber.length() != 1) return false;
	if (!('1' <= inputNumber[0] && inputNumber[0] <= '7')) return false;

	int idx = inputNumber[0] - '0' - 1;
	for (int i = COL_LEN; i >= 0; i--)
	{
		if (this->_board[i][idx] == '-')
		{
			return true;
		}
	}
	return false;
}

void Board::setPiece(int idx, char piece)
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
