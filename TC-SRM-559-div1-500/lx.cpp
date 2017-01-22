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

const int N = 52;

class HatRack
{
public : 
	LL dp[N][N];
	vector<int> adj[N];
	int n;

	inline void addEdge(int x, int y)
	{
		adj[x].pb(y);
		adj[y].pb(x);
	}

	LL treeDp(int x, int fa, int ind)
	{
		if (ind > n)
			return 0;

		LL & ans = dp[x][ind - 1];

		if (ans >= 0)
			return ans;

		ans = 0;
		vector<int> ch;

		rep (i, 0, adj[x].size() - 1)
		{
			if (adj[x][i] != fa)
				ch.pb(adj[x][i]);
		}

		if (ch.size() > 2)
			return ans = 0;

		switch (ch.size())
		{
			case 0 :
				ans = (ind << 1) > n;
				break ;
			case 1 : 
				if ((ind << 1 | 1) <= n)
					ans = 0;
				else
					ans = treeDp(ch[0], x, ind << 1);
				break ;
			case 2 : 
				LL p, q;
				p = treeDp(ch[0], x, ind << 1);
				q = treeDp(ch[1], x, ind << 1 | 1);
				ans += p * q;
				p = treeDp(ch[1], x, ind << 1);
				q = treeDp(ch[0], x, ind << 1 | 1);
				ans += p * q;
				break ;
		}

		return ans;
	}
    
	LL countWays(vector<int> A1, vector<int> A2)
	{
		n = A1.size() + 1;

		rep (i, 0, n - 2)
			addEdge(A1[i], A2[i]);

		LL ans = 0;

		rep (i, 1, n)
		{
			memset(dp, -1, sizeof(dp));
			ans += treeDp(i, i, 1);
		}

		return ans;
	}
};

