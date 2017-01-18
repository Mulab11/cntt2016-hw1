#line 5 "MegaFactorial.cpp"
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

const int Mod = 1e9 + 9;

inline int fpm(LL b, int e, int m)
{
	b %= m;
	LL t = 1;
	for ( ; e; e >>= 1, (b *= b) %= m)
		if (e & 1) (t *= b) %= m;
	return t;
}

const int maxk = 16, max0 = 100;

int fac[maxk + 5];
int ifac[maxk + 5];

int tot[maxk + 5];

inline void prepare(int Mod)
{
	fac[0] = ifac[0] = 1;
	tot[0] = 0;
	REP(i, 0, maxk) 
	{
		int u = i + 1;
		int v = 0;
		while (!(u % Mod)) u /= Mod, ++v;
		tot[i + 1] = tot[i] + v;
		fac[i + 1] = (LL)u * fac[i] % Mod;
		ifac[i + 1] = fpm(fac[i + 1], Mod - 2, Mod);
	}
}

inline int calc(int a, int b, int cnt, int K, int Mod)
{
	if (cnt <= max0)
	{
		int ret = 0;
		REP(i, 0, cnt)
		{
			int x = a + b * i + K - 1;
			int tmp = ifac[K - 1];
			int pw = -tot[K - 1];
			REP(j, 0, K - 1) 
			{
				int u = x - j;
				while (!(u % Mod)) ++pw, u /= Mod;
				tmp = (LL)tmp * u % Mod;
			}
			assert(pw >= 0);
			if (!pw) (ret += tmp) %= Mod;
		}
		return ret;
	}
	static int val[maxk + 5], dif[maxk + 5];
	memset(val, 0, sizeof val);
	memset(dif, 0, sizeof dif);
	val[0] = 0;
	REP(i, 0, K + 1)
	{
		int x = a + b * i + K - 1;
		int tmp = ifac[K - 1];
		int pw = -tot[K - 1];
		REP(j, 0, K - 1) 
		{
			int u = x - j;
			while (!(u % Mod)) ++pw, u /= Mod;
			tmp = (LL)tmp * u % Mod;
		}
		assert(pw >= 0);
		if (pw) tmp = 0;
		val[i + 1] = (val[i] + tmp) % Mod;
	}
	REP(i, 0, K + 1)
	{
		dif[i] = val[0];
		REP(j, 0, K + 1 - i - 1) val[j] = (val[j + 1] - val[j]) % Mod;
	}
	int ret = 0;
	REP(i, 0, K + 1)
	{
		int pw = -tot[i];
		int tmp = (LL)dif[i] * ifac[i] % Mod;
		REP(j, 0, i) 
		{
			int u = cnt - j;
			while (!(u % Mod)) ++pw, u /= Mod;
			tmp = (LL)tmp * u % Mod;
		}
		assert(pw >= 0);
		if (!pw) (ret += tmp) %= Mod;
	}
	return ret;
}

inline int work(int N, int K, int base, int Mod)
{
	prepare(Mod);
	int ret = 0;
	LL u = base;
	while (u <= N)
	{
		int tmp = N % u;
		(ret += calc(tmp, u, N / u, K, Mod)) %= Mod;
		u *= base;
	}
	return ret;
}

class MegaFactorial
{
	public:
		int countTrailingZeros(int N, int K, int B)
		{
			int ans;
			if (B == 10) ans = work(N, K, 5, Mod);
			else if (B == 6) ans = work(N, K, 3, Mod);
			else if (B == 2) ans = work(N, K, 2, Mod);
			else if (B == 3) ans = work(N, K, 3, Mod);
			else if (B == 5) ans = work(N, K, 5, Mod);
			else if (B == 7) ans = work(N, K, 7, Mod);
			else if (B == 9) ans = LL(work(N, K, 3, Mod) - work(N, K, 3, 2)) * ((Mod + 1) >> 1) % Mod;
			else if (B == 4) ans = LL(work(N, K, 2, Mod) - work(N, K, 2, 2)) * ((Mod + 1) >> 1) % Mod;
			else if (B == 8) ans = LL(work(N, K, 2, Mod) - work(N, K, 2, 3)) * fpm(3, Mod - 2, Mod) % Mod;
			else assert(0);
			(ans += Mod) %= Mod;
			return ans;
		}


};



// Powered by FileEdit
// Powered by TZTester 1.01 [25-Feb-2003]
// Powered by CodeProcessor
