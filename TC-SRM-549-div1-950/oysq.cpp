#line 2 "CosmicBlocks.cpp"  
#include <bits/stdc++.h> 

using namespace std;  

#define ui unsigned
#define ll long long

#define pii std::pair<int,int>
#define mp std::make_pair
#define fi first
#define se second

#define SZ(x) (int)(x).size()
#define pb push_back

template<class T>inline void chkmax(T &x, const T &y) {if(x < y) x = y;}
template<class T>inline void chkmin(T &x, const T &y) {if(x > y) x = y;}

const int N = 6;
const int INF = 1e9;

int n, fac[N + 9];
std::vector<int> p;
int minw, maxw;

std::vector<int> fl[N + 9];

int st[N + 9][N + 9];
int g[N + 9];

// calc num of valid matching condition
int dfs2(int x, int cur, int m) {
	if(x == m) {
		// dp num of ways to remove
		// g[i] means i's precursor
		int f[1 << N] = {0};
		f[0] = 1;
		for(int i = 1; i < (1 << n); ++i)
			for(int j = 0; j < n; ++j)
				if((i >> j & 1) && (g[j] & i) == g[j])
					f[i] += f[i ^ (1 << j)];
		return f[(1 << n) - 1] >= minw && f[(1 << n) - 1] <= maxw;
	}
	if(cur == SZ(fl[x])) {
		// check positive
		for(int i = 0; i < SZ(fl[x - 1]); ++i)
			if(p[fl[x - 1][i]] < 0) return 0;
		for(int i = 0; i < SZ(fl[x]); ++i)
			if(p[fl[x][i]] < 0) return 0;
		// Hall theorem to decide if valid
		for(int i = 0; i < (1 << SZ(fl[x])); ++i) {
			int s = 0, a = 0, b = 0;
			for(int j = 0; j < SZ(fl[x]); ++j)
				if(i >> j & 1)
					s |= st[x][j], a += p[fl[x][j]];
			for(int j = 0; j < SZ(fl[x - 1]); ++j)
				if(s >> j & 1)
					b += p[fl[x - 1][j]];
			if(b < a) return 0;
		}
		// backup info
		std::vector<int> tp = p;
		for(int i = 0; i < SZ(fl[x]); ++i)
			p[fl[x][i]] += __builtin_popcount(st[x][i]);
		int ret = dfs2(x + 1, 0, m);
		p = tp;
		return ret;
	}
	int ret = 0;
	// enumerate matching
	for(int i = 1; i < (1 << SZ(fl[x - 1])); ++i) {
		for(int j = 0; j < SZ(fl[x - 1]); ++j)
			if(i >> j & 1) p[fl[x - 1][j]]--, p[fl[x][cur]]--, g[fl[x - 1][j]] |= 1 << fl[x][cur];
		st[x][cur] = i;
		ret += dfs2(x, cur + 1, m);
		st[x][cur] = -1;
		for(int j = 0; j < SZ(fl[x - 1]); ++j)
			if(i >> j & 1) p[fl[x - 1][j]]++, p[fl[x][cur]]++, g[fl[x - 1][j]] ^= 1 << fl[x][cur];
	}
	return ret;
}

int calc(int m) {
	memset(st, -1, sizeof st);
	return dfs2(1, 0, m);
}

// decide which color on which floor
int dfs(int x, int used, int last) {
	if(used == (1 << n) - 1) return calc(x);
	int ret = 0;
	for(int i = 1; i < (1 << n); ++i)
		if(!(used & i)) {
			fl[x].clear();
			int sum = 0;
			for(int j = 0; j < n; ++j)
				if(i >> j & 1)
					fl[x].pb(j), sum += p[j];
			if(sum <= last) ret += dfs(x + 1, used | i, sum);
		}
	return ret;
}

class CosmicBlocks {  
public:  
	int getNumOrders(vector <int> _p, int _minw, int _maxw) {
		// copy info
		p = _p, minw = _minw, maxw = _maxw, n = SZ(p);
		// factorial
		fac[0] = 1;
		for(int i = 1; i <= n; ++i) fac[i] = fac[i - 1] * i;
		// calc ans
		return dfs(0, 0, INF);
	}  
};  
