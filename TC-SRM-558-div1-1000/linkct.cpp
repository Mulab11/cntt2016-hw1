#include <cstdio>
#include <bits/stdc++.h>
using namespace std;
const int dx[5] = {0, -1, 0, 0, 1}, dy[5] = {0, 0, -1, 1, 0}, INF = 0x3f3f3f3f, MAXN = 25 * 25 * 2, MAXM = 25 * 25 * 7;

class SurroundingGame{
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
		inline int convert(char x){
			if(x >= '0' && x <= '9') return x - '0';
			if(x >= 'a' && x <= 'z') return x - 'a' + 10;
			return x - 'A' + 36;
		}
		inline bool inmap(int x, int y){return x >= 0 && x < n && y >= 0 && y < m;}

		int maxScore(vector <string> cost, vector <string> benefit){
			int i, j, k, _i, _j, sum = 0;
			n = cost.size();
			m = cost[0].size();
			for(i = 0; i < n; ++ i){
				for(j = 0; j < m; ++ j){
					cost[i][j] = convert(cost[i][j]);
					benefit[i][j] = convert(benefit[i][j]);
				}
			}
			maxFlow.init(0, n * m * 2 + 1);
			for(i = 0; i < n; ++ i)
				for(j = 0; j < m; ++ j){
					sum += benefit[i][j];
					for(k = 0; k < 5; ++ k){ //Build extra nodes for min(x[i][j], x[i - 1][j], x[i][j - 1], x[i + 1][j], x[i][j + 1]) or max(...)
						_i = i + dx[k], _j = j + dy[k];
						if(inmap(_i, _j)){
							if((i ^ j) & 1) maxFlow.addEdge(_i * m + _j + 1, n * m + i * m + j + 1, INF);
							else maxFlow.addEdge(n * m + i * m + j + 1, _i * m + _j + 1, INF);
						}
					}
					if((i ^ j) & 1){//Black
						maxFlow.addEdge(n * m + i * m + j + 1, n * m * 2 + 1, benefit[i][j]);
						if(cost[i][j] >= benefit[i][j]) maxFlow.addEdge(i * m + j + 1, n * m * 2 + 1, cost[i][j] - benefit[i][j]);
						else{
							sum += benefit[i][j] - cost[i][j];
							maxFlow.addEdge(0, i * m + j + 1, benefit[i][j] - cost[i][j]);
						}
					}else{//White
						maxFlow.addEdge(0, n * m + i * m + j + 1, benefit[i][j]);
						if(cost[i][j] >= benefit[i][j]) maxFlow.addEdge(0, i * m + j + 1, cost[i][j] - benefit[i][j]);
						else{
							sum += benefit[i][j] - cost[i][j];
							maxFlow.addEdge(i * m + j + 1, n * m * 2 + 1, benefit[i][j] - cost[i][j]);
						}
					}
				}
			return sum - maxFlow.solve();
		}
};
