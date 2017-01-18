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

const int maxn = 60;

int n, m;
vector<pair<int, LL> > b;

class SpaceWarDiv1 
{
	public:
		long long minimalFatigue(vector<int> a, vector<int> _b, vector<long long> _c) 
		{
			n = SZ(a);
			m = SZ(_b);
			b.clear();
			REP(i, 0, m) b.pb(mp(_b[i], _c[i])); 
			sort(ALL(a)), sort(ALL(b));
			LL l = 0, r = 1e18;
			while (l < r)
			{
				LL mid = (l + r) >> 1;
				int j = 0;
				LL cnt = b[0].y;
				REP(i, 0, n)
				{
					LL res = mid;
					while (j < m && b[j].x <= a[i]) 
					{
						if (cnt > res) { cnt -= res; break; }
						res -= cnt;
						++j;
						if (j < m) cnt = b[j].y;
					}
				}
				if (j == m) r = mid;
				else l = mid + 1;
			}
			if (r == 1e18) return -1;
			return l;
		}
};

// Powered by Greed 2.0-RC
