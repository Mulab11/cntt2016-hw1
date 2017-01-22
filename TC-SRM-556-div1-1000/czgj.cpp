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
const LL MOD = 1e9 + 7;

const int NN = 666;
const int MM = 23333;
int hd[NN], cur[NN], dis[NN];
int nxt[MM], to[MM], flow[MM];
int id[NN][NN];
int n, tl;
void ae(int u, int v, int f){
	++tl; to[tl] = v; flow[tl] = f; nxt[tl] = hd[u]; hd[u] = tl;
}
void ae2(int u, int v, int f, int f2 = 0){
	ae(u, v, f); ae(v, u, f2);
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
	while (bfs(S, T)) ret += dfs(S, T, 666666);
	return ret;
}
class OldBridges{
	public:
	vector<string> g;
	int n;
	bool work(int a1, int a2, int an, int b1, int b2, int bn){
		MEM(hd, 0); tl = 1;
		rep(i, 0, n - 1) rep(j, i + 1, n - 1) if (g[i][j] != 'X'){
			int v = g[i][j] == 'O' ? 2 : 23333;
			ae2(i, j, v, v);
		}
		int S = n, T = n + 1;
		ae2(S, a1, an * 2); ae2(a2, T, an * 2);
		ae2(S, b1, bn * n); ae2(b2, T, bn * 2);
		return Dinic(S, T) == (an + bn) * 2;
	}
	string isPossible(vector<string> bridges, int a1, int a2, int an, int b1, int b2, int bn){
		g = bridges; n = g.size();
		return (work(a1, a2, an, b1, b2, bn) && work(a1, a2, an, b2, b1, bn)) ? "Yes" : "No";
	}
};

