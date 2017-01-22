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

typedef pair<int, int > pii;

class XorTravelingSalesman
{
public : 
	bool vis[N][1111];

	int maxProfit(vector<int> val, vector<string> G)
	{
		int n = val.size();
		int ans = 0;

		queue<pii> Q;

		vis[0][val[0]] = 1;
		Q.push(mp(0, val[0]));

		while (!Q.empty())
		{
			pii u = Q.front();
			Q.pop();
			upmax(ans, u.y);
			rep (i, 0, n - 1) 
			{
				if (G[u.x][i] == 'Y')
				{
					pii v = mp(i, u.y ^ val[i]);
					if (!vis[v.x][v.y])
					{
						vis[v.x][v.y] = 1;
						Q.push(v);
					}
				}
			}
		}

		return ans;
	}
};
