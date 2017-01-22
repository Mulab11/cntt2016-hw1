#include <bits/stdc++.h>
#define rep(i, l, r) for (int i = (l); i <= (r); ++i)
#define red(i, r, l) for (int i = (r); i >= (l); --i)
using namespace std;
typedef long long LL;
typedef pair<int, int> PI;
const int MAXN = 55;
const int MAXM = 66660;
struct WoBuHuiKM{ // flow
	int hd[MAXN], pre[MAXN], to[MAXM], nxt[MAXM], flow[MAXM], w[MAXM], tl;
	void add0(int u, int v, int f0, int w0){
		++tl; nxt[tl] = hd[u]; to[tl] = v; flow[tl] = f0; w[tl] = w0; hd[u] = tl;
	}
	void add(int u, int v, int f0, int w0){
		add0(u, v, f0, w0); add0(v, u, 0, -w0);
	}
	void allclear(){
		memset(hd, 0, sizeof hd); tl = 1;
	}
	int dis[MAXN];
	bool SPFA(int s, int t) {
		static int q[MAXM];
		static bool inq[MAXN];
		memset(inq, 0, sizeof inq);
		memset(dis, 0x80, sizeof dis);
		memset(pre, 0xff, sizeof pre);
		int l = 0, r = 1; q[0] = s; dis[s] = 0;
		while (l < r) {
			int u = q[l++], v; inq[u] = 0;
			for (int i = hd[u]; i; i = nxt[i])
				if (flow[i] && dis[v = to[i]] < dis[u] + w[i]) {
					pre[v] = i; dis[v] = dis[u] + w[i];
					if (!inq[v]) {inq[v] = 1; q[r++] = v;}
				}
		}
		return dis[t] != (int)0x80808080;
	}
	int WoBuHuiKMaaaaaaaa(int s, int t){
		int ret = 0;
		while (SPFA(s, t)) {
			for (int i = pre[t]; ~i; i = pre[to[i ^ 1]]) --flow[i], ++flow[i ^ 1];
			ret += dis[t];
		}
		return ret;
	}
}aaa;
int n;
vector<int> E[MAXN];
bool mark[MAXN];
void Mark(int u){
	mark[u] = 1;
	for (int v : E[u]) if (!mark[v]) Mark(v);
}
bool vis[MAXN][MAXN][MAXN][MAXN];
int f[MAXN][MAXN][MAXN][MAXN];
int dfs(int u, int fu, int v, int fv){ // memorized search
	if (vis[u][fu][v][fv]) return f[u][fu][v][fv];
	vis[u][fu][v][fv] = 1;
	map<PI, int> w; // store the weight of edges temporarily
	for (int tu : E[u]) if (tu != fu)
		for (int tv : E[v]) if (tv != fv)
			w[PI(tu, tv)] = dfs(tu, u, tv, v);
	aaa.allclear();
	// build then network graph
	for (int tu : E[u]) if (tu != fu) aaa.add(u, tu, 1, 0);
	for (int tv : E[v]) if (tv != fv) aaa.add(tv, v, 1, 0);
	for (int tu : E[u]) if (tu != fu)
		for (int tv : E[v]) if (tv != fv)
			aaa.add(tu, tv, 1, w[PI(tu, tv)]);
	return f[u][fu][v][fv] = aaa.WoBuHuiKMaaaaaaaa(u, v) + 1;
}
class DeerInZooDivOne {
	public:
	int getmax(vector <int> a, vector <int> b) {
		n = a.size() + 1;
		int ret = 0;
		rep(i, 0, n - 2){ // ban an edge
			memset(vis, 0, sizeof vis);
			memset(mark, 0, sizeof mark);
			rep(j, 0, n - 1) E[j].clear();
			rep(j, 0, n - 2) if (j != i) E[a[j]].push_back(b[j]), E[b[j]].push_back(a[j]);
			Mark(a[i]);
			rep(j, 0, n - 1) if (mark[j]) // Then find two roots and RUN!!!
				rep(k, 0, n - 1) if (!mark[k])
					ret = max(ret, dfs(j, j, k, k));
		}
		return ret;
	}
};

/*
	WO BU HUI KM AAAAAAA
*/
