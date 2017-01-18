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

class BigFatInteger 
{
	public:
		int minOperations(int A, int B) 
		{
			vector<int> all;
			for (int i = 2; i * i <= A; ++i)
			{
				if (!(A % i))
				{
					int cnt = 0;
					while (!(A % i)) A /= i, ++cnt;
					all.pb(cnt * B);
				}
			}
			if (A > 1) all.pb(B);
			int ret = 0;
			for (auto u : all)
			{
				int tmp = 0;
				while (u > 1) u = (u + 1) >> 1, ++tmp;
				chkmax(ret, tmp);
			}
			ret += SZ(all);
			return ret;
		}
};

// Powered by Greed 2.0-RC
