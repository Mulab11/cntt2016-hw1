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

class BinPacking 
{
	public:
		int minBins(vector<int> a) 
		{
			sort(ALL(a));
			int n = SZ(a);
			int ret = 0;
			static bool vis[maxn + 5];
			memset(vis, 0, sizeof vis);
			for (int i = n - 1; i >= 0 && a[i] > 100; --i) if (!vis[i])
			{
				for (int j = i - 1; j >= 0; --j) if (!vis[j] && a[j] + a[i] <= 300)
				{
					vis[j] = vis[i] = 1;
					++ret;
					break;
				}
			}
			int cnt = 0;
			REP(i, 0, n) if (!vis[i])
			{
				if (a[i] > 100) ++ret;
				else ++cnt;
			}
			ret += (cnt + 2) / 3;
			return ret;
		}
};

// Powered by Greed 2.0-RC
