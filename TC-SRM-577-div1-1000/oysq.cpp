#line 2 "BoardPainting.cpp"  
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
const int V = N * N + 2, E = N * N * 4, INF = 0x3f3f3f3f;

struct graph {// Dinic 最大流
	int sz, head[V + 9], to[E + 9], f[E + 9], ne[E + 9];
	void init() {
		sz = 1, memset(head, 0, sizeof head);
	}
	void addedge(int u, int v, int _f) {
		to[sz] = v, f[sz] = _f, ne[sz] = head[u], head[u] = sz++;
		to[sz] = u, f[sz] = 0, ne[sz] = head[v], head[v] = sz++;
	}
	int inv(int x) {
		return ((x - 1) ^ 1) + 1;
	}
	int dis[V + 9];
	int bfs(int S, int T) {
		static int q[V + 9], l, r;
		memset(dis, INF, sizeof dis);
		q[l = 0, r = 1] = S, dis[S] = 0;
		while(l < r) {
			int x = q[++l];
			for(int i = head[x], y; i; i = ne[i])
				if(f[i] && dis[x] + 1 < dis[y = to[i]]) {
					dis[y] = dis[x] + 1;
					q[++r] = y;
				}
		}
		return dis[T] < INF;
	}
	int dfs(int x, int T, int flow) {
		if(x == T || !flow) return flow;
		int ret = 0;
		for(int i = head[x], y, tmp; i; i = ne[i])
			if(f[i] && dis[x] + 1 == dis[y = to[i]] && (tmp = dfs(y, T, std::min(flow, f[i])))) {
				f[i] -= tmp, f[inv(i)] += tmp;
				ret += tmp, flow -= tmp;
				if(!flow) break;
			}
		dis[x] = INF;
		return ret;
	}
	int dinic(int S, int T) {
		int ret = 0;
		while(bfs(S, T))
			ret += dfs(S, T, INF);
		return ret;
	}
}g;

class BoardPainting {  
public:  
	int minimalSteps(vector <string> target) {
		g.init();
		int n = SZ(target), m = SZ(target[0]), s = n * m + 1, t = n * m + 2;
		for(int i = 0; i < n; ++i)
			for(int j = 0; j < m; ++j)
				if(target[i][j] == '#') {
					if(!j || target[i][j - 1] != '#') g.addedge(s, i * m + j, 1);// 左边为空地的情况下水平方向的代价
					else g.addedge(i * m + j - 1, i * m + j, 1);// 左边不为空地的情况下，如果两边不在一个S/T集中的代价
					if(!i || target[i - 1][j] != '#') g.addedge(i * m + j, t, 1);// 同上
					else g.addedge(i * m + j, (i - 1) * m + j, 1);// 同上
				}
		return g.dinic(s, t);
	}    
};  
