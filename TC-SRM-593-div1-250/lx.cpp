#include <bits/stdc++.h>

#define rep(i, x, y) for (int i = (x), _ = (y); i <= _; ++i)
#define down(i, x, y) for (int i = (x), _ = (y); i >= _; --i)
#define x first
#define y second
#define mp make_pair
#define pb push_back
#define bin(x) (1<<(x))
#define LX_JUDGE

using namespace std;
typedef long long LL;
typedef pair<int, int> pii;

template<typename T> inline void upmax(T &x, T y) { x < y ? x = y : 0; }
template<typename T> inline void upmin(T &x, T y) { x > y ? x = y : 0; }

const int inf = 0x3f3f3f3f;
const int N = 1e5 + 10;

const int dx[] = {-1, 0, -1, 1, 0, 1};
const int dy[] = {0, 1, 1, 0, -1, -1};

class HexagonalBoard {
private :
	vector<string> board;
	int n;
	inline bool inBoard(int x, int y) {
		return x >= 0 && x < n && y >= 0 && y < n;
	}
	inline bool check_0() {
		rep (i, 0, n-1) rep (j, 0, n-1) {
			if (board[i][j] == 'X') {
				return 0;
			}
		}
		return 1;
	}
	inline bool check_1() {
		rep (i, 0, n-1) rep (j, 0, n-1) {
			if (board[i][j] == 'X') {
				rep (d, 0, 5) {
					int _i = i + dx[d], _j = j + dy[d];
					if (inBoard(_i, _j) && board[_i][_j] == 'X') {
						return 0;
					}
				}
			}
		}
		return 1;
	}
	int vis[51][51];

	bool Dfs(int x, int y) {
		rep (d, 0, 5) {
			int _x = x + dx[d], _y = y + dy[d];
			if (inBoard(_x, _y) && board[_x][_y] == 'X') {
				if (vis[_x][_y] == -1) {
					vis[_x][_y] = vis[x][y] ^ 1;
					if (Dfs(_x, _y)) {
						return 1;
					}
				} else if (vis[_x][_y] == vis[x][y]) {
					return 1;
				}
			}
		}
		return 0;
	}

	inline bool check_2() {
		rep (i, 0, n-1) rep (j, 0, n-1) {
			vis[i][j] = -1;
		}
		rep (i, 0, n-1) rep (j, 0, n-1) {
			if (board[i][j] == 'X' && vis[i][j] == -1) {
				vis[i][j] = 0;
				if (Dfs(i, j)) {
					return 0;
				}
			}
		}
		return 1;
	}
public :
	int minColors(vector<string> board) {
		this->board = board;
		n = board.size();
		if (check_0())  return 0;
		if (check_1())  return 1;
		if (check_2())  return 2;
		return 3;
	}
};
