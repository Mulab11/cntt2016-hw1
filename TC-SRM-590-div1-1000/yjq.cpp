#include <bits/stdc++.h>

#define INF 1000000007 
using namespace std ;

int src, sink, head = 0, tail = 0 ;


const int MAXN = 60 ; 

int q[MAXN * MAXN] ; 
struct Edge {
		int l, r, c, nxt;
} e[MAXN * MAXN * MAXN * 10] ; 

int ecnt = 1, hed[MAXN * MAXN], dis[MAXN * MAXN]; 

void addedge(int l, int r, int c) {
		++ecnt, e[ecnt].l = l, e[ecnt].r = r, e[ecnt].c = c, e[ecnt].nxt = hed[l], hed[l] = ecnt ;
}

void adde(int l, int r, int c) {
		addedge(l, r, c); 
		addedge(r, l, 0) ;
}

int dx[4] = {0, 0, 1, -1}, dy[4] = {1, -1, 0, 0} ; 
bool bfs() { 
		q[head = tail = 0] = src ;
		memset(dis, -1, sizeof dis) ; 
		dis[src] = 0 ; 
		while (head <= tail) {
			   int cur = q[head ++] ;
			   for (int i = hed[cur]; i; i = e[i].nxt) {
						int to = e[i].r ; 
						if (e[i].c && dis[to] < 0) dis[to] = dis[cur] + 1, q[++tail] = to ; 
			   }
		}
		return dis[sink] >= 0 ;
}

int dfs(int cur, int flow) { 
		if (cur == sink) return flow ;
		int ret = flow ; 
		for (int i = hed[cur]; i && ret; i = e[i].nxt) { 
				int to = e[i].r ;
				if (dis[to] == dis[cur] + 1 && e[i].c) { 
						int delta = dfs(to, min(ret, e[i].c)) ; 
						ret -= delta ;
						e[i].c -= delta; 
						e[i ^ 1].c += delta ; 
				}
		}
		if (flow == ret) dis[cur] = -2 ; 
		return flow - ret ;
}


class FoxAndCity {
		public:

				int minimalCost(std::vector<std::string> linked, std::vector<int> want) {
						int n = linked.size();
						src = n * (n + 1), sink = n * (n + 1) + 1 ; 
						for (int i = 0; i < n; i++) {
								adde(src, i * (n + 1), INF);
								adde(i * (n + 1) + n, sink, INF);
								for (int j = 0; j < n; j++) {
										int w = i == 0 ? (j == 0 ? 0 : INF) : (j == 0 ? INF : (j - want[i]) * (j - want[i]));
										adde(i * (n + 1) + j, i * (n + 1) + j + 1, w);
								}
						}
						for (int i = 0; i < n; i++) {
								for (int j = 0; j < n; j++) {
										if (linked[i][j] == 'Y') {
												for (int k = 0; k < n; k++) {
														adde(j * (n + 1) + k + 1, i * (n + 1) + k, INF);
												}
										}
								}
						}
						int ans = 0 ;
						while (bfs()) ans += dfs(src, INF) ; 
						return ans ; 
				}
} ;
