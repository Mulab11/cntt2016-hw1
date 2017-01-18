#line 5 "WolfPack.cpp"
#include <bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for (int i = (a), _end_ = (b); i < _end_; ++i)
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

const int Mod = 1e9 + 7;

inline int fpm(LL b, int e, int m)
{
	b %= m;
	LL t = 1;
	for ( ; e; e >>= 1, (b *= b) %= m)
		if (e & 1) (t *= b) %= m;
	return t;
}

const int maxn = 50, maxm = 100000;

int n, m;

int a[maxn + 5], b[maxn + 5];

int C[maxm + 5];

inline int work(int *a)
{
	int Min = *min_element(a, a + n), Max = *max_element(a, a + n);
	int ret = 0;
	REP(i, Max - m, Min + m + 1)
		if (!((i ^ Min ^ m) & 1))
		{
			int tmp = 1;
			REP(j, 0, n) tmp = (LL)tmp * C[(m + a[j] - i) >> 1] % Mod;
			(ret += tmp) %= Mod;
		}
	return ret;
}

class WolfPack
{
	public:
		int calc(vector <int> x, vector <int> y, int m)
		{
			n = SZ(x);
			::m = m;
			C[0] = 1;
			REP(i, 0, m) C[i + 1] = (LL)C[i] * (m - i) % Mod * fpm(i + 1, Mod - 2, Mod) % Mod;
			REP(i, 1, n) if ((x[i] ^ y[i] ^ x[0] ^ y[0]) & 1) return 0;
			REP(i, 0, n) a[i] = x[i] - y[i], b[i] = x[i] + y[i];
			return (LL)work(a) * work(b) % Mod;
		}


};



// Powered by FileEdit
// Powered by TZTester 1.01 [25-Feb-2003]
// Powered by CodeProcessor
