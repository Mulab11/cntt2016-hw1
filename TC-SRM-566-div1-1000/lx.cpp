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

const double pi = acos(-1);
const int mo = 100007;
const int N = 241;

class FencingPenguins
{
public:
	inline void upd(int & x, int y)
	{
		(x += y) >= mo ? x -= mo : 0;
	}

	inline int onLeft(double x1, double y1, double x2, double y2, double x3, double y3)
	{
		x1 -= x3, y1 -= y3;
		x2 -= x3, y2 -= y3;
		double t = x1 * y2 - x2 * y1;
		return t < 0 ? -1 : t > 0;
	}

	int countWays(int len, int R, vector<int> x, vector<int> y, string str)
	{
		static double px[N], py[N];

		rep (i, 0, len - 1)
		{
			double a = pi * 2 * i / len;
			px[i] = R * cos(a);
			py[i] = R * sin(a);
		}

		static int col[N];

		int n = x.size();
		int cn = 1;

		col[0] = 0;

		rep (i, 1, n - 1)
		{
			col[i] = -1;
			rep (j, 0, i - 1)
			{
				if (str[i] == str[j])
				{
					col[i] = col[j];
					break ;
				}
			}
			if (col[i] < 0)
				col[i] = cn++;
		}

		static LL mask[N][N], cmask[N][N];
		static bool can[N][N];

		rep (i, 0, len - 1) 
		{
			rep (j, 0, len - 1)
			{
				mask[i][j] = 0;
				cmask[i][j] = 0;
				rep (k, 0, n - 1)
				{
					if (onLeft(px[i], py[i], px[j], py[j], x[k], y[k]) == 1)
					{
						mask[i][j] |= 1ll << k;
						cmask[i][j] |= 1ll << col[k];
					}
				}
			}
		}

		if (mask[0][len - 1] != 0)
			return 0;

		rep (i, 0, len - 1) rep (j, 0, len - 1)
			can[i][j] = ((cmask[i][j] & cmask[j][i]) == 0);
		
		static int h[N][N][2], g[N][N], f[N][N];
		
		rep (i, 0, len - 1)
			h[i][i][1] = 1;

		rep (w, 1, len - 1)
		{
			rep (l, 0, len - w - 1)
			{
				int r = l + w;
				int ans = 0;

				rep (i, 0, 1)
				{
					ans = 0;
					rep (nl, l + 1, r)
					{
						if (can[l][nl])
						{
							LL inter = mask[l][nl] & mask[nl][r] & mask[r][l];
							int ni = (inter != 0) ? 1 : i;
							if (mask[nl][l] == 0)
								upd(ans, h[nl][r][ni]);
							else if (nl - l >= 4)
							{
								if ((mask[nl][l] & mask[l + 1][nl - 1]) == 0)
									upd(ans, (LL) h[nl][r][ni] * f[l + 1][nl - 1] % mo);
							}
						}
					}
					h[l][r][i] = ans;
				}

				ans = 0;
				down (nr, r, l + 2)
				{
					if (can[l][nr])
					{
						LL inter = mask[r][l] & mask[l][nr];
						if (inter == 0)
							upd(ans, h[l][nr][0]);
						else if (nr + 2 < r)
						{
							inter &= mask[nr + 1][r];
							if (inter == 0)
								upd(ans, (LL) h[l][nr][0] * f[nr + 1][r] % mo);
						}
					}
				}
				g[l][r] = ans;

				ans = 0;
				rep (nl, l, r - 1)
				{
					LL inter = mask[r][l] & mask[nl][r];
					if (inter == 0)
						upd(ans, g[nl][r]);
				}

				f[l][r] = ans;
			}
		}

		return f[0][len - 1];
	}
};
