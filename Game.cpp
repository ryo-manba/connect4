#include "Game.hpp"
#include "Const.hpp"

#define PVE "1"
#define PVP "2"

Game::Game(){ std::cout << ("Welcome to 4 in a row!") << std::endl; }

Game::~Game() {}

void Game::PvE()
{
	Board board;
	Player player(1, board);
	Cpu cpu(2, board);

	for (int i = 0; i < MAX_TURN; i += 2)
	{
		player.selectNumber();
		if (board.checkGame(PIECE1))
		{
			board.showBoard();
			printf("Player WIN!!\n");
			return ;
		}
		cpu.selectNumber();
		if (board.checkGame(PIECE2))
		{
			board.showBoard();
			printf("CPU WIN!!\n");
			return ;
		}
	}
}

void Game::PvP()
{
	Board board;
	Player players[2] = {{1, board}, {2, board}};

	for (int i = 0; i < MAX_TURN; i += 2)
	{
		for (int j = 0; j < 2; j++)
		{
			players[j].selectNumber();
			char piece = (j == 0) ? PIECE1 : PIECE2;
			if (board.checkGame(piece))
			{
				board.showBoard();
				printf("Player%d WIN!!\n", j);
				return ;
			}
		}
	}
}

void Game::selectMode()
{
	while (true)
	{
		printf(""
		"Please enter the mode :\n"
		"  [1] 1P vs CPU\n"
		"  [2] 1P vs 2P\n\n");
		std::cout << " > ";
		std::cin >> this->_mode;
		if (this->_mode == PVP || this->_mode == PVE)
			break ;
	}
}

void Game::Start()
{
	selectMode();
	if (this->_mode == PVE) PvE();
	if (this->_mode == PVP) PvP();
}
