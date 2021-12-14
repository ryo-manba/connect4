#ifndef GAME_HPP
#define GAME_HPP

#include "Board.hpp"
#include "Player.hpp"

#define COL_LEN 6
#define ROW_LEN 7
#define PLAYER1 'O'
#define PLAYER2 'X'
class Game
{
public:
	Game();
	~Game();
	void Start();

private:
	int _turn;
//	Board _board;
//	CPU	_cpu;
	std::string _Mode;
	bool _isCpuMode;
};

#endif
