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
const int N = 233;

typedef bitset<233> mark;

struct point
{
	LL x, y;
	point() {}
	point(LL x, LL y) : x(x), y(y) {}

	inline point operator - (const point & b) const
	{
		return point(x - b.x, y - b.y);
	}
	inline friend LL cross(const point & a, const point & b)
	{
		return a.x * b.y - a.y * b.x;
	}
};

class CheckerFreeness
{
public : 
	inline void transform(vector<string> & A, vector<int> & a)
	{
		int x = 0;
		rep (i, 0, A.size() - 1)
		{
			rep (j, 0, A[i].size() - 1)
			{
				if (A[i][j] >= '0' && A[i][j] <= '9')
					x = x * 10 + A[i][j] - '0';
				else if (x)
				{
					a.pb(x);
					x = 0;
				}
			}
		}
		if (x)
			a.pb(x);
	}

	mark lef[N][N], rig[N][N];

	string isFree(vector<string> whiteX, vector<string> whiteY, vector<string> blackX, vector<string> blackY)
	{
		vector<int> wx, wy, bx, by;

		transform(whiteX, wx);
		transform(whiteY, wy);
		transform(blackX, bx);
		transform(blackY, by);

		vector<point> w, b;

		int n = wx.size();
		int m = bx.size();

		rep (i, 0, n - 1)
			w.pb(point(wx[i], wy[i]));
		rep (i, 0, m - 1)
			b.pb(point(bx[i], by[i]));

		rep (i, 0, n - 1) rep (j, 0, m - 1)
		{
			rep (k, 0, n - 1) 
			{
				if (i != k)
				{
					if (cross(b[j] - w[i], w[k] - w[i]) > 0)
						lef[i][j][k] = 1;
					else 
						rig[i][j][k] = 1;
				}
			}
		}

		rep (i, 0, m - 1) rep (j, i + 1, m - 1)
		{
			static mark now;
			now.reset();
			rep (k, 0, n - 1) 
			{
				if (cross(w[k] - b[i], b[j] - b[i]) < 0)
					now[k] = 1;
			}
			rep (k, 0, n - 1)
			{
				if (cross(w[k] - b[i], b[j] - b[i]) > 0)
				{
					if ((now & rig[k][i] & lef[k][j]).count())
						return "NO";
				}
			}
		}

		return "YES";
	}
};
