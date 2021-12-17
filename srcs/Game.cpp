#include "Game.hpp"

#include "Const.hpp"

#define MODE_PVP "1"
#define MODE_EASY "2"
#define MODE_NORMAL "3"
#define MODE_HARD "4"
#define EASY 25
#define NORMAL 100
#define HARD 500

int g_sampleSize;
int g_maxDepth;

Game::Game() { std::cout << ("Welcome to Connect 4!") << std::endl; }

Game::~Game() {}

void Game::printResult(const char *color, const char *message) const
{
    printf("%s%s%s%s\n", BOLD, color, message, RESET);
}

void Game::PvE(const int &mode)
{
    g_sampleSize = mode;
    g_maxDepth   = mode * ROW_LEN;
    Board board;
    Player player(1, board);
    Cpu cpu(2, board);

    for (int i = 0; i < MAX_TURN; i += 2)
    {
        player.selectNumber();
        if (board.checkGame(PIECE1))
        {
            board.showBoard();
            printResult(GREEN, "YOU WIN!");
            return;
        }
        cpu.selectNumber();
        if (board.checkGame(PIECE2))
        {
            board.showBoard();
            printResult(RED, "YOU LOSE!");
            return;
        }
    }
    board.showBoard();
    printResult(YELLOW, "DRAW!");
}

void Game::PvP()
{
    Board board;
    Player players[2] = {{1, board}, {2, board}};

    for (int i = 0; i < MAX_TURN; i += 2)
    {
        for (int j = 0; j < 2; j += 1)
        {
            players[j].selectNumber();
            char piece = (j == 0) ? PIECE1 : PIECE2;
            if (board.checkGame(piece))
            {
                board.showBoard();
                std::cout << BOLD << GREEN;
                printf("Player%d WIN!\n", j + 1);
                std::cout << RESET;
                return;
            }
        }
    }
    board.showBoard();
    printResult(YELLOW, "DRAW!");
}

void Game::selectMode()
{
    while (true)
    {
        printf(
            ""
            "Please select the mode :\n"
            "  [1] 1P vs 2P\n"
            "  [2] 1P vs CPU [easy]\n"
            "  [3] 1P vs CPU [normal]\n"
            "  [4] 1P vs CPU [hard]\n\n");
        std::cout << " > ";
        std::cin >> this->_mode;
        if (this->_mode == MODE_PVP || this->_mode == MODE_EASY ||
            this->_mode == MODE_NORMAL || this->_mode == MODE_HARD)
            break;
    }
}

void Game::Start()
{
    selectMode();
    if (this->_mode == MODE_PVP)    PvP();
    if (this->_mode == MODE_EASY)   PvE(EASY);
    if (this->_mode == MODE_NORMAL) PvE(NORMAL);
    if (this->_mode == MODE_HARD)   PvE(HARD);
}
