#include "Cpu.hpp"

#include <thread>
#include <chrono>

constexpr int TIME_TO_SLEEP = 100;

Cpu::Cpu(int id, Board &board): _id(id), _board(board)
{
    if (_id == 1) _piece = 'o';
    else _piece = 'x';
}

Cpu::~Cpu() {}

bool Cpu::selectNumber()
{
    while (true)
    {
        this->_board.showBoard();
        printf("TURN CPU (%c)\n", this->_piece);
        std::this_thread::sleep_for(std::chrono::milliseconds(TIME_TO_SLEEP));
        this->_random = (rand() % 7);
        if (this->_board.isValidInput(std::to_string(this->_random)))
        {
            this->_board.setPiece(this->_random, this->_piece);
            break ;
        }
    }
    if (this->_board.checkGame(this->_piece))
    {
        this->_board.showBoard();
        std::cout << "CPU WIN!!" << std::endl;
        return true;
    }
    return false;
}

