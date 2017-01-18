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

class NewArenaPassword 
{
	public:
		int minChange(string s, int K) 
		{
			int n = SZ(s);
			if (K == n) return 0;
			int ret = n;
			int step = n - K;
			REP(i, 0, step)
			{
				static int cnt[26];
				memset(cnt, 0, sizeof cnt);
				int u = i;
				while (u < n)
				{
					++cnt[s[u] - 'a'];
					u += step;
				}
				ret -= *max_element(cnt, cnt + 26);
			}
			return ret;
		}
};

// Powered by Greed 2.0-RC
