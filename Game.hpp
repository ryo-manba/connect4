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
	std::string _mode;
	void PvE();
	void PvP();
	void selectMode();
};

#endif
