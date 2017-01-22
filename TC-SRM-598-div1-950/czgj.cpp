/*
	Some magic conclusion
	Tree dp
*/

#include <bits/stdc++.h>
#define rep(i, l, r) for (int i = (l); i <= (r); ++i)
#define red(i, r, l) for (int i = (r); i >= (l); --i)
using namespace std;
typedef long long LL;
const int MAXN = 63;
vector<int> G[MAXN];
int n;
int dfs(int p, int fa = -1){
	int ret = 0;
	bool flag = 0;
	for (int x : G[p]) if (x != fa){
		int r = dfs(x, p);
		if (!r) flag = 1; // flag = if some subtree x is a chain
		ret += max(1, r); // set at least 1 beacon in subtree x
	}
	return ret -= flag; // -1 cost for one chain
}
class TPS {
	public:
	int minimalBeacons(vector <string> linked) {
		n = linked.size(); if (n == 1) return 0;
		rep(i, 0, n - 1) G[i].clear();
		rep(i, 0, n - 1) rep(j, 0, n - 1) if (linked[i][j] == 'Y') G[i].push_back(j);
		int ret = 666;
		rep(i, 0, n - 1) ret = min(ret, dfs(i) + 1); // set a beacon at i & make i be the root
		return ret;
	}
};

/*
	Another test!
*/
