#include <bits/stdc++.h>

#define INF 1000000007
using namespace std ;

int n, m, src, sink ; 

const int MAXN = 2510 ;

struct Edge {
		int l, r, c, nxt;
} e[MAXN * 100] ;

int ecnt = 1, hed[MAXN] ; 

void addedge(int l, int r, int c) {
		++ecnt, e[ecnt].l = l, e[ecnt].r = r, e[ecnt].c = c, e[ecnt].nxt = hed[l], hed[l] = ecnt ;
} 

void adde(int l, int r, int c) { 
		addedge(l, r, c), addedge(r, l, 0) ;
}

int dx[4] = {0, 0, -1, 1}, dy[4] = {1, -1, 0, 0} ; 

int P(int x, int y) {
		return x * m + y + 1 ; 
}

int dis[MAXN], q[MAXN], head = 0, tail = 0 ;

bool Bfs() {
		q[head = tail = 0] = src ; 
		memset(dis, -1, sizeof dis) ; 
		dis[src] = 0 ;
		while (head <= tail) { 
				int cur = q[head ++] ;
				for (int i = hed[cur]; i; i = e[i].nxt) {
						int to = e[i].r ; 
						if (dis[to] < 0 && e[i].c) dis[to] = dis[cur] + 1, q[++tail] = to ; 
				}
		}
		return dis[sink] >= 0 ; 
}

int Dfs(int cur, int flow) { 
		if (cur == sink) return flow ; 
		int ret = flow ; 
		for (int i = hed[cur]; i && ret; i = e[i].nxt) {
				int to = e[i].r ;
				if (dis[to] == dis[cur] + 1 && e[i].c) {
						int delta = Dfs(to, min(ret, e[i].c)) ;
						ret -= delta ;
						e[i].c -= delta ;
						e[i ^ 1].c += delta ;
				}
		}
		if (ret == flow) dis[cur] = -2 ;
		return flow - ret ;
}

class BoardPainting {
		public :
				int minimalSteps(vector<string> mp) { 
						n = mp.size() ; 
						m = mp[0].length() ; 
						int ans = 0 , tmp = 0;
						sink = n * m + 1, src = 0 ; 
						for (int i = 0; i < n; i ++) { 
								for (int j = 0; j < m; j ++) { 
										if (mp[i][j] == '#') {
												ans ++ ; 
												for (int d = 0; d < 4; d ++) { 
														int tx = i + dx[d], ty = j + dy[d] ; 
														if (0 <= tx && tx < n && 0 <= ty && ty < m) { 
																if (mp[tx][ty] == '#') {
																		tmp += 2 ; 
																		adde(P(tx, ty), P(i, j), 1) ; 
																		adde(P(i, j), P(tx, ty), 1) ; 
																		if (dx[d] == 0) { 
																				adde(P(tx, ty), sink, 1) ; 
																				adde(P(i, j), sink, 1) ; 
																		}
																		else {
																				adde(src, P(tx, ty), 1) ;
																				adde(src, P(i, j), 1) ; 
																		}
																}
														}
												}
										}
								}
						}
						while (Bfs()) tmp -= Dfs(src, INF) ; 
						tmp >>= 2 ; 
						return ans - tmp ; 
				}
} ;


