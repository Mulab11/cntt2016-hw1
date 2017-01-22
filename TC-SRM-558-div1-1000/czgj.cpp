/*
	Minimum cut
*/
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
const int NN = 3000;
const int MM = 200000;
const int INF = 0x23333333;
int hd[NN], cur[NN], dis[NN];
int nxt[MM], to[MM], flow[MM];
int id[NN][NN];
int n, tl = 1;
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
	while (bfs(S, T)) ret += dfs(S, T, INF);
	return ret;
}

class SurroundingGame{
	public:
	int n, m;
	int val(char c){
		if (isdigit(c)) return c - '0';
		if (islower(c)) return c - 'a' + 10;
		if (isupper(c)) return c - 'A' + 36;
		return -1;
	}
	int getid(int i, int j){
		return (i * m + j) * 2;
	}
	const int dx[4] = {0, 1, 0, -1};
	const int dy[4] = {-1, 0, 1, 0};
	int maxScore(vector<string> cost, vector<string> benefit) {
		n = cost.size(), m = cost[0].size();
		int S = getid(n, 0), T = S + 1, sum = 0;
		rep(i, 0, n - 1) rep(j, 0, m - 1){
			int be = val(benefit[i][j]), co = val(cost[i][j]); sum += be;
			int id1 = getid(i, j), id2 = id1 + 1;
			if ((i ^ j) & 1){
				ae2(S, id1, co);
				ae2(id1, id2, be);
				rep(d, 0, 3){
					int ti = i + dx[d], tj = j + dy[d];
					if (ti >= 0 && ti < n && tj >= 0 && tj < m){
						int tid1 = getid(ti, tj), tid2 = tid1 + 1;
						ae2(id1, tid2, INF); ae2(id2, tid1, INF);
					}
				}
			}
			else{
				ae2(id2, id1, be);
				ae2(id1, T, co);
			}
		}
		return sum - Dinic(S, T);
	}
};

