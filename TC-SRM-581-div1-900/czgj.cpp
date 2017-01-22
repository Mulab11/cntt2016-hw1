/*
	State-compressed brute force
*/

#include <bits/stdc++.h>
#define rep(i, l, r) for (int i = (l); i <= (r); ++i)
#define red(i, r, l) for (int i = (r); i >= (l); --i)
using namespace std;
typedef long long LL;
const int MAXN = 15;
int pow3[MAXN] = {1};
bool a[MAXN][MAXN];
int ret, n, m;
void move(int r, int c, int type){
	if (r) a[r - 1][c] ^= 1;
	if (c) a[r][c - 1] ^= 1;
	if (r < n - 1) a[r + 1][c] ^= 1;
	if (c < m - 1) a[r][c + 1] ^= 1;
	if (type) a[r][c] ^= 1;
}
void dfs(int r, int c, int vis, int mask, int rowtype, int d){
	if (r == n){
		// judge and quit
		bool ok = 1;
		rep(i, 0, m - 1) if (a[n - 1][i]) {ok = 0; break;}
		if (ok && (ret < 0 || ret > d)) ret = d;
		return;
	}
	// when in the first row, or the upper grid is '0', we have the choice to make no move.
	if (!r || !a[r - 1][c]) dfs(r + (c == m - 1), (c + 1) % m, vis, mask, (c < m - 1 ? rowtype : -1), d);
	// when in the first row, or the upper is '1', we can make a move.
	if (!r || a[r - 1][c]){
		rep(type, 0, 1){
			// constraints : row and column
			if ((rowtype != -1 && rowtype != type) || (vis >> c & 1 && (mask >> c & 1) ^ type)) continue;
			move(r, c, type); // move
			dfs(r + (c == m - 1), (c + 1) % m, vis | 1 << c, mask | type << c, (c < m - 1 ? type : -1), d + 1);
			move(r, c, type); // undo
		}
	}
}
class YetAnotherBoardGame {
	public:
	int minimumMoves(vector <string> board) {
		n = board.size(); m = board[0].size(); ret = -1;
		rep(i, 0, n - 1) rep(j, 0, m - 1) a[i][j] = (board[i][j] == 'W');
		dfs(0, 0, 0, 0, -1, 0);
		return ret;
	}
};

/*
	Error : 0x000030A2 IQ_Catch_Chicken
*/
