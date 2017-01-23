#include <bits/stdc++.h>
using namespace std;
const int MAXN = 55, INF = 0x3f3f3f3f;

class DeerInZooDivOne{
public:
	int g[MAXN], nxt[MAXN << 1], to[MAXN << 1], edgeSize;
	int dfsClock, st[MAXN], ed[MAXN], fa[MAXN], lt[MAXN], R1;
	int rt[MAXN], slack[MAXN], lmatch[MAXN], rmatch[MAXN];
	int prev[MAXN], q[MAXN], h, t, w[MAXN][MAXN], dp[MAXN][MAXN];
	bool lvis[MAXN], rvis[MAXN];
	void dfs(int x){
		st[x] = ++ dfsClock;
		for(int p = g[x]; p; p = nxt[p])
			if(to[p] != fa[x])
				fa[to[p]] = x, dfs(to[p]);
		ed[x] = dfsClock;
	}
	inline bool update(int &a, int b){if(a < b) return false; a = b; return true;}
	void augment(int x){
		for(int y; x; x = y){
			y = lmatch[prev[x]];
			lmatch[rmatch[x] = prev[x]] = x;
		}
	}
	void find(int n, int m, int x){
		int i, mn;
		memset(slack, 0x3f, sizeof(int) * (m + 1));
		memset(lvis, false, sizeof(bool) * (n + 1));
		memset(rvis, false, sizeof(bool) * (m + 1));
		lvis[q[h = t = 1] = x] = true;
		while(true){
			for(; h <= t; ++ h)
				for(i = 1; i <= m; ++ i){
					if(rvis[i]) continue;
					if(lt[q[h]] + rt[i] == w[q[h]][i]){
						prev[i] = q[h];
						if(!rmatch[i]){
							augment(i);
							return;
						} rvis[i] = true;
						lvis[q[++ t] = rmatch[i]] = true;
					}else if(update(slack[i], lt[q[h]] + rt[i] - w[q[h]][i]))
						prev[i] = q[h];
				}
			mn = INF;
			for(i = 1; i <= m; ++ i)
				if(!rvis[i]) update(mn, slack[i]);
			for(i = 1; i <= n; ++ i)
				if(lvis[i]) lt[i] -= mn;
			for(i = 1; i <= m; ++ i)
				if(rvis[i]) rt[i] += mn;
				else slack[i] -= mn;
			for(i = 1; i <= m; ++ i)
				if(!rvis[i] && !slack[i]){
					if(!rmatch[i]){augment(i); return;}
					lvis[q[++ t] = rmatch[i]] = rvis[i] = true;
				}
		}
	}
	int getMatch(int n, int m){
		int i, j, ret = 0;
		memset(lt, 0, sizeof(int) * (n + 1));
		memset(rt, 0, sizeof(int) * (m + 1));
		memset(prev, 0, sizeof(int) * (m + 1));
		memset(lmatch, 0, sizeof(int) * (n + 1));
		memset(rmatch, 0, sizeof(int) * (m + 1));
		for(i = 1; i <= n; ++ i)
			for(j = 1; j <= m; ++ j)
				lt[i] = max(lt[i], w[i][j]);
		for(i = 1; i <= n; ++ i) find(n, m, i);
		for(i = 1; i <= n; ++ i) ret += lt[i];
		for(i = 1; i <= m; ++ i) ret += rt[i];
		return ret;
	}
	int solve(int i, int fi, int j, int fj){
		if(~dp[i][j]) return dp[i][j];
		int p, u, v; vector <int> s1, s2;
		for(p = g[i]; p; p = nxt[p])
			if(to[p] != fi) s1.push_back(to[p]);
		for(p = g[j]; p; p = nxt[p])
			if(to[p] != fj && to[p] != R1)
				s2.push_back(to[p]);
		for(u = 0; u < int(s1.size()); ++ u)
			for(v = 0; v < int(s2.size()); ++ v)
				solve(s1[u], i, s2[v], j);
		for(u = 0; u < int(s1.size()); ++ u)
			for(v = 0; v < int(s2.size()); ++ v)
				if(s1.size() <= s2.size())
					w[u + 1][v + 1] = dp[s1[u]][s2[v]];
				else w[v + 1][u + 1] = dp[s1[u]][s2[v]];
		return dp[i][j] = getMatch(min(s1.size(), s2.size()), max(s1.size(), s2.size())) + 1;
	}
	void addEdge(int u, int v){
		nxt[++ edgeSize] = g[u];
		to[g[u] = edgeSize] = v;
	}
	int getmax(vector <int> u, vector <int> v){
		int i, j, ans = 1, n = u.size() + 1;
		memset(g, 0, sizeof(g));
		edgeSize = dfsClock = 0;
		for(i = 0; i < n - 1; ++ i){
			addEdge(u[i] + 1, v[i] + 1);
			addEdge(v[i] + 1, u[i] + 1);
		} dfs(1);
		for(i = 2; i <= n; ++ i){
			R1 = i;
			for(j = 1; j <= n; ++ j)
				if(st[j] < st[i] || st[j] > ed[i]){
					memset(dp, -1, sizeof(dp));
					ans = max(ans, solve(i, fa[i], j, 0));
				}
		} return ans;
	}
};
