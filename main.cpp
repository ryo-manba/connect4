#include <bits/stdc++.h>
using namespace std;
using ll = long long;
struct fast_ios { fast_ios(){ cin.tie(nullptr), ios::sync_with_stdio(false), cout << fixed << setprecision(20); }; } fast_ios_;
template<class T> inline bool chmax(T& a, T b) { if (a < b) { a = b; return true; } return false; }
template<class T> inline bool chmin(T& a, T b) { if (a > b) { a = b; return true; } return false; }

#define PLAYER1 'o'
#define PLAYER2 'x'
#define ROW_LEN 7
#define COL_LEN 6

// 縦6横7
string board[COL_LEN] = {
	"-------",
	"-------",
	"-------",
	"-------",
	"-------",
	"-------"};


bool is_valid_input(string s)
{
	if (s.length() != 1) return false;
	if (!('1' <= s[0] && s[0] <= '7')) return false;

	int idx = s[0] - '0' - 1;

	for (int i = 0; i < COL_LEN; i++)
	{
		if (board[i][idx] == '-') // コマが置ける
			return true;
	}
	return false;
}

void print_board()
{
	for (int i = 0; i < COL_LEN; i++)
	{
		cout << board[i] << endl;
	}
	cout << "1234567" << endl;
}

bool is_win_row()
{
	for (int y = 0; y < COL_LEN; y++)
	{
		int cnt = 0;
		char before = '*';
		for (int x = 0; x < ROW_LEN; x++)
		{
			if (board[y][x] == PLAYER1 || board[y][x] == PLAYER2)
				cnt += 1;
			if (before != board[y][x])
			{
				if (board[y][x] == PLAYER1 || board[y][x] == PLAYER2)
					cnt = 1;
				else cnt = 0;
			}
			before = board[y][x];
			if (cnt == 4) return true;
		}
	}
	return false;
}

bool is_win_col()
{
	for (int x = 0; x < ROW_LEN; x++)
	{
		char before = '*';
		int cnt = 0;
		for (int y = 0; y < COL_LEN; y++)
		{
			if (board[y][x] == PLAYER1 || board[y][x] == PLAYER2)
				cnt += 1;
			if (before != board[y][x])
			{
				if (board[y][x] == PLAYER1 || board[y][x] == PLAYER2)
					cnt = 1;
				else cnt = 0;
			}
			before = board[y][x];
			if (cnt == 4) return true;
		}
	}
	return false;
}

bool is_win_diagonally_4_pattern(int x, int y, int sign_x, int sign_y)
{
	int i = 1;
	int cnt = 1;
	char c = board[y][x];

	while (true)
	{
		if (sign_y == -1 && y - i == -1)      break;
		if (sign_x == -1 && x - i == -1)      break;
		if (sign_y == +1 && y + i == COL_LEN) break;
		if (sign_x == +1 && x + i == ROW_LEN) break;

		if (board[y + (i * sign_y)][x + (i * sign_x)] != c)
			break;
		cnt += 1;
		if (cnt == 4) return true;
		i += 1;
	}
	return false;
}

bool is_win_diagonally()
{
	for (int y = 0; y < COL_LEN; y++)
	{
		for (int x = 0; x < ROW_LEN; x++)
		{
			if (board[y][x] == PLAYER1 || board[y][x] == PLAYER2)
			{
				if (is_win_diagonally_4_pattern(x, y, +1, +1)) return true; // [\]下
				if (is_win_diagonally_4_pattern(x, y, +1, -1)) return true; // [/]上
				if (is_win_diagonally_4_pattern(x, y, -1, +1)) return true; // [/]下
				if (is_win_diagonally_4_pattern(x, y, -1, -1)) return true; // [\]上
			}
		}
	}
	return false;
}

bool is_game_set()
{
	if (is_win_row())        return true;
	if (is_win_col())        return true;
	if (is_win_diagonally()) return true;
	return false;
}

void game_loop()
{
	int id = 1;
	int turn = 0;
	const int max_turn = ROW_LEN * COL_LEN;
	char c;

	while (turn < max_turn)
	{
		printf("Player%dの番です.\n", id);
		print_board();
		cout << "(1 ~ 7)を入力してください." << endl;
		string s;
		cin >> s;
		if (!is_valid_input(s))
			continue;
		if (id % 2) c = PLAYER1;
		else c = PLAYER2;
		for (int i = 5; i >= 0; i--)
		{
			if (board[i][s[0]-'0'-1] == '-')
			{
				board[i][s[0]-'0'-1] = c;
				break ;
			}
		}
		if (is_game_set())
		{
			print_board();
			printf("Player%dの勝利です！\n", id);
			return;
		}
		if (id == 1) id = 2;
		else if (id == 2) id = 1;
		turn += 1;
	}
	print_board();
	printf("引き分けです！\n");
}

int main()
{
	int id = 1;
	cout << "4目並べスタート" << endl;
	game_loop();
	return 0;
}
