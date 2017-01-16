#line 2 "TheTilesDivOne.cpp"  
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
const int V = 5000;
const int E = 60000;
const int d[][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
const int INF = 0x3f3f3f3f;

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

int id[N + 9][N + 9], tot;// id 表示每个位置的点的编号

class TheTilesDivOne {  
public:  
	int find(vector <string> b) {  
		g.init(), tot = 0;
		int n = SZ(b), m = SZ(b[0]);
		int S = tot++, T = tot++;
		for(int i = 0; i < n; ++i)
			for(int j = 0; j < m; ++j)
				if(b[i][j] == '.') {
					if((i + j) & 1) {
						id[i][j] = tot++;
						// 将白点根据行号的奇偶性分别从S，向T连边
						if(i & 1) g.addedge(id[i][j], T, 1);
						else g.addedge(S, id[i][j], 1);
					}
					else {
						// 将黑点拆成两个点A, B，A->B连一条流量为1的边表示一个黑点只能用一次
						id[i][j] = tot++, tot++;// id[i][j] 表示A，id[i][j] + 1 表示B
						g.addedge(id[i][j], id[i][j] + 1, 1);
					}
				}
		for(int i = 0; i < n; ++i)
			for(int j = 0; j < m; ++j)
				if(b[i][j] == '.' && !((i + j) & 1)) {
					for(int k = 0; k < 4; ++k) {
						int x = i + d[k][0], y = j + d[k][1];
						if(x >= 0 && x < n && y >= 0 && y < m && b[x][y] == '.') {
							// 将黑点与相邻的白点连边
							// 如果白点是从S来的，白点连向拆的点A
							// 否则拆的点B连向白点
							if(x & 1) g.addedge(id[i][j] + 1, id[x][y], 1);
							else g.addedge(id[x][y], id[i][j], 1);
						}
					}
				}
		return g.dinic(S, T);
	}    
};  
