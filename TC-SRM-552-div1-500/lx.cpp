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
const int N = 31;

class FoxAndFlowerShopDivOne {
private :
	int n, m, K;
	int cost[N][N];

	int sum[N][N], num[N][N];
	int f[N][1805], g[N][1805];

	//二维前缀和查询
	inline int Get1(int x1, int y1, int x2, int y2) {
		return sum[x2][y2] - sum[x2][y1 - 1] - sum[x1 - 1][y2] + sum[x1 - 1][y1 - 1];
	}
	inline int Get2(int x1, int y1, int x2, int y2) {
		return num[x2][y2] - num[x2][y1 - 1] - num[x1 - 1][y2] + num[x1 - 1][y1 - 1];
	}

	int Solve() {
		int ans = -inf;
		rep (i, 1, n) rep (j, 1, m) {		//预处理二维前缀和
			sum[i][j] = sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1];
			num[i][j] = num[i - 1][j] + num[i][j - 1] - num[i - 1][j - 1];
			sum[i][j] += cost[i - 1][j - 1];
			num[i][j] += cost[i - 1][j - 1] != 0;
		}
		int Lim = n * m;
		rep (i, 1, n) {
			if (i > 1) {
				memcpy(f[i], f[i - 1], sizeof(f[i]));
			} else {
				memset(f[i], -0x3f, sizeof(f[i]));
			}
			rep (t, 1, i) rep (l, 1, m) rep (r, l, m) {
				int cost = Get1(t, l, i, r);
				int val = Get2(t, l, i, r);
				upmax(f[i][cost + Lim], val);
			}
		}
		down (i, n, 1) {
			if (i < n) {
				memcpy(g[i], g[i + 1], sizeof(g[i]));
			} else {
				memset(g[i], -0x3f, sizeof(g[i]));
			}
			rep (t, i, n) rep (l, 1, m) rep (r, l, m) {
				int cost = Get1(i, l, t, r);
				int val = Get2(i, l, t, r);
				upmax(g[i][cost + Lim], val);
			}
		}
		rep (i, 1, n-1) {
			rep (j, 0, Lim*2) rep (k, max(Lim*2-K-j, 0), min(Lim*2+K-j, Lim*2)) {
				upmax(ans, f[i][j] + g[i + 1][k]);
			}
		}
		rep (i, 1, m) {
			if (i > 1) {
				memcpy(f[i], f[i - 1], sizeof(f[i]));
			} else {
				memset(f[i], -0x3f, sizeof(f[i]));
			}
			rep (t, 1, i) rep (d, 1, n) rep (u, d, n) {
				int cost = Get1(d, t, u, i);
				int val = Get2(d, t, u, i);
				upmax(f[i][cost + Lim], val);
			}
		}
		down (i, m, 1) {
			if (i < m) {
				memcpy(g[i], g[i + 1], sizeof(g[i]));
			} else {
				memset(g[i], -0x3f, sizeof(g[i]));
			}
			rep (t, i, m) rep (d, 1, n) rep (u, d, n) {
				int cost = Get1(d, i, u, t);
				int val = Get2(d, i, u, t);
				upmax(g[i][cost + Lim], val);
			}
		}
		rep (i, 1, m-1) {
			rep (j, 0, Lim*2) rep (k, max(Lim*2-K-j, 0), min(Lim*2+K-j, Lim*2)) {
				upmax(ans, f[i][j] + g[i + 1][k]);
			}
		}
		return ans;
	}
public :
	//两个矩形可以被水平或者垂直的一条分割线分开
	//用DP预处理出前缀和后缀最优矩形，枚举分割线，更新答案即可
	int theMaxFlowers(vector<string> field, int maxDiff) {
		n = field.size();
		m = field[0].size();
		K = maxDiff;
		rep (i, 0, n-1) rep (j, 0, m-1) {
			if (field[i][j] == 'L') {
				cost[i][j] = 1;
			} else if (field[i][j] == 'P') {
				cost[i][j] = -1;
			}
		}
		int ans = Solve();
		return ans < 0 ? -1 : ans;
	}
};
