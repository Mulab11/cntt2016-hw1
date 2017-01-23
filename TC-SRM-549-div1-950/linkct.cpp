#include <cstdio>

struct Dinic{
	struct Edge{
		int n, p, r;
		void var(int a, int b, int c){
			n = a, p = b, r = c;
		}
	}edges[MAXM << 1];
	int g[MAXN], d[MAXN], edgeSize, s, t;

	void init(int s_, int t_){
		s = s_, t = t_, edgeSize = 1;
		memset(g, 0, sizeof(g));
	}
	void addEdge(int u, int v, int c){
		edges[++ edgeSize].var(v, g[u], c);
		g[u] = edgeSize;
		edges[++ edgeSize].var(u, g[v], 0);
		g[v] = edgeSize;
	}
	bool bfs(){
		int now, p;
		memset(d, 0, sizeof(d));
		q.push(s); d[s] = 1;
		while(!q.empty()){
			now = q.front(); q.pop();
			cur[now] = g[now];
			for(p = cur[now] = g[now]; p; p = edges[p].p)
				if(edges[p].r && !d[edges[p].n]){
					d[edges[p].n] = d[now] + 1;
					q.push(edges[p].n);
				}
		} return d[t];
	}
	int dfs(int x, int a){
		if(x == t || !a) return a;
		int f, flow = 0;
		for(int &p = cur[x]; p; p = nxt[p])
			if(d[edges[p].n] == d[x] + 1 && (f = dfs(edges[p].n, min(edges[p].r, a)))){
				flow += f, edges[p ^ 1].r += f;
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
class CosmicBlocks{
	public:
		int getNumOrders(vector <int> bcnt, int mn, int mx){
			
		}
}x;
