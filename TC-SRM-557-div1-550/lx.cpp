#include <bits/stdc++.h>

#define rep(i, x, y) for (int i = (x), _ = (y); i <= _; ++i)
#define down(i, x, y) for (int i = (x), _ = (y); i >= _; --i)
#define LX_JUDGE

using namespace std;
typedef long long LL;

const int N = 63;

class Incubator
{
public :
	bool adj[N][N];
	bool vis[N];
	int match[N], n;
	
	bool Dfs(int x)
	{
		rep (y, 0, n - 1) 
		{
			if (adj[x][y] && !vis[y])
			{
				vis[y] = 1;
				if (match[y] == -1 || Dfs(match[y]))
				{
					match[y] = x;
					return 1;
				}
			}
		}
		return 0;
	}

	int maxMagicalGirls(vector<string> G)
	{
		n = G.size();
		memset(match, -1, sizeof(match));
		rep (i, 0, n - 1) rep (j, 0, n - 1)
			adj[i][j] = G[i][j] == 'Y';
		rep (k, 0, n - 1) rep (i, 0, n - 1) rep (j, 0, n - 1)
			adj[i][j] |= adj[i][k] && adj[k][j];
		int ans = n;
		rep (i, 0, n - 1)
		{
			memset(vis, 0, sizeof(vis));
			ans -= Dfs(i);
		}
		return ans;
	}
};
