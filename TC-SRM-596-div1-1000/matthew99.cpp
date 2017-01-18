#line 5 "SparseFactorial.cpp"
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

const int max0 = 1000000, max1 = 10;

LL L, R;
int d;
LL fir[max0 + 5];

inline void doit(int p, int cnt)
{
	int mo = 1;
	REP(i, 0, cnt) mo *= p;
	vector<LL> Min(mo);
	vector<int> tot(mo);
	vector<int> nxt(mo);
	Min[0] = 0, tot[0] = cnt;
	REP(i, 1, mo) 
	{
		int u = __gcd(i, mo);
		tot[i] = 0;
		while (u > 1) ++tot[i], u /= p;
		Min[i] = R;
	}
	REP(i, 0, mo) nxt[i] = i + p;
	for (LL i = 1; i * i <= R; ++i)
	{
		int tmp = i * i % mo, foo = tmp % p;
		for (int x = foo, lst = foo; x < mo; x = nxt[x])
		{
			if (tot[x] >= cnt) continue;
			int u = __gcd((x - tmp + mo) % mo, mo);
			while (u > 1) ++tot[x], u /= p;
			if (tot[x] >= cnt) nxt[lst] = nxt[x], Min[x] = i * i + 1;
			else lst = x;
		}
	}
	REP(i, 0, d) chkmax(fir[i], Min[i % mo]);
}

class SparseFactorial
{
	public:
		long long getCount(long long lo, long long hi, long long _d)
		{
			L = lo, R = hi + 1, d = _d;
			REP(i, 0, d) fir[i] = L;
			int u = d;
			for (int i = 2; i * i <= u; ++i)
			{
				if (!(u % i))
				{
					int cnt = 0;
					while (!(u % i)) u /= i, ++cnt;
					doit(i, cnt);
				}
			}
			if (u > 1) doit(u, 1);
			LL ret = 0;
			REP(i, 0, d) fir[i] = fir[i] + (i - fir[i] % d + d) % d;
			REP(i, 0, d) ret += max(0LL, (R - fir[i] + d - 1) / d);
			return ret;
		}
		

};



// Powered by FileEdit
// Powered by TZTester 1.01 [25-Feb-2003]
// Powered by CodeProcessor
