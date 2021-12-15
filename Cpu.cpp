#include "Cpu.hpp"

#include <thread>
#include <chrono>
#include <random>

//constexpr int TIME_TO_SLEEP = 100;

Cpu::Cpu(int id, Board &board): _id(id), _board(board)
{
    if (_id == 1) _piece = 'o';
    else _piece = 'x';
}

Cpu::~Cpu() {}

bool Cpu::toWinInARow(const char &piece)
{
    for (int y = 0; y < COL_LEN; y++)
    {
        int cnt = 0;
        char before = '*';
        for (int x = 0; x < ROW_LEN; x++)
        {
            if (this->_board._board[y][x] == piece)
                cnt += 1;
            if (before != this->_board._board[y][x])
            {
                if (this->_board._board[y][x] == piece)
                    cnt = 1;
                else cnt = 0;
            }
            before = this->_board._board[y][x];
            if (cnt == 3)
            {
                if (x + 1 < ROW_LEN && this->_board._board[y][x + 1] == '-') // 右隣が空いている
                {
                    if (y - 1 > 0 && this->_board._board[y - 1][x + 1] != '-') // コマが置ける
                    {
                        this->_toWin = x + 1;
                        return true;
                    }
                }
                if (x - 3 >= 0 && this->_board._board[y][x - 3] == '-') // 左隣が空いている
                {
                    if (y - 1 > 0 && this->_board._board[y - 1][x - 3] != '-') // コマが置ける
                    {
                        this->_toWin = x - 3;
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

bool Cpu::toWinInACol(const char &piece)
{
    for (int x = 0; x < ROW_LEN; x++)
    {
        char before = '*';
        int cnt = 0;
        for (int y = 0; y < COL_LEN; y++)
        {
            if (this->_board._board[y][x] == piece)
                cnt += 1;
            if (before != this->_board._board[y][x])
            {
                if (this->_board._board[y][x] == piece)
                    cnt = 1;
                else cnt = 0;
            }
            before = this->_board._board[y][x];
            if (cnt == 3)
            {
                if (y + 1 < COL_LEN && this->_board._board[y + 1][x] == '-') // 上が空いている
                {
                    this->_toWin = x;
                    return true;
                }
            }
        }
    }
    return false;
}

bool Cpu::toWinCheck4Pattern(const int &x,
                               const int &y,
                               const int &sign_x,
                               const int &sign_y)
{
    int i = 1;
    int cnt = 1;
    char piece = this->_board._board[y][x];

    while (true)
    {
        if (sign_y == -1 && y - i == -1)      break;
        if (sign_x == -1 && x - i == -1)      break;
        if (sign_y == +1 && y + i == COL_LEN) break;
        if (sign_x == +1 && x + i == ROW_LEN) break;

        if (this->_board._board[y + (i * sign_y)][x + (i * sign_x)] != piece)
            break;
        cnt += 1;
        if (cnt == 3)
        {
            if (sign_y == +1 && sign_x == +1) // [\]下
            {
                if (y + 4 < COL_LEN && x + 3 < ROW_LEN) // 下方向に進むから+4のチェック
                {
                    if (this->_board._board[y + 3][x + 3] == '-') // [\]下方向が空
                    {
                        if (this->_board._board[y + 4][x + 3] != '-') // [\]下方向に置ける
                        {
                            this->_toWin = x + 3;
                            return true;
                        }
                    }
                }
                if (y - 1 >= 0 && x - 1 >= 0)
                {
                    if (this->_board._board[y - 1][x - 1] == '-') // [\]上方向が空
                    {
                        if (this->_board._board[y][x - 1] != '-') // [\]上方向に置ける
                        {
                            this->_toWin = x - 1;
                            return true;
                        }
                    }
                }
            }
            if (sign_y == -1 && sign_x == -1) // [\]上
            {
                if (y - 3 >= 0 && x - 3 >= 0)
                {
                    if (this->_board._board[y - 3][x - 3] == '-') // [\]上方向が空
                    {
                        if (this->_board._board[y - 2][x - 3] != '-') // [\]上方向に置ける
                        {
                            this->_toWin = x - 3;
                            return true;
                        }
                    }
                }
                if (y + 2 < COL_LEN && x + 1 < ROW_LEN) // 右下に置くから+2のチェック
                {
                    if (this->_board._board[y + 1][x + 1] == '-') // [\]下方向が空
                    {

                        if (this->_board._board[y + 2][x + 1] != '-') // [\]下方向に置ける
                        {
                            this->_toWin = x - 1;
                            return true;
                        }
                    }
                }
            }
            if (sign_y == +1 && sign_x == -1) // [/]下
            {
                if (y + 4 < COL_LEN && x - 3 >= 0)
                {
                    if (this->_board._board[y + 3][x - 3] == '-') // [\]下方向が空
                    {
                        if (this->_board._board[y + 4][x - 3] != '-') // [\]下方向に置ける
                        {
                            this->_toWin = x - 3;
                            return true;
                        }
                    }
                }
                if (y - 1 >= 0 && x + 1 < ROW_LEN)
                {
                    if (this->_board._board[y - 1][x + 1] == '-') // [/]上方向が空
                    {
                        if (this->_board._board[y][x + 1] != '-') // [/]上方向に置ける
                        {
                            this->_toWin = x + 1;
                            return true;
                        }
                    }
                }
            }
            if (sign_y == -1 && sign_x == +1) // [/]上
            {
                if (y - 3 >= 0 && x + 3 < ROW_LEN)
                {
                    if (this->_board._board[y - 3][x + 3] == '-') // [/]上方向が空
                    {
                        if (this->_board._board[y - 2][x + 3] != '-') // [/]上方向に置ける
                        {
                            this->_toWin = x + 3;
                            return true;
                        }
                    }
                }
                if (y + 2 < ROW_LEN && x - 1 >= 0) // [/]下
                {
                    if (this->_board._board[y + 1][x - 1] == '-') // [/]上方向が空
                    {
                        if (this->_board._board[y + 2][x - 1] != '-') // [/]上方向に置ける
                        {
                            this->_toWin = x - 1;
                            return true;
                        }
                    }
                }
            }
        }
        i += 1;
    }
    return false;
}

bool Cpu::toWinInaADiagonally(const char &piece)
{
    for (int y = 0; y < COL_LEN; y++)
    {
        for (int x = 0; x < ROW_LEN; x++)
        {
            if (this->_board._board[y][x] == piece)
            {
                if (toWinCheck4Pattern(x, y, +1, +1)) return true; // [\]下
                if (toWinCheck4Pattern(x, y, +1, -1)) return true; // [/]上
                if (toWinCheck4Pattern(x, y, -1, +1)) return true; // [/]下
                if (toWinCheck4Pattern(x, y, -1, -1)) return true; // [\]上
            }
        }
    }
    return false;
}

bool Cpu::toWinOrRand(const char &piece)
{
    if (toWinInARow(piece))         return true;
    if (toWinInACol(piece))         return true;
    if (toWinInaADiagonally(piece)) return true;
    return false;
}

void Cpu::selectNumber()
{
    while (true)
    {
        this->_board.showBoard();
        printf("TURN CPU (%c)\n", this->_piece);
//        std::this_thread::sleep_for(std::chrono::milliseconds(TIME_TO_SLEEP));
        if (toWinOrRand(this->_piece))
            this->_random = this->_toWin;
        else
        {
            std::random_device rnd;
            this->_random = rnd() % 7;
        }
        if (this->_board.isValidInput(std::to_string(this->_random + 1)))
        {
            this->_board.setPiece(this->_random, this->_piece);
            break ;
        }
    }
}

