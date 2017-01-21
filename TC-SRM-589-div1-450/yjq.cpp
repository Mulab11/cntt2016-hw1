#include <bits/stdc++.h>

#define INF 1000000007
using namespace std ;

int src, sink ; 

const int MAXN = 110 ;

struct Edge {
		int l, r, c, nxt;
} e[MAXN * MAXN] ;

int ecnt = 1, hed[MAXN], typ[MAXN] ;

void addedge(int l, int r, int c) {
		++ecnt, e[ecnt].l = l, e[ecnt].r = r, e[ecnt].c = c, e[ecnt].nxt = hed[l], hed[l] = ecnt ; 
}

void adde(int l, int r, int c) {
		addedge(l, r, c) ;
		addedge(r, l, 0) ; 
}

void Init() {
		ecnt = 1 ;
		memset(hed, 0, sizeof hed) ;
}

int get_typ(char a) {
		if (a == 'R') return 0 ;
		if (a == 'G') return 1 ;
		return 2 ;
}

int dis[MAXN], q[MAXN], head = 0, tail = 0 ;

bool Bfs() {
		q[head = tail = 1] = src; 
		memset(dis, -1, sizeof dis) ; 
		dis[src] = 0;
		while (head <= tail) { 
				int cur = q[head ++] ;
				for (int i = hed[cur] ; i; i = e[i].nxt) {
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

class GearsDiv1 {
		public :
				int getmin(string c, vector<string> mp) { 
						int n = c.length() ; 
						src = 0, sink = n + 1 ;
						for (int i = 0; i < n; i ++) {
								typ[i + 1] = get_typ(c[i]) ; 
						}
						int ans = 1 << 30 ; 
						// Remove R 
						Init() ;
						for (int i = 0; i < n; i ++) {
							   if (typ[i + 1]) { 
								   if (typ[i + 1] == 1) adde(src, i + 1, 1) ; 
								   else adde(i + 1, sink, 1) ; 
							   }
						}
						for (int i = 0; i < n; i ++) {
								for (int j = i + 1; j < n; j ++) { 
										if (typ[i + 1] != 0 && typ[j + 1] != 0 && mp[i][j] == 'Y') {
												if (typ[i + 1] == 1) adde(i + 1, j + 1, 1) ;
												else adde(j + 1, i + 1, 1) ; 
										}
								}
						}
						int tmp = 0 ;
						while (Bfs()) tmp += Dfs(src, INF) ; 
						ans = min(ans, tmp) ; 
						// Remove G 
						Init() ;
						for (int i = 0; i < n; i ++) {
							   if (typ[i + 1] != 1) { 
								   if (typ[i + 1] == 0) adde(src, i + 1, 1) ; 
								   else adde(i + 1, sink, 1) ; 
							   }
						}
						for (int i = 0; i < n; i ++) {
								for (int j = i + 1; j < n; j ++) { 
										if (typ[i + 1] != 1 && typ[j + 1] != 1 && mp[i][j] == 'Y') {
												if (typ[i + 1] == 0) adde(i + 1, j + 1, 1) ;
												else adde(j + 1, i + 1, 1) ; 
										}
								}
						}
						tmp = 0 ;
						while (Bfs()) tmp += Dfs(src, INF) ; 
						ans = min(ans, tmp) ; 
						Init() ;
						for (int i = 0; i < n; i ++) {
							   if (typ[i + 1] != 2) { 
								   if (typ[i + 1] == 0) adde(src, i + 1, 1) ; 
								   else adde(i + 1, sink, 1) ; 
							   }
						}
						for (int i = 0; i < n; i ++) {
								for (int j = i + 1; j < n; j ++) { 
										if (typ[i + 1] != 2 && typ[j + 1] != 2 && mp[i][j] == 'Y') {
												if (typ[i + 1] == 0) adde(i + 1, j + 1, 1) ;
												else adde(j + 1, i + 1, 1) ; 
										}
								}
						}
						tmp = 0 ;
						while (Bfs()) tmp += Dfs(src, INF) ; 
						ans = min(ans, tmp) ;
						return ans ; 
				}
} solution ;

string a[110] = {"NYY","YNY","YYN"}, b = "RGB" ; 

vector<string> g ; 

int main() { 
		int n = 3 ; 
		for (int i = 0; i < n; i ++) g.push_back(a[i]) ; 
		printf("%d\n", solution.getmin(b, g)) ; 
}



									   
							



