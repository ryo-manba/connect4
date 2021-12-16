#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Board.hpp"
#include "Game.hpp"
#include <iostream>

class Player
{
public:
	Player(int id, Board &board);
	~Player();
	void selectNumber();

private:
	int	_id;
	int	_idx;
	char _piece;
	Board &_board;
	std::string _inputNumber;
	bool isValidInput();
};

#endif
