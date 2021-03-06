#line 2 "TheBrickTowerHardDivOne.cpp"  
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

const int C = 5000;
const ll MOD = 1234567891;

ll fac[C + 9], inv[C + 9];

// fast power
ll fpm(ll a, ll b) {
	a %= MOD;
	ll ret = 1;
	while(b) {
		if(b & 1) ret = ret * a % MOD;
		a = a * a % MOD, b >>= 1;
	}
	return ret;
}

// P(n, m) = n! / (n - m)!
ll perm(ll n, ll m) {
	if(n < m) return 0;
	return fac[n] * inv[n - m] % MOD;
}

struct state {
	int g[2][2];
	state() {g[0][0] = g[0][1] = g[1][0] = g[1][1] = -1;}
	friend bool operator < (const state &p, const state &q) {
		if(p.g[0][0] != q.g[0][0]) return p.g[0][0] < q.g[0][0];
		if(p.g[0][1] != q.g[0][1]) return p.g[0][1] < q.g[0][1];
		if(p.g[1][0] != q.g[1][0]) return p.g[1][0] < q.g[1][0];
		if(p.g[1][1] != q.g[1][1]) return p.g[1][1] < q.g[1][1];
		return false;
	}
	// maxcolor : starts from 0
	int maxcol() const {
		return std::max(g[0][0], std::max(g[0][1], std::max(g[1][0], g[1][1])));
	}
	// count the number of same pairs 
	int count() const {
		return (g[0][0] == g[0][1]) + (g[0][1] == g[1][1]) + (g[1][1] == g[1][0]) + (g[1][0] == g[0][0]);
	}
};

const int S = 120;

ll g[S + 9][S + 9];
ll a[S + 9][S + 9];

// matrix multiplication
void mult(ll a[S + 9][S + 9], ll b[S + 9][S + 9], int n) {
	ll c[S + 9][S + 9] = {0};
	for(int i = 0; i <= n; ++i)
		for(int j = 0; j <= n; ++j)
			for(int k = 0; k <= n; ++k)
				(c[i][j] += a[i][k] * b[k][j] % MOD) %= MOD;
	for(int i = 0; i <= n; ++i)
		for(int j = 0; j <= n; ++j)
			a[i][j] = c[i][j];
}

// change the state to its minimal representation
state change(const state &s) {
	state ret;
	int f[8];
	memset(f, -1, sizeof f);
	int c = -1;
	for(int i = 0; i < 2; ++i)
		for(int j = 0; j < 2; ++j) {
			if(f[s.g[i][j]] == -1)
				f[s.g[i][j]] = ++c;
			ret.g[i][j] = f[s.g[i][j]];
		}
	return ret;
}

class TheBrickTowerHardDivOne {  
public:
	// find all valid state
	void dfs_state(int x, int y, int c, std::vector<state> &s, std::map<state, int> &id, state &cur, int col, int maxn) {
		int nx = x, ny = y;
		ny++;
		if(ny == 2) nx++, ny = 0;
		for(int i = 0; i <= c + 1 && i < col; ++i) {
			cur.g[x][y] = i;
			if(nx == 2) {
				if(cur.count() <= maxn) s.pb(cur), id[cur] = SZ(s) - 1;
			}
			else dfs_state(nx, ny, std::max(c, i), s, id, cur, col, maxn);
			cur.g[x][y] = -1;
		}
	}
	// find all tranfers between states
	void dfs_trans(int x, int y, int c, int frid, state &fr, state &cur, int col, int maxn, int sn, std::map<state, int> &id) {
		int nx = x, ny = y;
		ny++;
		if(ny == 2) nx++, ny = 0;
		for(int i = 0; i <= c + 1 && i < col; ++i) {
			cur.g[x][y] = i;
			if(nx == 2) {
				int add = cur.count();
				for(int a = 0; a < 2; ++a)
					for(int b = 0; b < 2; ++b)
						add += cur.g[a][b] == fr.g[a][b];
				// add means extended same pairs in this transfer
				int curid = id[change(cur)], num = perm(col - fr.maxcol() - 1, std::max(c, i) - fr.maxcol());
				// num means the number of arrangementes of colors in current condition
				for(int j = 0; j + add <= maxn; ++j)
					(g[frid + j * sn][curid + (j + add) * sn] += num) %= MOD;
			}
			else dfs_trans(nx, ny, std::max(c, i), frid, fr, cur, col, maxn, sn, id);
			cur.g[x][y] = -1;
		}
	}
	int find(int col, int maxn, long long n) {
		// precalculate the factorial and its inversion
		fac[0] = 1;
		for(int i = 1; i <= col; ++i) fac[i] = fac[i - 1] * i % MOD;
		inv[col] = fpm(fac[col], MOD - 2);
		for(int i = col - 1; i >= 0; --i) inv[i] = inv[i + 1] * (i + 1) % MOD;

		std::vector<state> s;// contains all states
		std::map<state, int> id;// id[x] means state x's id
		state ini;
		dfs_state(0, 0, -1, s, id, ini, col, maxn);
		memset(g, 0, sizeof g);
		for(int i = 0; i < SZ(s); ++i)
			dfs_trans(0, 0, s[i].maxcol(), i, s[i], ini, col, maxn, SZ(s), id);

		int m = SZ(s) * (maxn + 1);

		for(int i = 0; i <= m; ++i) g[i][m] = 1;// to sum up the value from 1 ~ n

		// for(int i = 0; i <= m; ++i)
			// for(int j = 0; j <= m; ++j)
				// printf("%lld%c", g[i][j], j == m ? '\n' : ' ');

		memset(a, 0, sizeof a);
		for(int i = 0; i <= m; ++i) a[i][i] = 1;// initial matrix
		while(n) {
			if(n & 1) mult(a, g, m);
			mult(g, g, m), n >>= 1;
		}
		ll ans = 0;
		for(int i = 0; i < SZ(s); ++i)// enumerate the color of first floor
			(ans += perm(col, s[i].maxcol() + 1) * a[i + s[i].count() * SZ(s)][m] % MOD) %= MOD;
		return ans;
	}    
};
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                   