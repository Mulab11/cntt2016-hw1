/*
	dfs and similar
	brute force
*/

#include <bits/stdc++.h>
#define rep(i, l, r) for (int i = (l); i <= (r); ++i)
#define red(i, r, l) for (int i = (r); i >= (l); --i)
using namespace std;
typedef long long LL;
const int MAXN = 60;
const LL MOD = 1000000007;
bool mark[2][MAXN], vis[2][MAXN];
vector<string> brd;
int val[2][MAXN];
int n;
class EqualSums {
	public:
	bool dfs(int p, int q, int v, int lb){
		mark[p][q] = vis[p][q] = 1; val[p][q] = v;
		if ((!p && v < lb) || v < 0) return 0;
		rep(i, 0, n - 1) if ((p ? brd[i][q] : brd[q][i]) != '-'){
			if (vis[!p][i] && v + val[!p][i] != (p ? brd[i][q] : brd[q][i]) - '0') return 0; // Visited, but not satisfied
			if (!vis[!p][i] && !dfs(!p, i, (p ? brd[i][q] : brd[q][i]) - '0' - v, lb)) return 0; // Go deeper and boom
		}
		return 1; // ok
	}
	int work(int lb){ // lb = lowerbound for one side
		LL ret = 1; n = brd.size();
		memset(mark, 0, sizeof mark);
		rep(i, 0, n - 1) if (!mark[0][i]){ // count a connected component for each time
			int cnt = 0;
			rep(j, lb, 9){
				memset(vis, 0, sizeof vis);
				cnt += dfs(0, i, j, lb);
			}
			ret = ret * cnt % MOD;
		}
		return ret;
	}
	int count(vector <string> board) {
		brd = board;
		return (MOD + work(0) - work(1)) % MOD;
	}
};

/*
	Topcoder
	Fuuhyouhigai
	Uneibakuha
*/
