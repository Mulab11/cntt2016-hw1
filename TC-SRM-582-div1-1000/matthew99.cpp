#line 5 "SemiPerfectPower.cpp"
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

inline int rt2(const LL &x) { int tmp = sqrt(x) + 2; while ((LL)tmp * tmp > x) --tmp; return tmp; }
inline int rt3(const LL &x) { int tmp = pow(x, 1. / 3) + 2; while ((LL)tmp * tmp * tmp > x) --tmp; return tmp; }

const int max0 = 1000000, max1 = 30000;

int mu[max0 + 5];
bool ok[max1 + 5];
int fir[max1 + 5];
vector<int> sum[max1 + 5];

inline void prepare()
{
	memset(mu, 0, sizeof mu);
	mu[1] = 1;
	for (int i = 1; i <= max0; ++i) for (int j = i << 1; j <= max0; j += i) mu[j] -= mu[i];
	fir[1] = 1;
	for (int i = max1; i >= 2; --i) for (int j = i; j <= max1; j += i) fir[j] = i;
	memset(ok, 1, sizeof ok);
	for (int i = 2; i * i * i <= max1; ++i) if (fir[i] == i) for (int t = i * i * i; t <= max1; t += i * i * i) ok[t] = 0;
	for (int i = 1; i <= max1; ++i) if (mu[i])
	{
		sum[i].clear();
		sum[i].resize(max0 / i + 5);
		sum[i][0] = 0;
		for (int j = 1; i * j <= max0; ++j) sum[i][j] = sum[i][j - 1] + (!!mu[i * j]);
	}
}

LL work(const LL &x)
{
	LL ret = 0;
	for (int a = 1; (LL)a * a * a < x; ++a) if (mu[a]) ret += rt2(x / a) - a;
	for (int a = 1; (LL)a * a * a * a < x; ++a) if (ok[a]) for (int b = 1; b * b * b <= a; ++b)
	{
		int foo = __gcd(b * b, a), bar = a / foo;
		if (!mu[bar]) continue;
		int baz = b * b / foo, l = a / baz, r = rt3(x / a) / baz;
		vector<int> a;
		a.pb(1);
		int u = bar;
		while (u > 1)
		{
			int tmp = fir[u];
			REP(i, 0, SZ(a)) a.pb(a[i] * tmp);
			u /= tmp;
		}
		for (auto u : a) ret += (LL)mu[u] * (sum[u][r / u] - sum[u][l / u]);
	}
	return ret;
}

class SemiPerfectPower
{
	public:
		long long count(long long L, long long R)
		{
			prepare();
			return work(R) - work(L - 1);
		}
		

};



// Powered by FileEdit
// Powered by TZTester 1.01 [25-Feb-2003]
// Powered by CodeProcessor
