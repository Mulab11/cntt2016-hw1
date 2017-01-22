#include <bits/stdc++.h>

#define rep(i, x, y) for (int i = (x), _ = (y); i <= _; ++i)
#define down(i, x, y) for (int i = (x), _ = (y); i >= _; --i)
#define LX_JUDGE

using namespace std;
typedef long long LL;

template<typename T> inline void upmax(T & x, T y) { x < y ? x = y : 0; }
template<typename T> inline void upmin(T & x, T y) { x > y ? x = y : 0; }

const int inf = 0x3f3f3f3f;
const int N = 53;

class Stamp
{
public:
	int getMinimumCost(string color, int Cost, int Push)
	{
		int n = color.size();
		static int f[N], a[N];

		rep (i, 0, n - 1)
		{
			switch (color[i])
			{
				case '*' : 
					a[i] = 7;
					break ;
				case 'R' : 
					a[i] = 1;
					break ;
				case 'G' : 
					a[i] = 2;
					break ;
				case 'B' : 
					a[i] = 4;
					break ;
			}
		}

		int ans = inf;

		rep (len, 1, n)
		{
			memset(f, inf, sizeof(f));
			f[0] = 0;
			rep (i, 0, n - 1)
			{
				if (f[i] == inf)
					continue ;
				int color = 7;
				rep (j, i, n - 1)
				{
					color &= a[j];
					if (!color)
						break ;
					int l = j - i + 1;
					if (l >= len)
						upmin(f[j + 1], f[i] + (l + len - 1) / len * Push);
				}
			}
			upmin(ans, f[n] + Cost * len);
		}

		return ans;
	}
};
