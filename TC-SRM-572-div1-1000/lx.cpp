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
typedef pair<int , int > pii;

class NextAndPrev
{
public : 
	int vis[305], to[305];

	int getMinimum(int costN, int costP, string from, string goal)
	{
		if (from == goal)
			return 0;
		int n = from.size();
		memset(vis, 0, sizeof(vis));
		rep (i, 0, n - 1)
			vis[goal[i]] = 1;
		if (count(vis + 'a', vis + 'z' + 1, 0) == 0)
			return -1;
		rep (i, 'a', 'z')
			to[i] = ' ';
		rep (i, 0, n - 1)
		{
			if (to[from[i]] == ' ')
				to[from[i]] = goal[i];
			else if (to[from[i]] != goal[i])
				return -1;
		}
		vector<pii> S;
		rep (i, 'a', 'z') 
		{
			if (to[i] != ' ')
				S.pb(mp(i - 'a', to[i] - 'a'));
		}
		int m = S.size();
		int ans = inf;
		rep (st, 0, m - 1)
		{
			bool flag = 1;
			rep (i, 0, m - 2) 
			{
				if (S[i].y > S[i + 1].y)
					flag = 0;
			}
			if (flag)
			{
				rep (shift, -1, 2)
				{
					rep (i, 0, m - 1)
						S[i].y += shift * 26;
					int i = 0, cur = 0;
					while (i < m)
					{
						int j = i;
						while (j < m && S[i].y == S[j].y)
							++j;
						int low = S[i].y, high = S[i].y;
						rep (k, i, j - 1)
						{
							upmin(low, S[k].x);
							upmax(high, S[k].x);
						}
						cur += (S[i].y - low) * costN;
						cur += (high - S[i].y) * costP;
						i = j;
					}
					upmin(ans, cur);
					rep (i, 0, m - 1)
						S[i].y -= shift * 26;
				}
			}
			pii u = mp(S[0].x + 26, S[0].y);
			rep (i, 1, m - 1)
				S[i - 1] = S[i];
			S[m - 1] = u;
		}
		return ans < inf ? ans : -1;
	}
};
