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

class PyramidSequences 
{
	public:
		long long distinctPairs(int n, int m) 
		{
			int N = (n << 1) - 2, M = (m << 1) - 2;
			int d = __gcd(N, M);
			int totm = M / d;
			int u = m / d, v = m % d;
			int a = n / d, b = n % d;
			LL ret = 0;
			int w[] = {0, 1, v, b, d >> 1, (d >> 1) + 1, d};
			sort(w, w + 7);
			REP(i, 0, 6) if (w[i] != w[i + 1])
			{
				int numu = u + (w[i] < v);
				int numv = a + (w[i] < b);
				ret += (LL)numu * numv * (w[i + 1] - w[i]);
				if (w[i] != (d - w[i]) % d) ret += (LL)(totm - numu) * numv * (w[i + 1] - w[i]);
			}
			return ret;
		}
};

// Powered by Greed 2.0-RC
