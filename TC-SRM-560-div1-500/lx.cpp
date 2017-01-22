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

const int N = 312;
const int M = 75;

class DrawingPointsDivOne
{
public : 
	int w[N][N];

	int maxSteps(vector<int> x, vector<int> y)
	{
		int l = 1, r = 150;
		while (l <= r)
		{
			int mid = (l + r) >> 1;

			memset(w, 0, sizeof(w));

			rep (i, 0, x.size() - 1)
				w[x[i] + M][y[i] + M] = 1;

			rep (x, 1, 310) rep (y, 1, 310)
			{
				int c = mid + 1;
				if (w[x - 1][y] > 0)
					c = min(c, w[x - 1][y]);
				if (w[x][y - 1] > 0)
					c = min(c, w[x][y - 1]);
				if (w[x - 1][y - 1] > 0)
					c = min(c, w[x - 1][y - 1]);
				if (!w[x][y] && c < mid)
					w[x][y] = c + 1;
			}

			int cnt = 0;

			down (x, 310, 1) down (y, 310, 1)
			{
				if (w[x][y] > 0)
					w[x][y] = 1 + min(w[x + 1][y], min(w[x][y + 1], w[x + 1][y + 1]));
				if (w[x][y] >= mid)
					++cnt;
			}

			cnt == x.size() ? l = mid + 1 : r = mid - 1;
		}

		return r <= 150 ? r - 1 : -1;
	}
};

