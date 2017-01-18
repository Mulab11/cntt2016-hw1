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

const int max0 = 1000100, max1 = 64;

class TheDivisionGame 
{
	public:
		long long countWinningIntervals(int L, int R) 
		{
			static int val[max0 + 5], res[max0 + 5];
			memset(val, 0, sizeof val);
			REP(i, 0, R - L + 1) res[i] = L + i;
			for (int i = 2; i <= max0; ++i)
			{
				int u = R / i * i;
				while (u >= L) 
				{
					int &tmp = res[u - L];
					while (!(tmp % i)) 
					{
						++val[u - L];
						tmp /= i;
					}
					u -= i;
				}
			}
			REP(i, 0, R - L + 1) if (res[i] > 1) ++val[i];
			static int cnt[max1 + 5];
			memset(cnt, 0, sizeof cnt);
			LL ret = (LL)(R - L + 1) * (R - L + 2) >> 1;
			int sum = 0;
			++cnt[sum];
			REP(i, 0, R - L + 1)
			{
				sum ^= val[i];
				ret -= cnt[sum];
				++cnt[sum];
			}
			return ret;
		}
};

// Powered by Greed 2.0-RC
