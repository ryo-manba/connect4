#ifndef CPU_HPP
#define CPU_HPP

#include "Game.hpp"

class Cpu
{
public:
	Cpu(int id, Board &board);
	~Cpu();
	void selectNumber();

private:
	int _id;
	int	_idx;
	int _maxScore;
	int _maxIdx;
	char _piece;
	static int score[ROW_LEN];
	Board &_board;

	void montecarlo(const Board &board, int depth);
	void playOut(const Board &board, int &depth);
	bool selectIdx(int idx);
	void selectRandom();
	void setPiece(int &idx, char &piece);
	bool isValidInput(std::string &inputNumber) const;
};

#endif
