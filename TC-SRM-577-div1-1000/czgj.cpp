/*
	Minimum Cut
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
const int dx[4] = {0, 1, 0, -1};
const int dy[4] = {1, 0, -1, 0};
class BoardPainting {
	public:
	int minimalSteps(vector <string> target) {
		int n = target.size(), m = target[0].size();
		int S = n * m, T = S + 1;
		memset(hd, 0, sizeof hd); tl = 1;
		rep(i, 0, n - 1) rep(j, 0, m - 1) if (target[i][j] == '#'){ // for each grid to be colored
			int id1 = i * m + j;
			rep(d, 0, 3){ // for each grid adjacent to it
				int ti = i + dx[d], tj = j + dy[d], id2 = ti * m + tj;
				if (ti >= 0 && tj >= 0 && ti < n && tj < m && target[ti][tj] == '#') ae2(id1, id2, 1); // cut between
				else if (d & 1) ae2(S, id1, 1); // auto cut : horizontally
				else ae2(id1, T, 1); // auto cut : vertically
			}
		}
		return Dinic(S, T) / 2;
	}
};

/*
	water...
	I'm a Salty Fish now.
*/
