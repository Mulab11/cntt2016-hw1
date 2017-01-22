#include <bits/stdc++.h>
#define rep(i, l, r) for (int i = (l); i <= (r); ++i)
#define red(i, r, l) for (int i = (r); i >= (l); --i)
#define MEM(x, y) memset(x, y, sizeof x)
using namespace std;
typedef long long LL;
const int dx[4] = {1, 0, -1, 0};
const int dy[4] = {0, 1, 0, -1};
const int MAXN = 63;
const int NN = MAXN * MAXN;
void cmax(int &a, int b){a = max(a, b);}
void cmin(int &a, int b){a = min(a, b);}
class Tunnels {
	public:
	vector<string> st;
	int full[MAXN];
	int n, m;
	bool check(int x, int y) {
		return x >= 0 && y >= 0 && x < n && y < m && st[x][y] == 'X';
	}
	int mark[MAXN][MAXN], cnt;
	bool lu[MAXN], ru[MAXN], ld[MAXN],rd[MAXN];
	void dfs(int x,int y) {
		if (!check(x, y) || mark[x][y] != -1) return;
		mark[x][y] = cnt;
		rep(i, 0, 3) dfs(x + dx[i], y + dy[i]);
	}
	int dp() {
		static int f[MAXN][MAXN][MAXN]; MEM(f, 0xf0); f[n][0][0] = 0;
		red(i, n - 1, 0) rep(lc, 0, i) rep(rc, 0, i) rep(x, -1, 1) rep(y, -1, 1){
			if ((x == -1 && !lu[i]) || (x == 1 && !ld[i])) continue;
			if ((y == -1 && !ru[i]) || (y == 1 && !rd[i])) continue;
			if (full[i] && x * y == 1) continue;
			if (lc + x >= 0 && rc + y >= 0) cmax(f[i][lc][rc], f[i + 1][lc + x][rc + y] + (x == -1) + (y == -1));
		}
		return f[0][0][0];
	}
	int deg[MAXN][MAXN];
	int minr[NN], maxr[NN];
	int minimumTunnels(vector<string> frame) {
		st = frame, n = st.size(), m = st[0].size();
		MEM(mark, 0xff);
		rep(i, 0, n - 1) rep(j, 0, m - 1) if (mark[i][j] == -1 && st[i][j] == 'X') dfs(i, j), ++cnt;
		if (m == 1) return cnt ? 1 : 0;
		rep(i, 0, n - 1) rep(j, 0, m - 1) rep(k, 0, 3)
			deg[i][j] += (check(i + dx[k], j + dy[k]));
		MEM(minr, 0x3f); MEM(maxr, 0);
		rep(i, 0, n - 1) rep(j, 0, m - 1) if (st[i][j] == 'X') 
			cmin(minr[mark[i][j]],i), cmax(maxr[mark[i][j]],i);
		rep(i, 0, n - 1){
			if (st[i][0] == 'X' && deg[i][0] <= 1){
				lu[i] = (i == minr[mark[i][0]]);
				ld[i] = (i == maxr[mark[i][0]]);
			}
			if (st[i][m - 1] == 'X' && deg[i][m - 1] <= 1){
				ru[i] = (i == minr[mark[i][m - 1]]);
				rd[i] = (i == maxr[mark[i][m - 1]]);
			}
		}
		rep(i, 1, n - 1){
			if (st[i][0] == 'X' && i == minr[mark[i][0]] && mark[i][0] == mark[i + 1][0] && maxr[mark[i][0]] == i + 1)
				if (lu[i]) ld[i + 1] = 0;
			if (st[i][m - 1] == 'X' && i == minr[mark[i][m - 1]] && mark[i][m - 1] == mark[i + 1][m - 1] && maxr[mark[i][m - 1]] == i + 1)
				if (ru[i]) rd[i + 1] = 0;
		}
		rep(i, 0, n - 1) if (mark[i][0] == mark[i][m - 1] && mark[i][0] != -1) full[i] = 1;
		rep(i, 1, n - 1) {
			int l = mark[i][0], r = mark[i][m - 1];
			if (l != r)	{
				if (l != -1 && minr[l] == maxr[l]) ld[i] = 0;
				if (r != -1 && minr[r] == maxr[r]) rd[i] = 0;
			}
		}
		return cnt - dp();
	}
};

