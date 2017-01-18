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

class IncrementAndDoubling 
{
	public:
		int getMin(vector<int> a) 
		{
			int n = SZ(a);
			int ret = 0;
			bool flag = 0;
			for (int i = 9; i >= 0; --i)
			{
				int cnt = 0;
				REP(j, 0, n) if (a[j] >> i & 1) ++cnt;
				ret += cnt + flag;
				if (cnt) flag = 1;
			}
			return ret;
		}
};

// Powered by Greed 2.0-RC
