#ifndef Cpu_HPP
#define Cpu_HPP

#include "Game.hpp"

class Cpu
{
public:
	Cpu(int id, Board &board);
	~Cpu();
	void selectNumber();

private:
	int _id;
	char _piece;
	Board &_board;
	int	_random;
	int	_toWin;
	bool isValidInput(std::string &inputNumber) const;
	void setPiece(int &idx, char &piece);

	bool toWinOrRand(const char &piece);
	bool toWinInACol(const char &piece);
	bool toWinInARow(const char &piece);
	bool toWinInaADiagonally(const char &piece);
	bool toWinCheck4Pattern(const int &x,
                            const int &y,
                            const int &sign_x,
                            const int &sign_y);

};

#endif
