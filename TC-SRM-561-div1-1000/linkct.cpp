#include <bits/stdc++.h>
using namespace std;
const int MAXN = 55, MAXM = 305, dx[4] = {-1, 0, 0, 1}, dy[4] = {0, -1, 1, 0};

class Orienteering{
public:
	int r, c, n, m, q, id[MAXN][MAXN], *dis, g[MAXN * MAXN];
	int nid[MAXM], cid[MAXN * MAXN], d[MAXM][MAXM], size[MAXN * MAXN];
	int edgeSize, nxt[MAXN * MAXN * 2], to[MAXN * MAXN * 2]; double ans;
	void getLength(int x, int f, int l){
		dis[cid[x]] = l;
		for(int p = g[x]; p; p = nxt[p])
			if(to[p] != f) getLength(to[p], x, l + 1);
	}
	inline double calc(int a, int b, int C){ //Calculate C(a, c) / C(b, c) without overflow
		if(a < C) return 0.0;
		double ret = 1.0;
		for(int i = 0; i < C; ++ i)
			ret *= 1.0 * (a - i) / (b - i);
		return ret; //a! / (a-c)! / (b! / (b-c)!)
	}
	void getTotal(int x, int f){
		int p; size[x] = (cid[x] ? 1 : 0);
		for(p = g[x]; p; p = nxt[p]){
			if(to[p] == f) continue;
			getTotal(to[p], x);
			size[x] += size[to[p]];
		}
		for(p = g[x]; p; p = nxt[p]){
			if(to[p] == f) continue;
			ans += 1.0 - calc(size[to[p]], m, q) - calc(m - size[to[p]], m, q);
		}
	}
	void addEdge(int u, int v){
		if(!v) return;
		nxt[++ edgeSize] = g[u];
		to[g[u] = edgeSize] = v;
	}
	inline bool inmap(int x, int y){return x >= 0 && x < r && y >= 0 && y < c;}
	double expectedLength(vector <string> graph, int q_){
		int i, j, k, dia, cnt; q = q_; ans = 0.0;
		r = graph.size(), c = graph[0].length();
		memset(id, 0, sizeof(id));
		memset(cid, 0, sizeof(cid));
		memset(nid, 0, sizeof(nid));
		memset(g, 0, sizeof(g));
		edgeSize = n = m = 0;
		for(i = 0; i < r; ++ i)
			for(j = 0; j < c; ++ j)
				if(graph[i][j] != '#'){
					id[i][j] = ++ n;
					if(graph[i][j] == '*')
						nid[cid[n] = ++ m] = n;
				}
		for(i = 0; i < r; ++ i)
			for(j = 0; j < c; ++ j){
				if(!id[i][j]) continue;
				for(k = 0; k < 4; ++ k)
					if(inmap(i + dx[k], j + dy[k]))
						addEdge(id[i][j], id[i + dx[k]][j + dy[k]]);
			}
		for(i = 1; i <= m; ++ i)
			dis = d[i], getLength(nid[i], -1, 0);
		getTotal(1, -1); ans *= 2.0; //Part I: calculate E(sum) = \sum_{e} P(e is included)
		for(i = 1; i <= m; ++ i){
			for(j = i + 1; j <= m; ++ j){
				dia = d[i][j];
				for(k = 1, cnt = 0; k <= m; ++ k){
					if(d[i][k] > dia || d[j][k] > dia) continue;
					if((d[i][k] < dia || k < j) && (d[j][k] < dia || k < i))
						++ cnt;
				} ans -= calc(cnt, m, q - 2) * q * (q - 1) / (m - q + 1) / (m - q + 2) * dia; //Part II: calculate (i, j) as the diameter of tree
			}
		} return ans;
	}
};
