#include "Player.hpp"

#include <string>

#include "Board.hpp"
#include "Const.hpp"

Player::Player(int id, Board &board) : _id(id), _board(board)
{
    if (_id == 1)
        _piece = PIECE1;
    else
        _piece = PIECE2;
    _idxRange = ("SELECT(1 ~ " + std::to_string(ROW_LEN) + ") > ");
}

Player::~Player() {}

void Player::selectNumber()
{
    while (true)
    {
        this->_board.showBoard();
        printf("TURN Player%d (%c)\n", this->_id, this->_piece);
        std::cout << this->_idxRange;
        std::cin >> this->_inputNumber;
        if (this->_board.isValidInput(this->_inputNumber))
        {
            this->_board.setPiece(std::stoi(this->_inputNumber) - 1,
                                  this->_piece);
            break;
        }
    }
}
