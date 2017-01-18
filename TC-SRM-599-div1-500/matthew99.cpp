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

class FindPolygons 
{
	public:
		double minimumPolygon(int L) 
		{
			if (L == 2 || (L & 1)) return -1;
			double ret = 1e100;
			vector<pair<pair<int, int>, int> > all;
			REP(i, 0, L + 1) REP(j, 0, L + 1) if (i || j)
			{
				if (i * i + j * j >= L * L) break;
				int tmp = sqrt(i * i + j * j) + .5;
				if (tmp * tmp == i * i + j * j) all.pb(mp(mp(i, j), tmp));
			}
			REP(i, 0, SZ(all)) REP(j, 0, i)
			{
				const auto &u = all[i], &v = all[j];
				if (u.y + v.y < L && u.x.x * v.x.y != u.x.y * v.x.x)
				{
					if ((L - u.y - v.y) * (L - u.y - v.y) == (u.x.x - v.x.x) * (u.x.x - v.x.x) + (u.x.y - v.x.y) * (u.x.y - v.x.y))
					{
						int res = L - u.y - v.y;
						chkmin(ret, (double)max({abs(u.y - v.y), abs(u.y - res), abs(v.y - res)}));
					}
				}
			}
			if (ret > L) 
			{
				if (!(L & 3)) return 0.0;
				return 1;
			}
			return ret;
		}
};

// Powered by Greed 2.0-RC
