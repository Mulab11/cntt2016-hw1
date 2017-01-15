#line 2 "OldBridges.cpp"  
#include <bits/stdc++.h> 

using namespace std;  

#define ui unsigned
#define ll long long

#define pii std::pair<int,int>
#define mp std::make_pair
#define fi first
#define se second

#define SZ(x) (int)(x).size()
#define pb push_back

template<class T>inline void chkmax(T &x, const T &y) {if(x < y) x = y;}
template<class T>inline void chkmin(T &x, const T &y) {if(x > y) x = y;}

const int N = 50;

const int V = N + 2, E = N * N * 2 + 8;

const int INF = 1e9;

struct graph {
	int sz, head[V + 9], to[E + 9], f[E + 9], ne[E + 9], dis[V + 9];
	void init() {
		memset(head, 0, sizeof head), sz = 1;
	}
	void addedge(int u, int v, int _f) {
		to[sz] = v, f[sz] = _f, ne[sz] = head[u], head[u] = sz++;
		to[sz] = u, f[sz] = 0, ne[sz] = head[v], head[v] = sz++;
	}
	bool bfs(int s, int t) {// get distance labels
		static int q[V + 9];
		int l = 0, r = 0;
		memset(dis, -1, sizeof dis);
		q[++r] = s, dis[s] = 0;
		while(l < r) {
			int x = q[++l];
			for(int i = head[x], y; i; i = ne[i])
				if(f[i] && dis[y = to[i]] == -1) {
					dis[y] = dis[x] + 1;
					q[++r] = y;
				}
		}
		return dis[t] != -1;
	}
	int dfs(int x, int sink, int flow) {// augment path
		if(x == sink || !flow) return flow;
		int ret = 0;
		for(int i = head[x], y, tmp; i; i = ne[i])
			if(dis[y = to[i]] == dis[x] + 1 && f[i] && (tmp = dfs(y, sink, min(flow, f[i])))) {
				f[i] -= tmp, f[((i - 1) ^ 1) + 1] += tmp;
				flow -= tmp, ret += tmp;
				if(!flow) break;
			}
		dis[x] = -1;
		return ret;
	}
	int dinic(int s, int t) {
		int ret = 0;
		while(bfs(s, t))
			ret += dfs(s, t, INF);
		return ret;
	}
}g1, g2;

class OldBridges {  
public:  
	string isPossible(vector <string> bridges, int a1, int a2, int an, int b1, int b2, int bn) {  
		g1.init(), g2.init();
		int n = SZ(bridges);
		// build the graph
		for(int i = 0; i < n; ++i)
			for(int j = 0; j < n; ++j)
				if(bridges[i][j] == 'O') g1.addedge(i, j, 2);
				else if(bridges[i][j] == 'N') g1.addedge(i, j, INF);
		int s = n, t = s + 1;
		g1.addedge(s, a1, 2 * an);
		g1.addedge(a2, t, 2 * an);
		g2 = g1;
		g1.addedge(s, b1, 2 * bn);
		g1.addedge(b2, t, 2 * bn);
		if(g1.dinic(s, t) != 2 * (an + bn)) return "No";// maxflow
		g2.addedge(s, b2, 2 * bn);
		g2.addedge(b1, t, 2 * bn);
		if(g2.dinic(s, t) != 2 * (an + bn)) return "No";// maxflow
		return "Yes";
	}    
};  
