#include <bits/stdc++.h>

#define rep(i, x, y) for (int i = (x), _ = (y); i <= _; ++i)
#define down(i, x, y) for (int i = (x), _ = (y); i >= _; --i)
#define x first
#define y second
#define mp make_pair
#define pb push_back
#define LX_JUDGE

using namespace std;
typedef long long LL;

template<typename T> inline void upmax(T & x, T y) { x < y ? x = y : 0; }
template<typename T> inline void upmin(T & x, T y) { x > y ? x = y : 0; }

const int inf = 0x3f3f3f3f;
const int mo = 1e9 + 9;
const int N = 42;

struct info
{
	int e[N][N], len;
	inline const int * operator [](const int x) const
	{
		return e[x];
	}
	inline int * operator [](const int x) 
	{
		return e[x];
	}
};

class InducedSubgraphs
{
public : 
	int n;
	int C[N][N], fac[N];
	bool adj[N][N];
	int cnt[N][N];
	int perm[N][N];
	info dp[N][N];

	inline void upd(int & x, int y)
	{
		(x += y) >= mo ? x -= mo : 0;
	}

	void dfs_1(int x, int fa)
	{
		if (cnt[fa][x])
			return ;
		perm[fa][x] = 1;
		int sum = 0;
		rep (i, 0, n - 1) 
		{
			if (adj[x][i] && fa != i)
			{
				dfs_1(i, x);
				int s = C[sum + cnt[x][i]][sum];
				int t = perm[x][i];
				perm[fa][x] = (LL) perm[fa][x] * s % mo * t % mo;
				sum += cnt[x][i];
			}
		}
		cnt[fa][x] = sum + 1;
	}
    
	int solve_1(int K)
	{
		static int dis[N][N];

		rep (i, 0, n - 1) rep (j, 0, n - 1)
			dis[i][j] = adj[i][j] ? 1 : inf;

		rep (i, 0, n - 1)
			dis[i][i] = 0;

		rep (k, 0, n - 1)
		{
			rep (i, 0, n - 1) rep (j, 0, n - 1)
				upmin(dis[i][j], dis[i][k] + dis[k][j]);
		}

		int d = n - 2 * K + 1;
		int ans = 0;

		rep (x, 0, n - 1) rep (y, 0, n - 1)
		{
			if (x != y && dis[x][y] == d)
			{
				int a = 0, b = 0;
				while (!adj[a][x] || dis[a][y] >= dis[x][y])
					++a;
				while (!adj[b][y] || dis[x][b] >= dis[x][y])
					++b;
				if (cnt[a][x] == K && cnt[b][y] == K)
					upd(ans, (LL) perm[a][x] * perm[b][y] % mo);
			}
		}

		return ans;
	}
    
	void merge(const info & a, const info & b, info & c)
	{
		static info ret;
		int A = a.len, B = b.len, L = A + B;

		rep (i, 0, L) rep (j, 0, L)
			ret[i][j] = 0;

		rep (i, 0, A) rep (j, 0, A)
		{
			rep (k, 0, B) rep (l, 0, B)
			{
				LL p = (LL) a[i][j] * b[k][l] % mo;
				int q = C[i + k][k];
				int r = C[j + l][l];
				upd(ret[i + k][j + l], p * q % mo * r % mo);
			}
		}

		rep (i, 0, L) rep (j, 0, L)
			c[i][j] = ret[i][j];
		c.len = L;
	}
    
	void dfs_2(int x, int fa)
	{
		if (dp[fa][x].len == 0)
		{
			info & a = dp[fa][x];
			a.len = 1;
			a[0][0] = 1;
			rep (i, 0, n - 1) 
			{
				if (adj[x][i] && fa != i)
				{
					dfs_2(i, x);
					merge(a, dp[x][i], a);
				}
			}
			a[cnt[fa][x]][0] = perm[fa][x];
			a[0][cnt[fa][x]] = perm[fa][x];
		}
	}

	int solve_2(int K)
	{
		int ans = 0;
		rep (i, 0, n - 1)
		{
			dfs_2(i, n);
			upd(ans, dp[n][i][n - K][n - K]);
		}
		return (LL) ans * fac[2 * K - n - 1] % mo;
	}

	int getCount(vector<int> e_l, vector<int> e_r, int K)
	{
		n = e_l.size() + 1;

		fac[0] = 1;
		rep (i, 1, n)
			fac[i] = (LL) fac[i - 1] * i % mo;

		if (K == 1)
			return fac[n];

		rep (i, 0, n - 2)
			adj[e_l[i]][e_r[i]] = adj[e_r[i]][e_l[i]] = 1;

		C[0][0] = 1;
		rep (i, 1, n)
		{
			C[i][0] = 1;
			rep (j, 1, n)
				(C[i][j] = C[i - 1][j - 1] + C[i - 1][j]) >= mo ? C[i][j] -= mo : 0;
		}

		rep (i, 0, n - 1)
			dfs_1(i, n);

		if (n >= 2 * K)
			return solve_1(K);
		else
			return solve_2(K);
    }
};
