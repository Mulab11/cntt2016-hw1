#include <bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for (int i = (a), i##_end_ = (b); i < i##_end_; ++i)
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define mp make_pair
#define x first
#define y second
#define pb push_back
#define SZ(x) (int((x).size()))
#define ALL(x) (x).begin(), (x).end()

template<typename T> inline bool chkmin(T &a, const T &b) { return a > b ? a = b, 1 : 0; }
template<typename T> inline bool chkmax(T &a, const T &b) { return a < b ? a = b, 1 : 0; }

typedef long long LL;

const int oo = 0x3f3f3f3f;

vector<pair<int, int> > all;

inline bool add(int x, int y)
{
	if (SZ(all) >= 2 && (LL)(x - all[0].x) * (y - all[1].y) != (LL)(x - all[1].x) * (y - all[0].y)) return 1;
	all.pb(mp(x, y));
	return 0;
}

inline LL ceil(LL a, LL b);
inline LL floor(LL a, LL b);

inline LL ceil(LL a, LL b)
{
	if (b < 0) a = -a, b = -b;
	if (a < 0) return -floor(-a, b);
	return (a + b - 1) / b;
}

inline LL floor(LL a, LL b)
{
	if (b < 0) a = -a, b = -b;
	if (a < 0) return -ceil(-a, b);
	return a / b;
}


class ConvexPolygonGame 
{
	public:
		string winner(vector<int> x, vector<int> y) 
		{
			all.clear();
			int n = SZ(x);
			REP(i, -100000, 100001)
			{
				int l = -100001, r = 100000;
				REP(j, 0, n)
				{
					int nxt = (j + 1) % n;
					if (x[j] != x[nxt] && LL(x[j] - i) * (x[nxt] - i) <= 0)
					{
						if (x[j] < x[nxt])
						{
							if (x[j] == i) chkmax(l, y[j] + 1);
							else if (x[nxt] == i) chkmax(l, y[nxt] + 1);
							else chkmax(l, (int)ceil((LL)(i - x[j]) * y[nxt] + (LL)(x[nxt] - i) * y[j], x[nxt] - x[j]));
						}
						else
						{
							if (x[j] == i) chkmin(r, y[j] - 1);
							else if (x[nxt] == i) chkmin(r, y[nxt] - 1);
							else chkmin(r, (int)floor((LL)(i - x[j]) * y[nxt] + (LL)(x[nxt] - i) * y[j], x[nxt] - x[j]));
						}
					}
				}
				if (l >= - 100000) REP(k, l, r + 1) if (add(i, k)) return "Masha";
			}
			return "Petya";
		}
};

// Powered by Greed 2.0-RC
