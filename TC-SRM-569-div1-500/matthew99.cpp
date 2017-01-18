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

class TheJediTest 
{
	public:
		int minimumSupervisors(vector<int> a, int K) 
		{
			int n = SZ(a);
			int ret = 0;
			int lst = 0;
			REP(i, 0, n)
			{
				ret += (a[i] + lst) / K;
				int tmp = (a[i] + lst) % K;
				if (i + 1 >= n) 
				{
					ret += !!tmp;
					continue;
				}
				if (a[i] >= tmp) lst = tmp;
				else
				{
					chkmax(a[i + 1] -= (K - tmp), 0);
					++ret;
					lst = 0;
				}
			}
			return ret;
		}
};

// Powered by Greed 2.0-RC
