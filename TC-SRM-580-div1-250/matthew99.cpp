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

class EelAndRabbit 
{
	public:
		int getmax(vector<int> l, vector<int> t) 
		{
			vector<pair<int, int> > all;
			int n = SZ(l);
			REP(i, 0, n) all.pb(mp(t[i], t[i] + l[i]));
			int ret = 0;
			REP(i, 0, n) REP(j, 0, i + 1)
			{
				int tmp = 0;
				REP(k, 0, n) if ((all[k].x <= all[i].x && all[k].y >= all[i].x) || (all[k].x <= all[j].x && all[k].y >= all[j].x)) ++tmp;
				chkmax(ret, tmp);
			}
			return ret;
		}
};

// Powered by Greed 2.0-RC
