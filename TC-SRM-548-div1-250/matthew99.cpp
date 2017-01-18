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

const int maxabs = 1.01e9;

const int maxn = 54;

int n;
int a[maxn + 5];

inline bool check(int x)
{
	int now = 1;
	REP(i, 0, n)
	{
		if (now > a[i] + x) return 0;
		chkmax(now, a[i] - x);
		++now;
	}
	return 1;
}

class KingdomAndTrees 
{
	public:
		int minLevel(vector<int> heights) 
		{
			n = SZ(heights);
			REP(i, 0, n) a[i] = heights[i];
			int l = 0, r = maxabs;
			while (l < r)
			{
				int mid = (l + r) >> 1;
				if (check(mid)) r = mid;
				else l = mid + 1;
			}
			return l;
		}
};

// Powered by Greed 2.0-RC
