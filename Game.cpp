#include "Game.hpp"

Game::Game() : _turn(0)
{
	std::cout << ("Welcome to 4 in a row!") << std::endl;
	printf(""
	"Please enter the mode :\n"
	"  [1] 1P vs CPU\n"
	"  [2] 1P vs 2P\n\n"
	" > ");
	std::cin >> this->_Mode;
	if (this->_Mode == "1") _isCpuMode = true;
	if (this->_Mode == "2") _isCpuMode = false;
}

Game::~Game() {}

void Game::Start()
{
	Board board;
	Player player1(1, board);
	Player player2(2, board);

	const int maxTurn = ROW_LEN * COL_LEN;
	while (this->_turn < maxTurn)
	{
		if (player1.SelectNumber())
		{
			break ;
		}
		this->_turn++;
		if (player2.SelectNumber())
			break ;
		this->_turn++;
	}
}
