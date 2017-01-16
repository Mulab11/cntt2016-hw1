#line 2 "FoxAndCity.cpp"  
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

const int N = 40;

int n;

const int V = N * N + 2, E = 2 * (2 * N * N + N * N * N), INF = 1e9;

struct net {// dinic求最大流
	int sz, head[V + 9], to[E + 9], f[E + 9], ne[E + 9];
	void init() {
		sz = 1, memset(head, 0, sizeof head);
	}
	void addedge(int u, int v, int _f) {
		to[sz] = v, f[sz] = _f, ne[sz] = head[u], head[u] = sz++;
		to[sz] = u, f[sz] = 0, ne[sz] = head[v], head[v] = sz++;
	}
	int dis[V + 9];
	bool bfs(int S, int T) {
		std::queue<int> q;
		memset(dis, -1, sizeof dis);
		q.push(S), dis[S] = 0;
		while(!q.empty()) {
			int x = q.front();q.pop();
			for(int i = head[x], y; i; i = ne[i])
				if(f[i] && dis[y = to[i]] == -1) {
					dis[y] = dis[x] + 1;
					q.push(y);
				}
		}
		return dis[T] != -1;
	}
	int inv(int x) {
		return ((x - 1) ^ 1) + 1;
	}
	int dfs(int x, int T, int flow) {
		if(!flow || x == T) return flow;
		int ret = 0;
		for(int i = head[x], y, tmp; i; i = ne[i])
			if(f[i] && dis[y = to[i]] == dis[x] + 1 && (tmp = dfs(y, T, std::min(flow, f[i])))) {
				f[i] -= tmp, f[inv(i)] += tmp;
				flow -= tmp, ret += tmp;
				if(!flow) break;
			}
		dis[x] = -1;
		return ret;
	}
	int maxflow(int S, int T) {
		int ret = 0;
		while(bfs(S, T)) ret += dfs(S, T, INF);
		return ret;
	}
}g;

class FoxAndCity {  
public:  
	int minimalCost(vector <string> linked, vector <int> want) {  
		n = SZ(want);
		g.init();
		int S = n * n, T = S + 1;
		for(int i = 0; i < n; ++i) {
			if(!i) g.addedge(S, i * n, 0);// 0号点强制割距离为0的边
			else g.addedge(S, i * n, INF);
			for(int j = 1; j < n; ++j) {
				if(!i) g.addedge(i * n + j - 1, i * n + j, INF);// 0号点不能割距离>0的边
				else g.addedge(i * n + j - 1, i * n + j, (want[i] - j) * (want[i] - j));// 距离为j的代价
				g.addedge(i * n + j, i * n + j - 1, INF);// 如果j在S割，那么j - 1也在S割
			}
			g.addedge(i * n + n - 1, T, INF);
		}
		for(int i = 0; i < n; ++i)
			for(int j = 0; j < n; ++j)
				if(linked[i][j] == 'Y')// 每条边形成了一个限制，dis[i] <= dis[j] + 1
					for(int k = 1; k < n; ++k)
						g.addedge(i * n + k, j * n + k - 1, INF);
		return g.maxflow(S, T);
	}    
};  
