#include <bits/stdc++.h>
using namespace std;
const int MAXN = 55, MOD = 1000000007;

class GooseInZooDivOne{
public:
	int f[MAXN * MAXN], n, m;
	int find(int x){return f[x] < 0 ? x : (f[x] = find(f[x]));}
	void merge(int u, int v){
		u = find(u), v = find(v);
		if(u == v) return;
		if(f[u] > f[v]) swap(u, v);
		f[u] += f[v], f[v] = u;
	}
	int count(vector <string> g, int dis){
		int i, j, u, v, odd, even;
		n = g.size(), m = g[0].length();
		memset(f, -1, sizeof(f));
		for(i = 0; i < n; ++ i)
			for(j = 0; j < m; ++ j){
				if(g[i][j] != 'v') continue;
				for(u = 0; i + u < n; ++ u)
					for(v = -j; v + j < m; ++ v)
						if(u + abs(v) <= dis && g[i + u][j + v] == 'v')
							merge(i * m + j + 1, (i + u) * m + j + v + 1);
			}
		odd = 0, even = 1;
		for(i = 0; i < n; ++ i)
			for(j = 0; j < m; ++ j){
				if(g[i][j] != 'v' || find(i * m + j + 1) != i * m + j + 1) continue;
				if((- f[i * m + j + 1]) & 1)
					odd = (odd + even) % MOD, even = odd;
				else (odd <<= 1) %= MOD, (even <<= 1) %= MOD;
			}
		return (even - 1 + MOD) % MOD;
	}
};
