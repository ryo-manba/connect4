#ifndef Cpu_HPP
#define Cpu_HPP

#include "Game.hpp"

class Cpu
{
public:
	Cpu(int id, Board &board);
	~Cpu();
	bool selectNumber();

private:
	int _id;
	char _piece;
	Board &_board;
	int	_random;
	bool isValidInput(std::string &inputNumber) const;
	void setPiece(int &idx, char &piece);
};

#endif
