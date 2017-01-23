#include <bits/stdc++.h>
#include <cstdio>
using namespace std;
const int MAXN = 8005, MAXM = 16005, INF = 0x3f3f3f3f;

class BoardPainting{
	public:
		struct dinic{
			struct edge{
				int n, p, r;
				void var(int _n, int _p, int _r){
					n = _n, p = _p, r = _r;
				}
			}edges[MAXM << 1];
			int g[MAXN], s, t, cur[MAXN], d[MAXN], edgeSize;
			void init(int _s, int _t){
				memset(g, 0, sizeof(g));
				edgeSize = 1;
				s = _s, t = _t;
			}
			void addEdge(int f, int to, int c){
				edges[++ edgeSize].var(to, g[f], c);
				g[f] = edgeSize;
				edges[++ edgeSize].var(f, g[to], 0);
				g[to] = edgeSize;
			}
			bool bfs(){
				int p, v, now;
				memset(d, 0, sizeof(d));
				std :: queue <int> q;
				q.push(s);
				d[s] = 1;
				while(!q.empty()){
					now = q.front();
					q.pop();
					for(p = g[now]; p; p = edges[p].p){
						v = edges[p].n;
						if(!d[v] && edges[p].r){
							d[v] = d[now] + 1;
							q.push(v);
						}
					}
				}
				return d[t];
			}
			int dfs(int x, int a){
				if(x == t || !a) return a;
				int flow = 0, f;
				for(int& p = cur[x]; p; p = edges[p].p){
					edge& e = edges[p];
					if(d[e.n] == d[x] + 1 && (f = dfs(e.n, min(e.r, a))) > 0){
						e.r -= f;
						edges[p ^ 1].r += f;
						flow += f;
						a -= f;
						if(!a) return flow;
					}
				}
				return flow;
			}
			int solve(){
				int flow = 0, i;
				while(bfs()){
					for(i = s; i <= t; ++ i)
						cur[i] = g[i];
					flow += dfs(s, INF);
				}
				return flow;
			}
		}maxFlow;
		int n, m;
		int minimalSteps(vector <string> graph){
			int i, j, sum = 0;
			n = graph.size();
			m = graph[0].size();
			maxFlow.init(0, m * n * 3 + 1);
			for(i = 0; i < n; ++ i){
				for(j = 0; j < m; ++ j){
					if(graph[i][j] == '.') continue;
					sum ++;
					if(j + 1 < m && graph[i][j + 1] == '#'){
						sum --;
						maxFlow.addEdge(i * m + j + 1, n * m + i * m + j + 1, INF);
						maxFlow.addEdge(i * m + j + 2, n * m + i * m + j + 1, INF);
						maxFlow.addEdge(n * m + i * m + j + 1, n * m * 3 + 1, 1);
					}
					if(i + 1 < n && graph[i + 1][j] == '#'){
						sum --;
						maxFlow.addEdge(n * m * 2 + i * m + j + 1, i * m + j + 1, INF);
						maxFlow.addEdge(n * m * 2 + i * m + j + 1, (i + 1) * m + j + 1, INF);
						maxFlow.addEdge(0, n * m * 2 + i * m + j + 1, 1);
					}
				}
			}
			return sum + maxFlow.solve();
		}
};
