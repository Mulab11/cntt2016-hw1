#include <bits/stdc++.h>

#define rep(i, x, y) for (int i = (x), _ = (y); i <= _; ++i)
#define down(i, x, y) for (int i = (x), _ = (y); i >= _; --i)
#define LX_JUDGE

using namespace std;
typedef long long LL;

template<typename T> inline void upmax(T & x, T y) { x < y ? x = y : 0; }
template<typename T> inline void upmin(T & x, T y) { x > y ? x = y : 0; }

const int N = 1e5 + 10;

class AlternateColors2
{
public : 
	LL f[N][8][3];
	int col[3];

	LL countWays(int n, int k)
	{
		down (i, n, 0)
		{
			rep (s, 1, 8)
			{
				int t = 0;
				rep (j, 0, 2)
				{
					if ((s >> j) & 1)
						col[t++] = j;
				}
				rep (p, 0, t - 1)
				{
					LL ans = 0;
					if (i == n)
						ans = 1;
					else
					{
						if ((k - 1) != i || (col[p] == 0))
							ans += f[i + 1][s][(p + 1) % t];
						if (t > 1)
						{
							int ns = s ^ (1 << (col[p]));
							int np = p == t - 1 ? 0 : p;
							ans += f[i][ns][np];
						}
					}
					f[i][s][p] = ans;
				}
			}
		}
		return f[0][7][0];
	}
}; 

