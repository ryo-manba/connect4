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

int score[7];

// ランダムに複数回戦わせて最も勝利数が多かったものを選択する
void montecarlo(int idx, int depth, Board board)
{
    Board b = board;
    Cpu cpu1(1, b);
    Cpu cpu2(2, b);

    if (depth >= 700)
    {
        return ;
    }

    // 1番最初の手は決め打ち
    if (cpu2.selectNumber(idx) == false) // もしコマが置けなかった場合
    {
        depth += 100; // 100進めて次のidxに進む
        if (depth >= 700) // 0~6までを100回ずつ試したら戻る
            return ;
        idx = depth / 100; // 0~99までは0, 100~199までは1,...,600~699までは6
        montecarlo(idx, depth, board);
        return;
    }
    // ランダムに勝敗がつくまで戦う
    // (1〜7)を各100回ランダムに戦わせて、勝利数が最も多かったものを選択
    while (true)
    {
        if (b.checkGame(PIECE2)) // CPUが勝利した場合
        {
            score[idx] += 1;
            break ;
        }
        if (b.isFull()) break;
        cpu1.selectNumber(-1);
        if (b.checkGame(PIECE1) || b.isFull()) // Userが勝利した場合 or 引き分けの場合
        {
            break ;
        }
        cpu2.selectNumber(-1);
    }
    depth += 1;
    idx = depth / 100; // 0~99までは0, 100~199までは1,...,600~699までは6
    montecarlo(idx, depth, board);
}

bool Cpu::selectNumber(int idx)
{
    if (idx == -2)
    {
        this->_board.showBoard();
        printf("TURN CPU (%c)\n", this->_piece);
    }
    while (true)
    {
//        std::this_thread::sleep_for(std::chrono::milliseconds(TIME_TO_SLEEP));
        std::random_device rnd;
        this->_random = rnd() % 7;
        if (idx >= 0) // もしidx指定があった場合はそれを選択する
        {
            this->_random = idx;
            if (!this->_board.isValidInput(std::to_string(this->_random + 1)))
            {
                return false;
            }
            else
            {
                this->_board.setPiece(this->_random, this->_piece);
                return true;
            }
        }
        else if (idx == -1) // モンテカルロ法内の処理
        {
            if (this->_board.isValidInput(std::to_string(this->_random + 1)))
            {
                this->_board.setPiece(this->_random, this->_piece);
                break ;
            }
        }
        else if (idx == -2) // モンテカルロを使う場合
        {
            for (int i = 0; i < 7; i++)
            {
                score[i] = 0;
            }
            montecarlo(0, 0, this->_board);
            int maxScore = 0;
            int maxIdx = 0;
            for (int i = 0; i < 7; i++)
            {
                printf("score[%d] = %d\n", i,score[i]);
                if (score[i] > maxScore) // 最大値を越した場合選択する
                {
                    maxIdx = i;
                    maxScore = score[i];
                }
            }
            if (maxScore != 0)
            {
                std::cout << maxIdx << std::endl;
                this->_board.setPiece(maxIdx, this->_piece);
                break ;
            }
            idx = -1;
        }
    }
    return true;
}

