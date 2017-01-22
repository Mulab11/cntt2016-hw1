/*
	Maximum-weight Closure, reduced to Minimum Cut
*/

#include <bits/stdc++.h>
#define rep(i, l, r) for (int i = (l); i <= (r); ++i)
#define red(i, r, l) for (int i = (r); i >= (l); --i)
using namespace std;
typedef long long LL;
const int NN = 3000;
const int MM = 200000;
int hd[NN], cur[NN], dis[NN];
int nxt[MM], to[MM], flow[MM];
int id[NN][NN];
int n, tl;
void ae(int u, int v, int f){
	++tl; to[tl] = v; flow[tl] = f; nxt[tl] = hd[u]; hd[u] = tl;
}
void ae2(int u, int v, int f){
	ae(u, v, f); ae(v, u, 0);
}
bool bfs(int S, int T){
	static int q[NN], l, r;
	rep(i, 0, T) cur[i] = hd[i], dis[i] = 0;
	for (l = r = dis[S] = 1, q[1] = S; l <= r && !dis[T]; ++l)
		for (int i = hd[q[l]]; i; i = nxt[i])
			if (flow[i] && !dis[to[i]])
				dis[q[++r] = to[i]] = dis[q[l]] + 1;
	return dis[T];
}
int dfs(int p, int T, int f){
	if (p == T || !f) return f;
	int ret = 0;
	for (int& i = cur[p]; i; i = nxt[i]){
		if (flow[i] && dis[to[i]] == dis[p] + 1){
			int r = dfs(to[i], T, min(f, flow[i]));
			f -= r; ret += r;
			flow[i] -= r; flow[i ^ 1] += r;
			if (!f) return ret;
		}
	}
	return ret;
}
int Dinic(int S, int T){
	int ret = 0;
	while (bfs(S, T)) ret += dfs(S, T, 66666);
	return ret;
}
class FoxAndCity {
	public:
	int minimalCost(vector <string> linked, vector <int> want) {
		memset(hd, 0, sizeof hd); tl = 1;
		int n = want.size(), S = 0, T = 0;
		// id[i][j] : dis_i <= j
		rep(i, 0, n - 1) rep(j, 0, n) id[i][j] = S++;
		T = S + 1;
		ae2(S, id[0][0], 1e5); // dis_0 = 0
		rep(i, 1, n - 1) ae2(id[i][0], T, 1e5); // dis_i > 0
		rep(i, 1, n - 1) ae2(S, id[i][n - 1], 1e5); // dis_i < n
		rep(i, 0, n - 1) rep(j, 1, n - 1) ae2(id[i][j - 1], id[i][j], 1e5); // dis_i <= j - 1 --> dis_i <= j
		rep(i, 0, n - 1) rep(j, 0, n - 1) if (linked[i][j] == 'Y')
			rep(k, 1, n - 1) ae2(id[i][k - 1], id[j][k], 1e5); // relax by edge i->j
		rep(i, 1, n - 1) rep(j, 1, n - 1) ae2(id[i][j], id[i][j - 1], (j - want[i]) * (j - want[i])); // weight
		return Dinic(S, T);
	}
};

/*
	I'm not so familiar with network flow...
*/
