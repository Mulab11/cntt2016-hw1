#include <bits/stdc++.h>
#define rep(i, l, r) for(int _r = r, i = l; i <= _r; ++i)
#define red(i, r, l) for(int _l = l, i = r; i >= _l; --i)
#define debug(x) cerr << #x << " = " << x << endl
#define MEM(x, y) memset(x, y, sizeof(x))
#define X first
#define Y second

using namespace std;
typedef long long LL;
typedef pair<int, int> PI;
typedef vector<int> VI;
const int MAXN = 55;
const int MAXK = 333;
const int NN = MAXN * MAXN;
const LL MOD = 1e9 + 7;
const int dx[4] = {0, 1, 0, -1};
const int dy[4] = {1, 0, -1, 0};
double C(int a, int b, int k){
	double ret = 1;
	rep(i, 0, k - 1) ret *= (double)(a - i) / (a + b - i);
	return ret;
}
int dis[MAXK][MAXK];
bool cmp(int x0, int y0, int x1, int y1){
	if (dis[x0][y0] != dis[x1][y1]) return dis[x0][y0] < dis[x1][y1];
	if (x0 > y0) swap(x0, y0);
	if (x1 > y1) swap(x1, y1);
	return PI(x0, y0) > PI(x1, y1);
}
int dd[MAXN][MAXN];
int px[MAXK], py[MAXK];
int fa[NN], sz[NN], qx[NN], qy[NN];
class Orienteering{
	public:
	double expectedLength(vector<string> field, int k){
		int n = field.size(), m = field[0].size(), pc = 0;
		double ret1 = 0, ret2 = 0;
		rep(i, 0, n - 1) rep(j, 0, m - 1) if (field[i][j] == '*'){
			++pc; px[pc] = i; py[pc] = j;
			MEM(dd, 0); dd[i][j] = 1;
			int l = 0, r = 0; qx[0] = i; qy[0] = j;
			for (; l <= r; ++l)
				rep(d, 0, 3){
					int tx = qx[l] + dx[d], ty = qy[l] + dy[d];
					if (tx >= 0 && tx < n && ty >= 0 && ty < m && !dd[tx][ty] && field[tx][ty] != '#'){
						++r; qx[r] = tx; qy[r] = ty;
						dd[tx][ty] = dd[qx[l]][qy[l]] + 1;
						if (pc == 1) fa[r] = l;
					}
				}
			if (pc == 1){
				red(i, r, 0){
					if (field[qx[i]][qy[i]] == '*') ++sz[i];
					if (i) sz[fa[i]] += sz[i];
				}
				rep(i, 1, r) ret1 += 1 - C(sz[i], sz[0] - sz[i], k) - C(sz[0] - sz[i], sz[i], k);
			}
			rep(i, 1, pc - 1) dis[pc][i] = dis[i][pc] = dd[px[i]][py[i]] - 1;
		}
		rep(i, 1, pc) rep(j, i + 1, pc){
			int cnt = 0;
			rep(k, 1, pc) if (k != i && k != j && cmp(i, k, i, j) && cmp(j, k, i, j)) ++cnt;
			ret2 += (double)dis[i][j] * (k - 1) * k / pc / (pc - 1) * C(cnt, pc - cnt - 2, k - 2);
		
		}
		return ret1 * 2 - ret2;
	}
};

