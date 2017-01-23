#include <bits/stdc++.h>
using namespace std;
typedef long long int LL;
const int MAXN = 45;
const LL MOD = 1000000009LL;

class InducedSubgraphs{
public:
	int n, k, g[MAXN], nxt[MAXN << 1], to[MAXN << 1], edgeSize;
	int size[MAXN][MAXN], dist[MAXN][MAXN], rt;
	LL ord[MAXN][MAXN], dp[MAXN][MAXN][MAXN], f[MAXN], inv[MAXN], inf[MAXN];
	void addEdge(int u, int v){
		nxt[++ edgeSize] = g[u];
		to[g[u] = edgeSize] = v;
	}
	void calc(int x, int fa, int d){
		size[x][fa] = ord[x][fa] = 1; dist[rt][x] = d;
		for(int p = g[x]; p; p = nxt[p]){
			if(to[p] == fa) continue;
			calc(to[p], x, d + 1);
			size[x][fa] += size[to[p]][x];
			ord[x][fa] = (ord[x][fa] * ord[to[p]][x] % MOD) * inf[size[to[p]][x]] % MOD;
		} (ord[x][fa] *= f[size[x][fa] - 1]) %= MOD;
	}
	int solve1(){ //Enumerate the middle chain
		int d = n - 2 * k + 1, i, j, u, v, ans = 0;
		for(i = 1; i <= n; ++ i)
			for(j = i + 1; j <= n; ++ j){
				if(dist[i][j] != d) continue;
				for(u = g[i]; u; u = nxt[u])
					if(1 + dist[to[u]][j] == d)
						break;
				if(size[i][to[u]] != k) continue;
				for(v = g[j]; v; v = nxt[v])
					if(dist[i][to[v]] + 1 == d)
						break;
				if(size[j][to[v]] != k) continue;
				ans = (ans + ord[i][to[u]] * ord[j][to[v]] * 2LL) % MOD;
			}
		return ans;
	}
	void solve(int x, int fa){ //dp[x][i][j]: number of orderings in subtree x, where x is a middle node, and there are i prev nodes & j last nodes
		int p, i, j, u, v, tmp, sz;
		dp[x][0][0] = 1;
		for(p = g[x]; p; p = nxt[p]){
			if(to[p] == fa) continue;
			solve(to[p], x); sz = size[to[p]][x];
			for(i = n - k; i >= 0; -- i)
				for(j = n - k; j >= 0; -- j){
					if(i + j >= size[x][fa]) continue;
					tmp = 0;
					//Case 1: all in [1, n - k](prev)
					if(i >= sz)
						tmp = (tmp + (dp[x][i - sz][j] * ord[to[p]][x] % MOD) * inf[sz]) % MOD;
					//Case 2: all in [k + 1, n](last)
					if(j >= sz)
						tmp = (tmp + (dp[x][i][j - sz] * ord[to[p]][x] % MOD) * inf[sz]) % MOD;
					//Case 3: at least one middle node
					for(u = 0; u <= i && u < sz; ++ u)
						for(v = 0; v <= j && u + v < sz; ++ v)
							tmp = (tmp + dp[x][i - u][j - v] * dp[to[p]][u][v]) % MOD;
					dp[x][i][j] = tmp;
				}
		}
	}
	int solve2(){
		int mid = 2 * k - n, i, ans = 0;
		for(i = 1; i <= n; ++ i){
			memset(dp, 0, sizeof(dp));
			solve(i, 0);
			if((ans += dp[i][n - k][n - k]) >= MOD)
				ans -= MOD;
		}
		return (((ans * f[n - k] % MOD) * f[n - k] % MOD) * f[mid] % MOD) * inv[mid] % MOD;
	}
	int getCount(vector <int> u, vector <int> v, int k_){
		int i; k = k_, n = u.size() + 1;
		for(i = 0; i < n - 1; ++ i){
			addEdge(u[i] + 1, v[i] + 1);
			addEdge(v[i] + 1, u[i] + 1);
		}
		for(i = f[0] = 1; i <= n; ++ i){
			f[i] = f[i - 1] * i % MOD;
			if(i == 1) inv[i] = 1;
			else inv[i] = inv[MOD % i] * (MOD - MOD / i) % MOD;
		}
		for(i = inf[0] = 1; i <= n; ++ i)
			inf[i] = inf[i - 1] * inv[i] % MOD;
		for(i = 1; i <= n; ++ i) calc(rt = i, 0, 0); //Preprocess size[][] & ord[][](ways of ordering in some subtree alone)
		if(k == 1) return f[n]; //Special case
		if(2 * k <= n) return solve1();
		return solve2();
	}
};
