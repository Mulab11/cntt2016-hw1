/*
	Minimum cut
*/

#include <bits/stdc++.h>
#define rep(i, l, r) for (int i = (l); i <= (r); ++i)
#define red(i, r, l) for (int i = (r); i >= (l); --i)
using namespace std;
typedef long long LL;
const int NN = 3000;
const int MM = 330000;
const int dx[4] = {0, 1, 0, -1};
const int dy[4] = {1, 0, -1, 0};
int hd[NN], cur[NN], dis[NN];
int nxt[MM], to[MM], flow[MM];
int n, tl;
void ae(int u, int v, int f){
	++tl; to[tl] = v; flow[tl] = f; nxt[tl] = hd[u]; hd[u] = tl;
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
	while (bfs(S, T)) ret += dfs(S, T, 23333);
	return ret;
}
class FoxAndGo3 {
	public:
	int maxEmptyCells(vector <string> board) {
		int n = board.size(), sum = 0;
		int S = n * n, T = S + 1;
		rep(i, 0, T) hd[i] = 0; tl = 1;
		rep(i, 0, n - 1) rep(j, 0, n - 1){
			int id = i * n + j;
			sum += (board[i][j] == 'o' || board[i][j] == '.');
			if (board[i][j] == '.') ae(S, id, 1), ae(id, S, 0);
			if (board[i][j] == 'o'){
				ae(id, T, 1); ae(T, id, 0);
				rep(d, 0, 3){
					int ti = i + dx[d], tj = j + dy[d];
					if (0 <= ti && ti < n && 0 <= tj && tj < n && board[ti][tj] == '.'){
						int id2 = ti * n + tj;
						ae(id2, id, 23333); ae(id, id2, 0);
					}
				}
			} 
		}
		return sum - Dinic(S, T);
	}
};

/*
	Who's the Master of Go?
*/
