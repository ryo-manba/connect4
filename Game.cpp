#include "Game.hpp"

Game::Game()
{
	printf("Welcome to 4 in a row!\n");
}

Game::~Game()
{
	delete []this->_Players;
	std::cout << "Bye." << std::endl;
}

void Game::Start()
{
	printf(""
	"Please enter the mode :\n"
	"  [1] 1P vs CPU\n"
	"  [2] 1P vs 2P\n\n"
	" > ");
	std::cin >> this->_Mode;

	if (this->_Mode == "1") _isCpuMode = true;
	if (this->_Mode == "2") _isCpuMode = false;
	std::cout << "4目並べスタート" << std::endl;

	this->_Players = new Player[2];

	while (true)
	{
		this->_Players[0].SelectNumber();
		this->_Players[1].SelectNumber();
	}
}
