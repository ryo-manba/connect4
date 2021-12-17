#ifndef GAME_HPP
#define GAME_HPP

#include "Board.hpp"
#include "Cpu.hpp"
#include "Player.hpp"

class Game
{
public:
    Game();
    ~Game();
    void Start();

private:
    std::string _mode;
    void PvE(const int &mode);
    void PvP();
    void selectMode();
    void printResult(const char *color, const char *message) const;
};

#endif
