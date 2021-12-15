#ifndef GAME_HPP
#define GAME_HPP

#include "Board.hpp"
#include "Player.hpp"
#include "Cpu.hpp"

class Game
{
public:
	Game();
	~Game();
	void Start();

private:
	int _turn;
	std::string _Mode;
	bool _isCpuMode;
};

#endif
