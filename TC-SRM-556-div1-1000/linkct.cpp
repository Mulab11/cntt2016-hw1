#include <bits/stdc++.h>
using namespace std;
const int MAXN = 55, MAXM = MAXN * MAXN, INF = 0x3f3f3f3f;

class OldBridges{
public:
	struct Dinic{
		struct Edge{
			int n, p, r;
			void var(int a, int b, int c){
				n = a, p = b, r = c;
			}
		}edges[MAXM << 1];
		queue <int> q;
		int g[MAXN], s, t, d[MAXN], edgeSize, cur[MAXN];
		void init(int s_, int t_){
			s = s_, t = t_, edgeSize = 1;
			memset(g, 0, sizeof(g));
		}
		void addEdge(int u, int v, int c){
			edges[++ edgeSize].var(v, g[u], c);
			g[u] = edgeSize;
			edges[++ edgeSize].var(u, g[v], c);
			g[v] = edgeSize;
		}
		bool bfs(){
			int now, p;
			memset(d, 0, sizeof(d));
			q.push(s), d[s] = 1;
			while(!q.empty()){
				now = q.front(); q.pop();
				for(p = cur[now] = g[now]; p; p = edges[p].p)
					if(!d[edges[p].n] && edges[p].r)
						q.push(edges[p].n), d[edges[p].n] = d[now] + 1;
			} return d[t];
		}
		int dfs(int x, int a){
			if(x == t || !a) return a;
			int f, flow = 0;
			for(int &p = cur[x]; p; p = edges[p].p)
				if(d[edges[p].n] == d[x] + 1 && (f = dfs(edges[p].n, min(edges[p].r, a)))){
					flow += f, edges[p ^ 1].r += f;
					edges[p].r -= f; if(!(a -= f)) return flow;
				}
			return flow;
		}
		int solve(){
			int ret = 0;
			while(bfs()) ret += dfs(s, INF);
			return ret;
		}
	}maxFlow;
	vector <string> g; int n;
	void buildGraph(){
		int i, j;
		maxFlow.init(0, n + 1);
		for(i = 0; i < n; ++ i)
			for(j = 0; j < i; ++ j)
				if(g[i][j] == 'O') maxFlow.addEdge(i + 1, j + 1, 1);
				else if(g[i][j] == 'N') maxFlow.addEdge(i + 1, j + 1, INF);
	}
	string isPossible(vector <string> g_, int a1, int a2, int an, int b1, int b2, int bn){
		g = g_, n = g.size();
        ++ a1, ++ a2, ++ b1, ++ b2;
		buildGraph();
		maxFlow.addEdge(0, a1, an);
		maxFlow.addEdge(0, b1, bn);
		maxFlow.addEdge(a2, n + 1, an);
		maxFlow.addEdge(b2, n + 1, bn);
		if(maxFlow.solve() != an + bn) return "No";
		buildGraph();
		maxFlow.addEdge(0, a1, an);
		maxFlow.addEdge(0, b2, bn);
		maxFlow.addEdge(a2, n + 1, an);
		maxFlow.addEdge(b1, n + 1, bn);
		if(maxFlow.solve() != an + bn) return "No";
		return "Yes";
	}
};
