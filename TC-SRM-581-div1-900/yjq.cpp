#include <bits/stdc++.h>

#define INF 1000000007 
using namespace std ;

int n, m, M ;

const int MAXN = 16 ; 

int a[MAXN], C[1 << MAXN] , ans = INF; 

int Calc(int dep, int b, int c, int d, int typ) {
		if (dep == n) return ( b > 0 ? INF : 0) ; 
		int tmp = (b & d) ; 
		int cur = INF ;  
		if (!(typ & tmp)) {
				int tb = a[dep] ^ c ^ (b >> 1) ^ ((b << 1) % M) ;
				cur = min(cur, Calc(dep + 1, tb, b, b | d, typ) + C[b]) ; 
		}
		if (!(~typ & tmp)) { 
				int tb = a[dep] ^ c ^ (b >> 1) ^ ((b << 1) % M) ^ b ; 
				cur = min(cur, Calc(dep + 1, tb, b, b | d, typ | b) + C[b]) ; 
		}
		return cur ; 
}

class YetAnotherBoardGame {
		public:
				int minimumMoves(vector<string> b) {
						n = b.size(), m = b[0].size(), M = (1 << m) ; 
						for (int i = 0; i < n; i ++) for (int j = 0; j < m; j ++) if (b[i][j] == 'W') a[i] |= (1 << j) ; 
						for (int i = 0; i < n; i ++) C[i] = C[i >> 1] + (i & 1) ; 	
						for (int i = 0; i < M; i ++) for (int j = 0; j < 2; j ++) {
								int tb = a[0] ^ (i >> 1) ^ ((i << 1) % M) ^ (i * j) ; 
								ans = min(ans, Calc(1, tb, i, i, j * i) + C[i]) ; 
						}
						if (ans == INF) return -1 ; 
						return ans ; 
				}
};
