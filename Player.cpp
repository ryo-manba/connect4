#include "Player.hpp"
#include "Board.hpp"
#include "Const.hpp"

#include <string>

Player::Player(int id, Board &board): _id(id), _board(board)
{
	if (_id == 1) _piece = PIECE1;
	else _piece = PIECE2;
}

Player::~Player() {}

bool Player::SelectNumber()
{
	while (true)
	{
		this->_board.showBoard();
		printf("TURN Player%d (%c)\n", this->_id, this->_piece);
		std::cout << "(1 ~ 7)> ";
		std::cin >> this->_inputNumber;
		if (this->_board.isValidInput(this->_inputNumber))
		{
			this->_board.setPiece(std::stoi(this->_inputNumber) - 1, this->_piece);
			break ;
		}
	}
	if (this->_board.checkGame(this->_piece))
	{
		this->_board.showBoard();
		printf("Player%d WIN!!\n", this->_id);
		return true;
	}
	return false;
}

