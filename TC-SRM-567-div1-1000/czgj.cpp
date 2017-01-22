/*
	Memorized search
*/

#include <bits/stdc++.h>
#define rep(i, l, r) for (int i = (l); i <= (r); ++i)
#define red(i, r, l) for (int i = (r); i >= (l); --i)
#define xx first
#define yy second
using namespace std;
typedef long long LL;
typedef pair<int, int> PI;
typedef vector<signed char> vc;
const int MAXN = 16;
const int MOD = 1e9 + 9;
vector<int> h;
vector<PI> vis;
map<vc, int> f[MAXN];
int n, w;
int dfs(int d, vc h0){
	if (d < 0) return 1;
	auto it = f[d].find(h0);
	if (it != f[d].end()) return it->yy;
	int ret = 0;
	rep(x, 0, w - 1){
		PI v0(-1, -1);
		rep(t, 0, w - 1) if (h[d] - abs(t - x) > h0[t]) {v0.xx = t; break;}
		red(t, w - 1, 0) if (h[d] - abs(t - x) > h0[t]) {v0.yy = t; break;}
		if (v0 == vis[d]){
			vc h1 = h0;
			if (v0.xx != -1) rep(t, v0.xx, v0.yy) h1[t] = h[d] - abs(t - x);
			ret = (ret + dfs(d - 1, h1)) % MOD;
		}
	}
	return f[d][h0] = ret;
}
class Mountains {
	public:
	int countPlacements(vector <int> heights, vector <string> _vis) {
		h = heights; n = h.size(); w = _vis[0].size(); vis.resize(n);
		rep(i, 0, n - 1){
			vis[i] = PI(-1, -1);
			rep(j, 0, w - 1) if (_vis[i][j] == 'X') {vis[i].xx = j; break;}
			red(j, w - 1, 0) if (_vis[i][j] == 'X') {vis[i].yy = j; break;}
		}
		return dfs(n - 1, vc(w, 0));
	}
};

/*
	Force is justice.
	Never forget that std::vector has comparisons!
*/
