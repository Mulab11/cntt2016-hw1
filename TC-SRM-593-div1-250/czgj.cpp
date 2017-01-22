/*
	board is empty --- 0
	no adjacent 'X's --- 1
	bipartite graph --- 2
	other --- 3
*/

#include <bits/stdc++.h>
using namespace std;

const int dx[6] = {-1, -1, 0, 0, 1, 1};
const int dy[6] = {0, 1, -1, 1, -1, 0};
class HexagonalBoard {
	public:
	int n;
	vector<string> board;
	bool vis[63][63], col[63][63];
	bool chkxy(int x, int y){
		return 0 <= x && x < n && 0 <= y && y < n;
	}
	bool check0(){
		for (int i = 0; i < n; ++i)
			for (int j = 0; j < n; ++j)
				if (board[i][j] == 'X')
					return 0;
		return 1;
	}
	bool check1(){
		for (int i = 0; i < n; ++i)
			for (int j = 0; j < n; ++j)
				if (board[i][j] == 'X')
					for (int d = 0; d < 6; ++d){
						int x = i + dx[d], y = j + dy[d];
						if (chkxy(x, y) && board[x][y] == 'X')
							return 0;
					}
		return 1;
	}
	bool dfs(int x, int y, bool c = 0){
		if (vis[x][y]) return col[x][y] == c;
		vis[x][y] = 1; col[x][y] = c;
		for (int d = 0; d < 6; ++d){
			int tx = x + dx[d], ty = y + dy[d];
			if (chkxy(tx, ty) && board[tx][ty] == 'X' && !dfs(tx, ty, !c))
				return 0;
		}
		return 1;
	}
	bool check2(){
		for (int i = 0; i < n; ++i)
			for (int j = 0; j < n; ++j)
				if (board[i][j] == 'X' && !vis[i][j] && !dfs(i, j))
					return 0;
		return 1;
	}
	int minColors(vector <string> brd) {
		board = brd; n = board.size();
		memset(vis, 0, sizeof vis);
		return check0() ? 0 : check1() ? 1 : check2() ? 2 : 3;
	}
};

/*
	Super Hexagon
		- Though I haven't played that game...
*/
