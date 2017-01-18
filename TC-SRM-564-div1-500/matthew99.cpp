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

const int maxn = 100010;

class AlternateColors2 
{
	public:
		long long countWays(int n, int k) 
		{
			LL ret = 0;
			for (int i = 1; i <= k; ++i)
			{
				int l = max(0, k - (i << 1) + 1), r = min(i - 1, k - i);
				if (l <= r) ret += r - l + 1;
				int res = k - i - (i - 1);
				if (res >= 0 && res < i) 
				{
					if (n - k - 1 >= 0) ret += (n - k) << 1;
				}
				if (res == i - 1)
				{
					if (n - k - 2 >= 0) ret += (LL)(n - k) * (n - k - 1) >> 1;
				}
			}
			return ret;
		}
};

// Powered by Greed 2.0-RC
