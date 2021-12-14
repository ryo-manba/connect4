#include "Player.hpp"
#include "Board.hpp"
Player::Player(int id, Board &board): _id(id), _board(board)
{
	if (_id == 1)
	{
		_piece = 'O';
		std::cout << 1;
	}
	else
	{
		_piece = 'X';
		std::cout << 2;
	}
}

Player::~Player() {}

bool Player::SelectNumber()
{
	printf("Player%dの番です.\n", this->_id);
	while (true)
	{
		std::cout << "(1 ~ 7)を入力してください." << std::endl;
		std::cout << "> ";
		std::cin >> this->_inputNumber;
		if (!this->_board.isValidInput(this->_inputNumber, this->_piece))
			continue;
		break ;
	}
	this->_board.showBoard();
	if (this->_board.checkGame())
		return true;
	return false;
}

