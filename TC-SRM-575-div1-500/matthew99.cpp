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

const int maxn = 2500;
const int maxk = 1000000;

int n;

class TheSwapsDivOne 
{
	public:
		double find(vector<string> _a, int K) 
		{
			string a = accumulate(ALL(_a), string());
			n = SZ(a);
			static double cnt[maxn + 5];
			int tot = n * (n + 1) >> 1;
			memset(cnt, 0, sizeof cnt);
			REP(i, 0, n) cnt[i] = double(i + 1) * (n - i) / tot;
			double ret = 0;
			double u = 1;
			REP(i, 0, K) u = u * (1 - 2. / n) + (1 - u) / (n * (n - 1) >> 1);
			REP(i, 0, n) REP(j, 0, n) ret += (i == j ? u: (1 - u) / (n - 1)) * cnt[j] * (a[i] - '0');
			return ret;
		}
};

// Powered by Greed 2.0-RC
