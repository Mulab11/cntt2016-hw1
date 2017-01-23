#include <bits/stdc++.h>
using namespace std;
const int MAXN = 55, MAXM = MAXN * MAXN, INF = 0x3f3f3f3f;

class GearsDiv1{
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
	int n; vector <int> gear[5];
	inline int id(char x){return x == 'R' ? 1 : (x == 'G' ? 2 : 3);}
	int getmin(string col, vector <string> g){
		int i, j, k, u, v, ans = n = col.length();
		for(i = 0; i < n; ++ i)
			gear[id(col[i])].push_back(i);
		for(i = 1; i <= 3; ++ i){
			maxFlow.init(0, n + 1);
			for(j = 1; j == i; ++ j) ;
			for(k = 3; k == i; -- k) ;
			for(u = 0; u < int(gear[j].size()); ++ u){
				maxFlow.addEdge(0, gear[j][u] + 1, 1);
				for(v = 0; v < int(gear[k].size()); ++ v)
					if(g[gear[j][u]][gear[k][v]] == 'Y')
						maxFlow.addEdge(gear[j][u] + 1, gear[k][v] + 1, 1);
			}
			for(u = 0; u < int(gear[k].size()); ++ u)
				maxFlow.addEdge(gear[k][u] + 1, n + 1, 1);
			ans = min(ans, n - maxFlow.solve());
		} return ans;
	}
};
