#ifndef CPU_HPP
#define CPU_HPP

#include "Game.hpp"

class Cpu
{
public:
	Cpu(int id, Board &board);
	~Cpu();
	bool selectNumber(int idx);

private:
	int _id;
	char _piece;
	Board &_board;
	int	_random;
	int	_toWin;
	bool isValidInput(std::string &inputNumber) const;
	void setPiece(int &idx, char &piece);
};

void montecarlo(int idx, int depth, Board board);

#endif
