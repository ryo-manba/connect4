#ifndef GAME_HPP
#define GAME_HPP

#include "Board.hpp"
#include "Player.hpp"
#include "Cpu.hpp"

#define COL_LEN 6
#define ROW_LEN 7

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
