#line 2 "FoxAndGo3.cpp"  
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
const int d[][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

int n;

const int V = N * N + 2, E = 6 * V, INF = 1e9;

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

class FoxAndGo3 {  
public:  
	int maxEmptyCells(vector <string> board) {  
		g.init(), n = SZ(board);
		int S = n * n, T = S + 1, cnt = 0;
		for(int i = 0; i < n; ++i)
			for(int j = 0; j < n; ++j) {
				int x = i * n + j;
				cnt += board[i][j] != 'x';
				if(board[i][j] == 'o') {// 'o'在S割表示变成了'.'，在T割表示没变
					g.addedge(S, x, 1);
					for(int t = 0; t < 4; ++t) {
						int ti = i + d[t][0], tj = j + d[t][1];
						if(ti >= 0 && ti < n && tj >= 0 && tj < n && board[ti][tj] == '.')
							g.addedge(x, ti * n + tj, INF);//这种情况下与它相邻的格子都应该是'x'
					}
				}
				else if(board[i][j] == '.') g.addedge(x, T, 1);// '.'在S割表示变成了'x'，否则没变
			}
		return cnt - g.maxflow(S, T);
	}    
};  
