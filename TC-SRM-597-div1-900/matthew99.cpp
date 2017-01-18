#line 5 "LittleElephantAndBoard.cpp"
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

const int maxn = 2100000;

int fac[maxn + 5], ifac[maxn + 5];

inline int fpm(LL b, int e, int m)
{
	b %= m;
	LL t = 1;
	for ( ; e; e >>= 1, (b *= b) %= m)
		if (e & 1) (t *= b) %= m;
	return t;
}

inline void prepare()
{
	fac[0] = 1;
	REP(i, 0, maxn) fac[i + 1] = (LL)fac[i] * (i + 1) % Mod;
	ifac[maxn] = fpm(fac[maxn], Mod - 2, Mod);
	for (int i = maxn - 1; i >= 0; --i) ifac[i] = (LL)ifac[i + 1] * (i + 1) % Mod;
}

inline int C(int x, int y) { if (y < 0 || y > x) return 0; return (LL)fac[x] * ifac[y] % Mod * ifac[x - y] % Mod; }

class LittleElephantAndBoard
{
	public:
		int getNumber(int M, int R, int G, int B)
		{
			prepare();
			int a[3] = {M - R, M - G, M - B};
			REP(i, 0, 3) if (a[i] < 0) return 0;
			sort(a, a + 3, greater<int>());
			int ret = 0;
			REP(i, 0, a[0]) REP(j, 0, 3)
			{
				int res = a[1] - i - j;
				if (res < 0) break;
				int tmp = (LL)C(a[0] - 1, i) % Mod * C(2, j) % Mod * C(res + i + j - 1, res) % Mod;
				int must = a[0] + a[1] - 1 - ((i << 1) + j);
				if (must > a[2]) continue;
				tmp = (LL)tmp * C(a[0] + a[1] + 1 - must, a[2] - must) % Mod;
				(ret += tmp) %= Mod;
			}
			(ret <<= 1) %= Mod;
			(ret += Mod) %= Mod;
			return ret;
		}
		

};



// Powered by FileEdit
// Powered by TZTester 1.01 [25-Feb-2003]
// Powered by CodeProcessor
