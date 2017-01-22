/*
	1. Transitive closure
	2. Solve the minimum path cover with Network Flow.
*/

#include <bits/stdc++.h>
#define rep(i, l, r) for (int i = (l); i <= (r); ++i)
using namespace std;
const int NN = 233;
const int MM = 6666;
int hd[NN], cur[NN], dis[NN];
int nxt[MM], to[MM], flow[MM];
bool G[NN][NN];
int n, tl;
void ae(int u, int v, int f){
	++tl; to[tl] = v; flow[tl] = f; nxt[tl] = hd[u]; hd[u] = tl;
}
bool bfs(int S, int T){
	static int q[NN], l, r;
	rep(i, 1, T) cur[i] = hd[i], dis[i] = 0;
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
	while (bfs(S, T)) ret += dfs(S, T, 23333);
	return ret;
}
class Incubator {
	public:
	int maxMagicalGirls(vector <string> love) {
		n = love.size();
		memset(hd, 0, sizeof hd); tl = 1;
		rep(i, 1, n) rep(j, 1, n) G[i][j] = love[i - 1][j - 1] == 'Y';
		rep(k, 1, n) rep(i, 1, n) rep(j, 1, n) G[i][k] |= G[i][j] && G[j][k];
		int S = n * 2 + 1, T = S + 1;
		rep(i, 1, n) ae(S, i, 1), ae(i, S, 0), ae(i + n, T, 1), ae(T, i + n, 0);
		rep(i, 1, n) rep(j, 1, n) if (G[i][j]) ae(i, j + n, 1), ae(j + n, i, 0);
		return n - Dinic(S, T);
	}
};

/*
	Yume no naka de atte, you na
	Sore wa tottemo ureshii na tte
	Mou nani mo kowaku nai
*/
