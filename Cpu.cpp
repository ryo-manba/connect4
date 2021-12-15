#include "Cpu.hpp"

#include <thread>
#include <chrono>
#include <random>

constexpr int TIME_TO_SLEEP = 100;

Cpu::Cpu(int id, Board &board): _id(id), _board(board)
{
    if (_id == 1) _piece = 'o';
    else _piece = 'x';
}

Cpu::~Cpu() {}

void Cpu::selectNumber()
{
    while (true)
    {
        this->_board.showBoard();
        printf("TURN CPU (%c)\n", this->_piece);
        std::this_thread::sleep_for(std::chrono::milliseconds(TIME_TO_SLEEP));
        std::random_device rnd;
        this->_random = rnd() % 7;
        std::cout << _random << std::endl;
        if (this->_board.isValidInput(std::to_string(this->_random + 1)))
        {
            this->_board.setPiece(this->_random, this->_piece);
            break ;
        }
    }
}

