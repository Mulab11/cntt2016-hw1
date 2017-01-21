#include <bits/stdc++.h>

#define MOD 1000000007 

using namespace std ;

int n, m, d; 

const int MAXN = 110 ; 

bool vis[MAXN][MAXN] ; 

int cnt = 0 ;

void Dfs(int x, int y) { 
		cnt ++ ; 
		for (int i = 0; i < n; i ++) {
				for (int j = 0; j < m; j ++) { 
						if (!vis[i][j] && abs(x - i) + abs(y - j) <= d) vis[i][j] = 1, Dfs(i, j) ; 
				}
		}
}
class GooseInZooDivOne {
		public:
				int count(vector<string> a, int dist) {
						d = dist ; 
						n = a.size() ; 
						m = a[0].size() ; 
						int v[2] = {0, 0} ; 
						for (int i = 0; i < n; i ++) for (int j = 0; j < m; j ++) if (a[i][j] == 'v' && !vis[i][j]) vis[i][j] = 1, cnt = 0, Dfs(i, j), v[cnt & 1] ++ ; 
						int ans = 1 ; 
						v[1] -- ;
						while (v[1] > 0) v[1] --, ans = (ans << 1) % MOD ; 
						while (v[0] --) ans = (ans << 1) % MOD ; 
						return (ans - 1 + MOD) % MOD ; 
				}
};

