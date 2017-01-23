#include <bits/stdc++.h>
using namespace std;
const int MAXN = 635 * 3, MAXM = 635 * 7, INF = 0x3f3f3f3f;
const int dx[4] = {-1, 0, 1, 0}, dy[4] = {0, 1, 0, -1};

class CurvyonRails{
public:
	struct CostFlow{
		struct Edge{
			int n, p, r, c;
			void var(int n_, int p_, int r_, int c_){
				n = n_, p = p_, r = r_, c = c_;
			}
		}edges[MAXM << 1];
		int g[MAXN], edgeSize, s, t, dis[MAXN], en[MAXN], pre[MAXN], flow, cost;
		bool inq[MAXN]; queue <int> q;
		void init(int s_, int t_){
			memset(g, 0, sizeof(g));
			edgeSize = 1, s = s_, t = t_;
		}
		void addEdge(int u, int v, int r, int c){
			edges[++ edgeSize].var(v, g[u], r, c);
			g[u] = edgeSize;
			edges[++ edgeSize].var(u, g[v], 0, -c);
			g[v] = edgeSize;
		}
		bool BellmanFord(){
			int now, p;
			memset(dis, 0x3f, sizeof(dis));
			dis[s] = 0; q.push(s); inq[s] = true;
			while(!q.empty()){
				now = q.front(); q.pop();
				for(p = g[now]; p; p = edges[p].p)
					if(edges[p].r && dis[edges[p].n] > dis[now] + edges[p].c){
						dis[edges[p].n] = dis[now] + edges[p].c;
						pre[edges[p].n] = now, en[edges[p].n] = p;
						if(!inq[edges[p].n]){
							inq[edges[p].n] = true;
							q.push(edges[p].n);
						}
					}
				inq[now] = false;
			} return dis[t] != INF;
		}
		void augment(){
			int p, delta = INF;
			for(p = t; p != s; p = pre[p])
				delta = min(delta, edges[en[p]].r);
			cost += delta * dis[t];
			flow += delta;
			for(p = t; p != s; p = pre[p]){
				edges[en[p]].r -= delta;
				edges[en[p] ^ 1].r += delta;
			}
		}
		void solve(){
			while(BellmanFord()) augment();
		}
	}maxFlow;
	int n, m;
	int getmin(vector <string> g){
		int i, j, b = 0, w = 0, x, y, k, NM, c;
		n = g.size(), m = g[0].length();
		maxFlow.init(0, n * m * 3 + 1);
		for(i = 0, NM = n * m; i < n; ++ i)
			for(j = 0; j < m; ++ j){
				if(g[i][j] == 'w') continue;
				c = i * m + j + 1;
				if((i + j) & 1){
					maxFlow.addEdge(0, c, 2, 0), ++ b;
					if(g[i][j] == 'C'){
						maxFlow.addEdge(c, NM + c, 1, 0);
						maxFlow.addEdge(c, NM + c, 1, 1);
						maxFlow.addEdge(c, 2 * NM + c, 1, 0);
						maxFlow.addEdge(c, 2 * NM + c, 1, 1);
					}else{
						maxFlow.addEdge(c, NM + c, 2, 0);
						maxFlow.addEdge(c, 2 * NM + c, 2, 0);
					}
					for(k = 0; k < 4; ++ k){
						x = i + dx[k], y = j + dy[k];
						if(x >= 0 && x < n && y >= 0 && y < m)
							maxFlow.addEdge(((k & 1) + 1) * NM + c, ((k & 1) + 1) * NM + x * m + y + 1, 1, 0);
					}
				}else{
					maxFlow.addEdge(c, n * m * 3 + 1, 2, 0), ++ w;
					if(g[i][j] == 'C'){
						maxFlow.addEdge(NM + c, c, 1, 0);
						maxFlow.addEdge(NM + c, c, 1, 1);
						maxFlow.addEdge(2 * NM + c, c, 1, 0);
						maxFlow.addEdge(2 * NM + c, c, 1, 1);
					}else{
						maxFlow.addEdge(NM + c, c, 2, 0);
						maxFlow.addEdge(2 * NM + c, c, 2, 0);
					}
				}
			}
		maxFlow.solve();
		if(maxFlow.flow != 2 * w || maxFlow.flow != 2 * b) return -1;
		return maxFlow.cost;
	}
};
