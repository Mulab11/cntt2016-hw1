#include <bits/stdc++.h>
using namespace std;
const int MAXN = 2505, MAXM = MAXN * 5, INF = 0x3f3f3f3f;
const int dx[4] = {-1, 0, 0, 1}, dy[4] = {0, -1, 1, 0};

class FoxAndGo3{
public:
	struct Dinic{
		struct edge{
			int n, p, r;
			void var(int n_, int p_, int r_){
				n = n_, p = p_, r = r_;
			}
		}edges[MAXM << 1];
		int g[MAXN], edgeSize, s, t, d[MAXN], cur[MAXN];
		queue <int> q;
		
		void init(int s_, int t_){
			memset(g, 0, sizeof(g));
			edgeSize = 1; s = s_, t = t_;
		}
		void addEdge(int u, int v, int r){
			edges[++ edgeSize].var(v, g[u], r);
			g[u] = edgeSize;
			edges[++ edgeSize].var(u, g[v], 0);
			g[v] = edgeSize;
		}
		bool bfs(){
			int now, p;
			memset(d, 0, sizeof(d));
			d[s] = 1; q.push(s);
			while(!q.empty()){
				now = q.front(); q.pop(); cur[now] = g[now];
				for(p = g[now]; p; p = edges[p].p)
					if(edges[p].r && !d[edges[p].n]){
						d[edges[p].n] = d[now] + 1;
						q.push(edges[p].n);
					}
			}
			return d[t];
		}
		int dfs(int x, int a){
			if(x == t || !a) return a;
			int f, flow = 0;
			for(int &p = cur[x]; p; p = edges[p].p)
				if(d[edges[p].n] == d[x] + 1 && (f = dfs(edges[p].n, min(a, edges[p].r)))){
					flow += f; edges[p ^ 1].r += f;
					edges[p].r -= f; if(!(a -= f)) break;
				}
			return flow;
		}
		int solve(){
			int ret = 0;
			while(bfs()) ret += dfs(s, INF);
			return ret;
		}
	}maxFlow;
	int n;
	inline bool inMap(int i, int j){return i >= 0 && i < n && j >= 0 && j < n;}
	int maxEmptyCells(vector <string> g){
		n = g.size();
		int i, j, k, x, y, cnt = n * n;
		maxFlow.init(0, n * n + 1);
		for(i = 0; i < n; ++ i)
			for(j = 0; j < n; ++ j){
				if(g[i][j] == '.') maxFlow.addEdge(i * n + j + 1, n * n + 1, 1);
				else if(g[i][j] == 'o'){
					maxFlow.addEdge(0, i * n + j + 1, 1);
					for(k = 0; k < 4; ++ k){
						x = i + dx[k], y = j + dy[k];
						if(inMap(x, y) && g[x][y] == '.')
							maxFlow.addEdge(i * n + j + 1, x * n + y + 1, INF);
					}
				}else -- cnt;
			}
		return cnt - maxFlow.solve();
	}
};
