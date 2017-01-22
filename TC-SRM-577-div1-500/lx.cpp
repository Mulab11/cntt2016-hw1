#include <bits/stdc++.h>

#define rep(i, x, y) for (int i = (x), _ = (y); i <= _; ++i)
#define down(i, x, y) for (int i = (x), _ = (y); i >= _; --i)
#define x first
#define y second
#define mp make_pair
#define pb push_back
#define LX_JUDGE

using namespace std;
typedef long long LL;

template<typename T> inline void upmax(T & x, T y) { x < y ? x = y : 0; }
template<typename T> inline void upmin(T & x, T y) { x > y ? x = y : 0; }

const int inf = 0x3f3f3f3f;

class EllysChessboard {
public :
	int w[21][21];
	int dp[21][21][21][21];

	int rec(int Minx, int Maxx, int Miny, int Maxy) {
		int & ans = dp[Minx][Maxx][Miny][Maxy];
		if (ans == -1) {
			if (Minx > Maxx || Miny > Maxy)  return ans = 0;
			ans = inf;
			int tmp = 0;
			rep (i, Miny, Maxy) if (w[Minx][i])
				tmp += max(max(Maxy - i, i - Miny), Maxx - Minx);
			upmin(ans, tmp + rec(Minx + 1, Maxx, Miny, Maxy));
			tmp = 0;
			rep (i, Miny, Maxy) if (w[Maxx][i])
				tmp += max(max(Maxy - i, i - Miny), Maxx - Minx);
			upmin(ans, tmp + rec(Minx, Maxx - 1, Miny, Maxy));
			tmp = 0;
			rep (i, Minx, Maxx) if (w[i][Miny])
				tmp += max(max(Maxx - i, i - Minx), Maxy - Miny);
			upmin(ans, tmp + rec(Minx, Maxx, Miny + 1, Maxy));
			tmp = 0;
			rep (i, Minx, Maxx) if (w[i][Maxy])
				tmp += max(max(Maxx - i, i - Minx), Maxy - Miny);
			upmin(ans, tmp + rec(Minx, Maxx, Miny, Maxy - 1));
		}
		return ans;
	}

	int minCost(vector<string>board) {
		rep (i, 0, 7) rep (j, 0, 7) {
			if (board[i][j] == '#')
				w[i + j][i - j + 7] = 1;
		}
		memset(dp, -1, sizeof(dp));
		return rec(0, 14, 0, 14);
	}
};
