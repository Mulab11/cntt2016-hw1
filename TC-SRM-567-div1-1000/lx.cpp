#include <bits/stdc++.h>

#define rep(i, x, y) for (int i = (x), _ = (y); i <= _; ++i)
#define down(i, x, y) for (int i = (x), _ = (y); i >= _; --i)
#define x first
#define y second

using namespace std;
typedef long long LL;

template<typename T> inline void upmax(T & x, T y) { x < y ? x = y : 0; }
template<typename T> inline void upmin(T & x, T y) { x > y ? x = y : 0; }

const int mo = 1e9 + 9;

class Mountains
{
public : 
	map <string, int> G;
	int height[55], n, m;
	bool can[55][55];
	int tmph[55][55], tot, h[55];

	int search(int now)
	{
		if (now < 0)
			return 1;

		string state = to_string(now);
		rep (i, 0, m - 1)
			state += " " + to_string(h[i]);

		if (G.find(state) != G.end())
			return G[state];

		int ans = 0;

		rep (i, 0, m - 1)
		{
			int j = 0;
			for ( ; j < m; ++j) 
			{
				if ((can[now][j]) ^ (height[now] - abs(i - j) > h[j]))
					break ;
			}
			if (j == m)
			{
				memcpy(tmph[now], h, sizeof(h));
				for (j = 0; j < m; ++j)
					upmax(h[j], height[now] - abs(i - j));
				ans = (ans + search(now - 1)) % mo;
				memcpy(h, tmph[now], sizeof(h));
			}
		}

		return G[state] = ans;
	}
    
	int countPlacements(vector<int > heights, vector<string> vis)
	{
		n = heights.size();
		m = vis[0].size();

		rep (i, 0, n - 1)
			height[i] = heights[i];
		rep (i, 0, n - 1) rep (j, 0, m - 1)
			can[i][j] = vis[i][j] == 'X';

		int ans = search(n - 1);
		return ans;
	}
};
