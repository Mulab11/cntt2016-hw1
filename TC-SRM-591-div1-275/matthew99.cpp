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

class TheTree 
{
	public:
		int maximumDiameter(vector<int> cnt) 
		{
			int n = SZ(cnt);
			int ret = 0;
			REP(i, 0, n + 1) REP(j, i, n + 1) REP(k, i, n + 1)
			{
				vector<int> tmp(cnt);
				bool failed = 0;
				REP(l, i + 1, j + 1) if (--tmp[l - 1] < 0) failed = 1;
				REP(l, i + 1, k + 1) if (--tmp[l - 1] < 0) failed = 1;
				if (!failed) chkmax(ret, j + k - (i << 1));
			}
			return ret;
		}
};

// Powered by Greed 2.0-RC
