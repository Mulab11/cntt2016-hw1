#include <bits/stdc++.h>
using namespace std;
const int MAXN = 2005, MAXM = 70005, INF = 0x3f3f3f3f;

class FoxAndCity{
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
	inline int sqr(int x){return x * x;}
	int minimalCost(vector <string> g, vector <int> target){
		int i, j, k, n = g.size();
		maxFlow.init(0, n * n + 1);
		for(i = 1; i < n; ++ i)
			maxFlow.addEdge(i, i + 1, INF);
		maxFlow.addEdge(n, n * n + 1, INF);
		for(i = 1; i < n; ++ i){
			maxFlow.addEdge(0, i * n + 1, INF);
			maxFlow.addEdge((i + 1) * n, n * n + 1, INF);
			for(j = 1; j < n; ++ j)
				maxFlow.addEdge(i * n + j, i * n + j + 1, sqr(j - target[i]));
		}
		for(i = 0; i < n; ++ i)
			for(j = i + 1; j < n; ++ j){
				if(g[i][j] != 'Y') continue;
				for(k = 1; k < n; ++ k){
					maxFlow.addEdge(i * n + k + 1, j * n + k, INF);
					maxFlow.addEdge(j * n + k + 1, i * n + k, INF);
				}
			}
		return maxFlow.solve();
	}
};
