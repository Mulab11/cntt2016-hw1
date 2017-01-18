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

class TheDevice 
{
	public:
		int minimumAdditional(vector<string> a) 
		{
			int n = SZ(a), m = SZ(a[0]);
			int ret = 0;
			REP(i, 0, m)
			{
				int cnt[2] = {0};
				REP(j, 0, n) ++cnt[a[j][i] - '0'];
				chkmax(ret, max(0, 1 - cnt[0]) + max(0, 2 - cnt[1]));
			}
			return ret;
		}
};

// Powered by Greed 2.0-RC
