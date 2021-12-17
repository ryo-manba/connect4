#include "Cpu.hpp"

#include <random>

#define SAMPLE_SIZE 100
#define MAX_DEPTH (SAMPLE_SIZE * 7)

int Cpu::score[ROW_LEN] = {};

Cpu::Cpu(int id, Board &board): _id(id), _board(board)
{
    if (_id == 1) _piece = PIECE1;
    else _piece = PIECE2;
}

Cpu::~Cpu() {}

void Cpu::playOut(const Board &board, int &depth)
{
    Board copyBoard = board;
    Cpu userCpu(1, copyBoard);
    Cpu cpu(2, copyBoard);
    int idx = depth / SAMPLE_SIZE;

    // 1番最初の手は決め打ちする
    if (cpu.selectIdx(idx) == false)
    {
        depth += SAMPLE_SIZE;
        if (depth >= MAX_DEPTH)
            return
        playOut(board, depth);
        return;
    }
    while (true)
    {
        if (copyBoard.checkGame(PIECE2)) // CPUが勝利した場合スコアを増やす
        {
            score[idx] += 1;
            break ;
        }
        if (copyBoard.isFull()) break; // 引き分けだった場合

        userCpu.selectRandom();
        if (copyBoard.checkGame(PIECE1) || copyBoard.isFull()) // Userが勝利した場合
        {
            break ;
        }
        cpu.selectRandom();
    }
}

// ランダムに複数回戦わせて最も勝利数が多かったものを選択する
void Cpu::montecarlo(const Board &board, int depth)
{
    if (depth >= MAX_DEPTH)
        return ;
    playOut(board, depth); // ランダムに戦わせる
    montecarlo(board, depth + 1); // depthが0~99までは0, 100~199までは1,...,600~699までは6
}

bool Cpu::selectIdx(int idx)
{
    if (!this->_board.isValidInput(std::to_string(idx + 1)))
    {
        return false;
    }
    this->_board.setPiece(idx, this->_piece);
    return true;
}

void Cpu::selectRandom()
{
    while (true)
    {
        std::random_device rnd;
        this->_idx = rnd() % 7;
        if (this->_board.isValidInput(std::to_string(this->_idx + 1)))
        {
            this->_board.setPiece(this->_idx, this->_piece);
            break ;
        }
    }
}

void Cpu::selectNumber()
{
    this->_board.showBoard();
    printf("TURN CPU (%c)\n", this->_piece);
    for (int i = 0; i < 7; i += 1)
    {
        score[i] = 0;
    }
    montecarlo(this->_board, 0);

    this->_maxScore = 0;
    this->_maxIdx = 0;
    for (int i = 0; i < 7; i += 1)
    {
//        printf("score[%d] = %d\n", i,score[i]);
        if (score[i] > this->_maxScore) // 最大スコアの手を選択する
        {
            this->_maxIdx = i;
            this->_maxScore = score[i];
        }
    }
    if (this->_maxScore == 0) // どこに置いても負ける or 引き分けの場合
    {
        selectRandom();
    }
    this->_board.setPiece(this->_maxIdx, this->_piece);
}
