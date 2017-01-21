#include <bits/stdc++.h>

#define INF 1000000007 
using namespace std ;

int src, sink, head = 0, tail = 0 ;


const int MAXN = 100010 ; 

int q[MAXN] ; 
struct Edge {
		int l, r, c, nxt;
} e[MAXN * 10] ; 

int ecnt = 1, hed[MAXN], dis[MAXN]; 

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
		for (int i = src; i <= sink; i ++) dis[i] = -1 ;
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

int id[60][60] ; 

class FoxAndGo3 {
		public:
				int maxEmptyCells(vector<string> mp) {
						int n = mp.size(), cnt = 0 ;
						for (int i = 0; i < n; i ++) {
							   for (int j = 0; j < n; j ++) {
									if (mp[i][j] == '.' || mp[i][j] == 'o') id[i][j] = ++ cnt ; 
							   }
						}
						src = 0 ;
						sink = cnt + 1; 			
						for (int i = 0; i < n; i ++) {
								for (int j = 0; j < n; j ++) {
										if (mp[i][j] == '.') { 
												adde(src, id[i][j], 1) ; 
												for (int d = 0; d < 4; d ++) { 
														int tx = i + dx[d], ty = j + dy[d] ; 
														if (0 <= tx && tx < n && 0 <= ty && ty < n && mp[tx][ty] == 'o') adde(id[i][j], id[tx][ty], INF) ; 
												}
										}
										if (mp[i][j] == 'o') adde(id[i][j], sink, 1) ; 
								}
						}
						int ans = cnt ; 
						while (bfs()) ans -= dfs(src, INF) ; 
						return ans ;
				}
};

int main() {
}

