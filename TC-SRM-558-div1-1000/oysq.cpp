#line 2 "SurroundingGame.cpp"  
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

#define A(x) ((x) << 1) // original node
#define B(x) ((x) << 1 | 1)// virtual node

const int N = 20;
const int INF = 1e9;
const int d[][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

int n, m;
int c[N + 9][N + 9];// cost
int b[N + 9][N + 9];// benefit
int id[N + 9][N + 9];// id of each cell

const int V = N * N * 2 + 2, E = 100000;

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
}g;

class SurroundingGame {  
public:
	// change the character into integer
	int get(char c) {
		if('0' <= c && c <= '9') return c - '0';
		else if('a' <= c && c <= 'z') return c - 'a' + 10;
		else return c - 'A' + 36;
	}
	int maxScore(vector <string> cost, vector <string> benefit) {
		int sum = 0;
		// initialization
		n = SZ(cost), m = SZ(cost[0]), g.init();
		for(int i = 0, tot = 0; i < n; ++i)
			for(int j = 0; j < m; ++j) {
				c[i][j] = get(cost[i][j]), b[i][j] = get(benefit[i][j]);
				id[i][j] = tot++, sum += b[i][j] + max(0, b[i][j] - c[i][j]);
			}
		int s = n * m * 2, t = s + 1;// source and sink
		for(int i = 0; i < n; ++i)
			for(int j = 0; j < m; ++j)
				if((i + j) & 1) {// black node
					g.addedge(B(id[i][j]), A(id[i][j]), INF);
					g.addedge(s, B(id[i][j]), b[i][j]);
					g.addedge(s, A(id[i][j]), max(0, c[i][j] - b[i][j]));
					g.addedge(A(id[i][j]), t, max(0, b[i][j] - c[i][j]));
					for(int k = 0; k < 4; ++k) {
						int ti = i + d[k][0], tj = j + d[k][1];
						if(ti >= 0 && ti < n && tj >= 0 && tj < m) {
							g.addedge(B(id[i][j]), A(id[ti][tj]), INF);
							g.addedge(A(id[i][j]), B(id[ti][tj]), INF);
						}
					}
				}
				else {// white node
					g.addedge(A(id[i][j]), B(id[i][j]), INF);
					g.addedge(B(id[i][j]), t, b[i][j]);
					g.addedge(s, A(id[i][j]), max(0, b[i][j] - c[i][j]));
					g.addedge(A(id[i][j]), t, max(0, c[i][j] - b[i][j]));
				}
		return sum - g.dinic(s, t);
	}    
};  
