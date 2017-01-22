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

typedef long double LD;

class CandyOnDisk
{
public : 
	int root[55];
	int x[55], y[55], r[55], n;
	LD dis[55][55];
	bool vis[55], del[55][55];
	LD low[55], high[55];

	bool inter(LD l, LD r, LD x, LD y)
	{
		return !(l > y || x > r);
	}
	inline LD vecLen(LD x, LD y)
	{
		return sqrt(x * x + y * y);
	}

	bool check(int sx, int sy, int tx, int ty)
	{
		if (sx == tx && sy == ty)
			return 1;
		rep (i, 0, n - 1) rep (j, i + 1, n - 1)
			dis[i][j] = dis[j][i] = vecLen(x[i] - x[j], y[i] - y[j]);
		rep (i, 0, n - 1)
		{
			LD tmp = vecLen(x[i] - sx, y[i] - sy);
			if (tmp < r[i])
			{
				vis[i] = 1;
				low[i] = high[i] = tmp;
			}
			else 
			{
				low[i] = 1e10;
				high[i] = -1e10;
			}
		}
		bool flag = 1;
		while (flag)
		{
			flag = 0;
			rep (i, 0, n - 1) if (vis[i])
			{
				rep (j, 0, n - 1) if (j != i)
				{
					LD mx = max(dis[i][j] - r[j], (LD)0.0);
					if (!del[i][j] && inter(low[i], high[i], mx, dis[i][j] + r[j]))
					{
						del[j][i] = del[i][j] = vis[j] = flag = 1;
						upmin(low[i], max(dis[i][j] - r[j], (LD)0));
						upmax(high[i], min(dis[i][j] + r[j], LD(r[i])));
						upmin(low[j], max(dis[i][j] - r[i], (LD)0));
						upmax(high[j], min(dis[i][j] + r[i], LD(r[j])));
					}
				}
			}
		}
		rep (i, 0, n - 1) if (vis[i])
		{
			LD t = vecLen(x[i] - tx, y[i] - ty);
			if (vis[i] && t >= low[i] && t <= high[i]) {
				printf("%d\n", i);
				return 1;
			}
		}
		return 0;
	}

	//Bellman-ford 算法
	//计算几何
	string ableToAchieve(vector<int> x, vector<int> y, vector<int> r, int sx, int sy, int tx, int ty)
	{
		n = 0;
		rep (i, 0, x.size() - 1)
		{
			int j = 0;
			for ( ; j < i; ++j)
			{
				if (x[i] == x[j] && y[i] == y[j])
					break ;
			}
			if (j == i)
				root[i] = n++;
			else
				root[i] = root[j];
			this->x[root[i]] = x[i];
			this->y[root[i]] = y[i];
			upmax(this->r[root[i]], r[i]);
		}
		bool ans = check(sx, sy, tx, ty);
		return ans ? "YES" : "NO";
	}
};
