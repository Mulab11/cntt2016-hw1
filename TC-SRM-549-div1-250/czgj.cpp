/*

	maximum matching (naive)
*/

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 500;
const int MAXM = 1000;
struct edge{
	int to, next, f;
}E[MAXM * 2];
int hd[MAXN], cur[MAXN], ne = 2;
void addedge(int x, int y, int f){
	E[ne] = edge{y, hd[x], f};
	hd[x] = ne++;
}
#define inv(x) ((x) ^ 1)
int dis[MAXN], q[MAXN];
bool bfs(int S, int T){
	memset(dis, -1, sizeof(dis));
	int l, r;
	for (dis[q[l = r = 1] = S] = 0; l <= r && dis[T] == -1; ++l)
		for (int i = hd[q[l]]; i; i = E[i].next)
			if (E[i].f && dis[E[i].to] == -1)
				dis[E[i].to] = dis[q[l]] + 1, q[++r] = E[i].to;
	if (dis[T] == -1) return 0;
	for (int i = 1; i <= T; ++i) cur[i] = hd[i];
	return 1;
}
int dfs(int x, int maxf, int T){
	if (x == T) return maxf;
	int r = 0;
	for (int &i = cur[x]; i; i = E[i].next)
		if (E[i].f && dis[E[i].to] == dis[x] + 1){
			int t = dfs(E[i].to, min(maxf, E[i].f), T);
			maxf -= t; E[i].f -= t;
			r += t; E[inv(i)].f += t;
			if (!maxf) break;
		}
	return r;
}
int dinic(int S, int T){
	int ret = 0;
	while(bfs(S, T)) ret += dfs(S, 0x23333, T);
	return ret;
}

int n1, n2;
class PointyWizardHats {
	public:
	int getNumHats(vector <int> h1, vector <int> r1, vector <int> h2, vector <int> r2) {
		n1 = h1.size(); n2 = h2.size();
		int S = n1 + n2 + 1, T = S + 1;
		for (int i = 1; i <= T; ++i) hd[i] = 0; ne = 2;
		for (int i = 1; i <= n1; ++i) addedge(S, i, 1), addedge(i, S, 0);
		for (int i = n1 + 1; i < S; ++i) addedge(i, T, 1), addedge(T, i, 0);
		for (int i = 0; i < n1; ++i) for (int j = 0; j < n2; ++j)
			if (r1[i] < r2[j] && r1[i] * h2[j] < h1[i] * r2[j])
				addedge(i + 1, n1 + j + 1, 1), addedge(n1 + j + 1, i + 1, 0);
		return dinic(S, T);
	}
};

/*
	'I fell into a burning ring of fire,
	Went down, down, down, and the flames went higher.'
		- Banned Forever
*/ 
