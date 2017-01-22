#include <bits/stdc++.h>

#define rep(i, x, y) for (int i = (x), _ = (y); i <= _; ++i)
#define down(i, x, y) for (int i = (x), _ = (y); i >= _; --i)
#define x first
#define y second
#define LX_JUDGE

using namespace std;
typedef long long LL;

template<typename T> inline void upmax(T & x, T y) { x < y ? x = y : 0; }
template<typename T> inline void upmin(T & x, T y) { x > y ? x = y : 0; }

class StringGame
{
public:
	int n, m;
	int count[52][26];
	bool vis[26], del[52];

	vector<int> getWinningStrings(vector<string> S)
	{
		n = S.size();
		m = S[0].size();

		memset(count, 0, sizeof(count));

		rep (i, 0, n - 1)
		{
			rep (j, 0, m - 1)
				count[i][S[i][j] - 'a']++;
		}

		vector<int> ans;

		rep (i, 0, n - 1)
		{
			memset(vis, 0, sizeof(vis));
			memset(del, 0, sizeof(del));
			del[i] = 1;
			int cnt = n - 1;
			rep (j, 0, 25)
			{
				int opt = -1;
				rep (a, 0, 25) if (!vis[a])
				{
					int k = 0;
					for ( ; k < n; ++k) 
					{
						if (!del[k] && count[k][a] > count[i][a])
							break ;
					}
					if (k == n)
					{
						opt = a;
						break ;
					}
				}
				if (opt != -1)
				{
					vis[opt] = 1;
					rep (k, 0, n - 1) 
					{
						if (!del[k] && count[k][opt] < count[i][opt])
						{
							del[k] = 1;
							cnt--;
						}
					}
				}
				else
					break ;
			}
			if (!cnt)
				ans.push_back(i);
		}

		return ans;
	}
};
