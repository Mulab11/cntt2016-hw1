/*
	Network flow
*/

#include <bits/stdc++.h>
#define rep(i, l, r) for (int i = (l); i <= (r); ++i)
#define red(i, r, l) for (int i = (r); i >= (l); --i)
using namespace std;
typedef long long LL;

const int NN = 5000;
const int MM = 50000;
int hd[NN], cur[NN], dis[NN];
int nxt[MM], to[MM], flow[MM];
int n, m, tl;
void ae(int u, int v, int f){
	++tl; to[tl] = v; flow[tl] = f; nxt[tl] = hd[u]; hd[u] = tl;
}
void ae2(int u, int v, int f = 1){
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

vector<string> board;
int getid(int x, int y){
	return 2 * (x * m + y);
}
bool check(int x, int y){
	return x >= 0 && y >= 0 && x < n && y < m && board[x][y] != 'X';
}
class TheTilesDivOne {
	public:
	const int dx[4] = {0, 1, 0, -1};
	const int dy[4] = {1, 0, -1, 0};
	int find(vector <string> board) {
		memset(hd, 0, sizeof hd); tl = 1;
		n = board.size(); m = board[0].size(); ::board = board;
		int S = getid(n, 0), T = S + 1;
		rep(i, 0, n - 1) rep(j, 0, m - 1) if (board[i][j] != 'X'){
			int id0 = 2 * (i * m + j), id1 = id0 + 1; // in, out
			ae2(id0, id1);
			rep(d, 0, 3) if (check(i + dx[d], j + dy[d])) ae2(id1, getid(i + dx[d], j + dy[d]));
			if (~(i + j) & 1) continue;
			if (i & 1) ae2(S, id0); else ae2(id1, T);
		}
		return Dinic(S, T);
	}
};

/*
	Furou de yasui dana
*/
