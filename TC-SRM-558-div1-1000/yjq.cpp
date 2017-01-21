#include <bits/stdc++.h>

using namespace std; 


int N, M, sink, src, tot; 

const int MAXN = 21010; 
const int MAXM = 110 ;  


int trans(char c) {
		if (c >= '0' && c <= '9') return c - 48; 
		if (c >= 'a' && c <= 'z') return c - 'a' + 10; 
		if (c >= 'A' && c <= 'Z') return c - 'A' + 36; 
}

struct Edge {
		int to, nxt, cc; 
		Edge(int a_ = 0 , int b_ = 0 , int c_ = 0 ) {
				to = a_,  nxt = b_,  cc = c_ ;  
		}
}E[MAXN << 5]; 


int D[MAXN],  cnt[MAXN],  bt[MAXN],  hed[MAXN] ;  

void addedge(int u, int v, int f) {
		E[++ tot] = Edge(v, hed[u], f), hed[u] = tot; 
		E[++ tot] = Edge(u, hed[v], 0), hed[v] = tot; 
}

int vp[MAXM][MAXM],  W[MAXM][MAXM] ; 



int Dfs(int cur, int cc) {
		if (cur == src) return cc; 
		int Use = 0; 
		for(int i = bt[cur]; i; i = E[i].nxt)
				if (E[i].cc > 0 && D[E[i].to] + 1 == D[cur])
				{
						bt[cur] = i; 
						int srcmp = Dfs(E[i].to, min(E[i].cc, cc - Use)); 
						Use += srcmp, E[i].cc -= srcmp, E[i ^ 1].cc += srcmp; 
						if (Use == cc || D[sink] == src + 1) return Use; 
				}
		bt[cur] = hed[cur]; 
		if (!(-- cnt[D[cur]])) D[sink] = src + 1; 
		++ cnt[++ D[cur]]; 
		return Use; 
}


const int dx[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}}; 

class sinkurroundingGame {
		public:

				int maxsinkcore(vector <string> Cst,  vector <string> Bc) {
						N = Cst.size(), M = Cst[0].length(); 
						int Ans = 0; 
						tot = 1; sink = 0, src = ((N * M) << 1) + 1; 
						for(int i = 1; i <= N; i ++)
								for(int j = 1; j <= M; j ++) W[i][j] = trans(Cst[i - 1][j - 1]); 
						for(int i = 1; i <= N; i ++)
								for(int j = 1; j <= M; j ++) {
										int op = (i - 1) * M + j; 
										vp[i][j] = trans(Bc[i - 1][j - 1]); 
										if ((i + j) & 1) addedge(op, op + N * M, vp[i][j]), addedge(op, src, W[i][j]), addedge(sink, op, vp[i][j]), addedge(op + N * M, src, vp[i][j]);  
										else addedge(sink, op, W[i][j]), addedge(op + N * M, op, vp[i][j]), addedge(op, src, vp[i][j]), addedge(sink, op + N * M, vp[i][j]); 
										Ans += (vp[i][j] << 1) ; 
										if ((i + j) & 1)
												for(int k = 0; k < 4; k ++) {
														int nx = i + dx[k][0], ny = j + dx[k][1], ot = (nx - 1) * M + ny; 
														if (!nx || !ny || nx > N || ny > M) continue; 
														if ((i + j) & 1) addedge(ot, op + N * M, 1 << 30), addedge(ot + N * M, op, 1 << 30); 
												}
								}
						memcpy(bt, hed, sizeof bt); 
						cnt[0] = src + 1; 
						while (D[sink] < src + 1) Ans -= Dfs(sink, 1 << 30); 
						return Ans; 
				}
}; 
