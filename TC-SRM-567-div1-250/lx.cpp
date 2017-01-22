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

class TheSquareRootDilemma
{
public:
	int vis[77785];

	int countPairs(int n, int m)
	{
		rep (i, 1, sqrt(n))
		{
			int step = i * i;
			for (int j = step, c = 1; j <= n; j += step, ++c)
				vis[j] = c;
		}
		int ans = 0;
		rep (i, 1, n)
			ans += sqrt(m / vis[i]);
		return ans;
	}
};
