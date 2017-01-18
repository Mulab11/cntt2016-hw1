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

LL K;

inline char get_sta(LL x, LL y)
{
	if ((x ^ y) & 1) return '.';
	LL u = (x + y) >> 1, v = (x - y) >> 1;
	if (u >= K || v < 0 || v > u || (v & u) != v) return '.';
	return u & 1 ? 'B' : 'A';
}

class CheckerExpansion 
{
	public:
		vector<string> resultAfter(long long t, long long x0, long long y0, int w, int h) 
		{
			K = t;
			vector<string> ret;
			for (int i = h - 1; i >= 0; --i)
			{
				string tmp;
				REP(j, 0, w) tmp.pb(get_sta(x0 + j, y0 + i));
				ret.pb(tmp);
			}
			return ret;
		}
};

// Powered by Greed 2.0-RC
