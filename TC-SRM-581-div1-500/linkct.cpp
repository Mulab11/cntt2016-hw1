#include <bits/stdc++.h>
using namespace std;
const int MAXN = 605;

class TreeUnion{
public:
	int *cnt, cnt1[9], cnt2[9], k, edgeSize, n, f1[MAXN];
	int g[MAXN], nxt[MAXN << 1], to[MAXN << 1], f2[MAXN];
	void dfs(int x, int f, int d){
		if(d > k - 2) return;
		++ cnt[d];
		for(int p = g[x]; p; p = nxt[p])
			if(to[p] != f) dfs(to[p], x, d + 1);
	}
	void addEdge(int u, int v){
		nxt[++ edgeSize] = g[u];
		to[g[u] = edgeSize] = v;
	}
	void extract(vector <string> &x, int y[], int &l){
		stringstream readin; int i;
		for(i = 0; i < int(x.size()); ++ i)
			readin << x[i];
		for(l = 0; readin >> y[0]; y[++ l] = y[0]) ;
	}
	double expectedCycles(vector <string> a, vector <string> b, int k_){
		int i; double ans = 0.0; k = k_;
		extract(a, f1, n);
		extract(b, f2, n);
		for(i = 1, ++ n; i < n; ++ i){
			addEdge(i, f1[i]);
			addEdge(n + i, n + f2[i]);
		} if(k <= 3 || n <= 2) return 0.0;
		for(i = 0, cnt = cnt1; i < n; ++ i)
			dfs(i, -1, 1);
		for(i = 0, cnt = cnt2; i < n; ++ i)
			dfs(n + i, -1, 1);
		for(i = 2; i <= k - 2; ++ i)
			ans += 2.0 / n / (n - 1) * cnt1[i] * cnt2[k - i];
		return ans;
	}
};
