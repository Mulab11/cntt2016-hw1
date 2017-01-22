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

const int mod = 1e9 + 7;
const int N = 55;

inline void upd(int &x, int y) {
	(x += y) >= mod ? x -= mod : 0;
}
inline int inc(int x, int y) {
	return (x += y) >= mod ? x - mod : x;
}
inline int dec(int x, int y) {
	return (x -= y) < 0 ? x + mod : x;
}

class TwoConvexShapes {
private :
	char a[N][N];
	int f[N][N], can[N][N], ans, n, m;

	void countInc() {
		rep (i, 0, m) f[0][i] = 1;
		rep (r, 1, n) {
			rep (i, 0, m) {
				f[r][i] = i ? f[r][i - 1] : 0;
				if (can[r][i]) upd(f[r][i], f[r - 1][i]);
			}
		}
		upd(ans, f[n][m]);
	}

	void countDec() {
		rep (i, 0, m) f[0][i] = 1;
		rep (r, 1, n) {
			down (i, m, 0) {
				f[r][i] = i < m ? f[r][i + 1] : 0;
				if (can[r][i]) upd(f[r][i], f[r - 1][i]);
			}
		}
		upd(ans, f[n][0]);
	}

	void countAllCol() {
		rep (i, 0, m) {
			int flag = 1;
			rep (j, 1, n) {
				if (!can[j][i]) {
					flag = 0;
					break ;
				}
			}
			ans -= flag;
		}
	}
	void countAllRow() {
		rep (i, 0, n) {
			int flag = 1;
			rep (j, 1, i) {
				if (!can[j][m]) {
					flag = 0;
					break ;
				}
			}
			if (flag) {
				rep (j, i + 1, n) {
					if (!can[j][0]) {
						flag = 0;
						break ;
					}
				}
			}
			ans -= flag;
		}
	}
	void countAllBoard() {
		rep (i, 1, n) rep (j, 1, m) {
			if (a[i][j] == 'W') {
				return ;
			}
		}
		ans++;
	}

	void letsCount() {
		rep (i, 1, n) rep (j, 0, m) {
			can[i][j] = 1;
			rep (k, 1, j) if (a[i][k] == 'W') {
				can[i][j] = 0;
				break ;
			}
			if (can[i][j]) {
				rep (k, j + 1, m) if (a[i][k] == 'B') {
					can[i][j] = 0;
					break ;
				}
			}
		}
		countInc();
		countDec();
		countAllCol();
		countAllRow();
		countAllBoard();
	}
public :
	//计数，容斥原理，DP
	int countWays(vector<string> grid) {
		n = grid.size();
		m = grid[0].size();
		rep (i, 1, n) rep (j, 1, m) {
			a[i][j] = grid[i - 1][j - 1];
		}
		letsCount();
		rep (i, 1, n) rep (j, 1, m) {
			a[i][j] = a[i][j] == 'B' ? 'W' : (a[i][j] == 'W' ? 'B' : '?');
		}
		letsCount();
		return (ans + mod) % mod;
	}
};
