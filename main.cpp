#include <bits/stdc++.h>
using namespace std;
using ll = long long;
struct fast_ios { fast_ios(){ cin.tie(nullptr), ios::sync_with_stdio(false), cout << fixed << setprecision(20); }; } fast_ios_;
template<class T> inline bool chmax(T& a, T b) { if (a < b) { a = b; return true; } return false; }
template<class T> inline bool chmin(T& a, T b) { if (a > b) { a = b; return true; } return false; }

#define PLAYER1 'o'
#define PLAYER2 'x'

// 縦6横7
string board[6] = {
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

	for (int i = 0; i < 6; i++)
	{
		if (board[i][idx] == '-') // コマが置ける
		{
			return true;
		}
	}

	return false;
}

void print_board()
{
	cout << " 1234567" << endl;
	for (int i = 0; i < 6; i++)
	{
		cout << i + 1;
		cout << board[i] << endl;
	}
}

bool is_valid_row()
{
	int cnt = 0;
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			if (board[i][j] == PLAYER1)
			{
				if (cnt > 0 && board[i][j-1] == PLAYER1) // 一個前のコマが同じかどうか
					cnt += 1;
				else
					cnt = 0;
			}
			if (board[i][j] == PLAYER2)
			{
				if (cnt > 0 && board[i][j-1] == PLAYER2)
					cnt += 1;
				else
					cnt = 0;
			}
			if (cnt == 4)
			{
				return true;
			}
		}
	}
	return false;
}

bool is_valid_col()
{
	int cnt = 0;
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			if (board[j][i] == PLAYER1)
			{
				if (cnt > 0 && board[j-1][i] == PLAYER1) // 一個前のコマが同じかどうか
					cnt += 1;
				else
					cnt = 0;
			}
			if (board[j][i] == PLAYER2)
			{
				if (cnt > 0 && board[j-1][i] == PLAYER2)
					cnt += 1;
				else
					cnt = 0;
			}
			if (cnt == 4)
			{
				return true;
			}
		}
	}
	return false;
}

bool is_game_set()
{
	int i = 0;
	if (is_valid_row) return true;
	if (is_valid_col) return true;
//	if (is_check_naname) return true;
	return false;
}

void game_loop()
{
	int id = 1;

	while (true)
	{
		printf("Player%dの番です.\n", id);
		print_board();
		cout << "(1 ~ 7)を入力してください." << endl;
		string s;
		cin >> s;
		if (is_valid_input(s))
		{
			char c;
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
		}
		else
			continue;
		// if (is_game_set())
		// {
		// 	print_board();
		// 	printf("Player%dの勝利です！\n", id);
		// 	return 0;
		// }
		if (id == 1) id = 2;
		else if (id == 2) id = 1;
	}
}

int main()
{
	int id = 1;
	cout << "4目並べスタート" << endl;
	game_loop();
	return 0;
}
