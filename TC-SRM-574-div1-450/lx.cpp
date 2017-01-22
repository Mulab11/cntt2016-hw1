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

class PolygonTraversal
{
public : 
	vector<int> points;
	int bin[33];
	LL dp[1 << 18 | 1][18];
	int n;

	bool inter(int mask, int a, int b)
	{
		if (a > b)
			swap(a, b);
		int p = (bin[b - a - 1] - 1) << (a + 1);
		int q = (bin[n] - 1) - p - bin[a] - bin[b];
		return (mask & p) && (mask & q);
	}

	LL calc(int mask, int now)
	{
		LL & ans = dp[mask][now];
		if (ans == -1)
		{
			if (mask == bin[n] - 1)
				ans = inter(mask, now, points[0]);
			else
			{
				ans = 0;
				rep (i, 0, n - 1)
				{
					if (!(mask & bin[i]) && inter(mask, now, i))
						ans += calc(mask | bin[i], i);
				}
			}
		}
		return ans;
	}

	LL count(int n, vector<int> points)
	{
		bin[0] = 1;
		rep (i, 1, 31)
			bin[i] = bin[i - 1] << 1;
		memset(dp, -1, sizeof(dp));
		int mask = 0;
		rep (i, 0, points.size() - 1)
		{
			points[i] -= 1;
			mask |= bin[points[i]];
		}
		this->n = n;
		this->points = points;
		return calc(mask, points[points.size() - 1]);
	}
};
