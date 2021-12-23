#include <iostream>
#include <set>
#include <vector>
#define vek vector<int>
#define cc continue
using namespace std;
int brd[15][15];
set<pair<int, int>> blank;
pair<int, int> geth(int index) {
	set<pair<int, int>>::iterator it = blank.begin();
	advance(it, index);
	return *it;
}
int check_fills(int a, int b, int c, int board[15][15]) {
	for (int i = 0; i < 9; i++)if (board[a][i] == c || board[i][b] == c)return 0;
	return 1;
}
int check_mini_square(int board[15][15], int a, int b) {
	int used[15] = {};
	for (int i = a; i < 3 + a; i++)for (int j = b; j < 3 + b; j++) {
		if (board[i][j] == -1)cc;
		if (used[board[i][j]])return 0;
		used[board[i][j]] = 1;
	}
	return 1;
}
int check_full_square(int a, int b, int c, int board[15][15]) {
	board[a][b] = c;
	for (int i = 0; i < 3; i++)for (int j = 0; j < 3; j++) {
		if (!check_mini_square(board, i * 3, j * 3))return 0;
	}
	return 1;
}
void solve(int br[15][15], int last_index) {
	if (last_index == blank.size()) {
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++) {
				if (brd[i][j] == -1) {
					cout << "\033[1;31m" << br[i][j] << "\033[0m ";
					cc;
				}
				cout << br[i][j] << " ";
			}
			cout << endl;
		}
		exit(0);
	}
	pair<int, int> cords = geth(last_index);
	for (int i = 1; i < 10; i++) {
		if (check_fills(cords.first, cords.second, i, br) && check_full_square(cords.first, cords.second, i, br)) {
			int copy[15][15];
			for (int i = 0; i < 15; i++)for (int j = 0; j < 15; j++)copy[i][j] = br[i][j];
			copy[cords.first][cords.second] = i;
			solve(copy, last_index + 1);
		}
	}
}
int main(void) {
	for (int i = 0; i < 9; i++)for (int j = 0; j < 9; j++) {
		int a;
		cin >> a;
		if (a == -1)blank.insert({i, j});
		brd[i][j] = a;
	}
	cout << endl;
	solve(brd, 0);
	cout << "No solution";
}
