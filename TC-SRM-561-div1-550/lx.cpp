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
const int N = 53;

struct circle
{
	int x, y, r;
	circle(){}
	circle(int x, int y, int r) : x(x), y(y), r(r) {}
	inline bool operator < (const circle & b) const
	{
		return r > b.r;
	}
};

inline int sqr(int x)
{
	return x * x;
}

class CirclesGame
{
public : 
	vector<circle> p;
	vector<int> adj[N];
	int pa[N], dp[N], n;
	vector<int> g[N];

	inline bool in(int i, int j)
	{
		return sqr(p[i].x - p[j].x) + sqr(p[i].y - p[j].y) <= sqr(p[j].r - p[i].r);
	}

	void treeDp(int x)
	{
		int now = 0;

		rep (i, 0, adj[x].size() - 1)
		{
			int to = adj[x][i];
			treeDp(to);
			now ^= dp[to];
		}

		rep (i, 0, adj[x].size() - 1)
		{
			int to = adj[x][i];
			int v = now ^ dp[to];
			rep (j, 0, g[to].size() - 1)
				g[x].pb(g[to][j] ^ v);
		}
		
		g[x].pb(now);
		sort(g[x].begin(), g[x].end());
		g[x].erase(unique(g[x].begin(), g[x].end()), g[x].end());

		int cur = 0, i = 0;
		while (i < g[x].size() && g[x][i] == cur)
			++cur, ++i;

		dp[x] = cur;
	}

	string whoCanWin(vector<int> x, vector<int> y, vector<int> r)
	{
		n = x.size();
		rep (i, 0, n - 1)
			p.pb(circle(x[i], y[i], r[i]));

		sort(p.begin(), p.end());

		rep (i, 0, n - 1)
		{
			int j = i - 1;
			while (j >= 0 && !in(i, j))
				--j;
			pa[i] = j;
			if (j >= 0)
				adj[j].pb(i);
		}

		int ans = 0;

		rep (i, 0, n - 1) 
		{
			if (pa[i] == -1)
			{
				treeDp(i);
				ans ^= dp[i];
			}
		}

		return ans ? "Alice" : "Bob";
	}
};
