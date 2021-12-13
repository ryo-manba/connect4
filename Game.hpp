#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>
#include "Player.hpp"
#include "Board.hpp"

class Game
{
public:
	Game();
	~Game();
	void Start();

private:
	Board _board;
	Player *_Players;
//	CPU	_cpu;
	std::string _Mode;
	bool _isCpuMode;
};

#endif
