#line 5 "SplittingFoxes2.cpp"
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

const double pi = acos(-1);

typedef complex<double> comp;

const int maxn = 25;

int n;
comp a[maxn + 5];

class SplittingFoxes2
{
	public:
		vector <int> getPattern(vector <int> amount)
		{
			n = SZ(amount);
			int half = (n >> 1) + 1;
			REP(i, 0, half) { a[i] = 0; REP(j, 0, n) a[i] += exp(comp(0, i * j * 2 * pi / n)) * (comp)amount[j]; }
			vector<int> ret(1, -1);
			REP(i, 0, half) a[i] = sqrt(a[i]);
			REP(i, half, n) a[i] = a[n - i];
			REP(i, 0, 1 << half)
			{
				static comp b[maxn + 5];
				REP(j, 0, n)
				{
					if (j < half) b[j] = (i >> j & 1) ? -a[j] : a[j];
					else b[j] = (i >> (n - j) & 1) ? -a[j] : a[j];
				}
				static comp c[maxn + 5];
				REP(i, 0, n) { c[i] = 0; REP(j, 0, n) c[i] += exp(comp(0, -i * j * 2 * pi / n)) * b[j]; }
				vector<int> d(n);
				bool ok = 1;
				REP(i, 0, half) 
				{
					double tmp = c[i].real() / n;
					if (tmp > 2e3 || tmp < -0.5) { ok = 0; break; }
					d[i] = int(tmp + 0.5);
					if (d[i] < 0) { ok = 0; break; }
				}
				REP(i, half, n) d[i] = d[n - i];
				if (!ok) continue;
				static int e[maxn + 5];
				memset(e, 0, sizeof e);
				REP(i, 0, n) REP(j, 0, n) e[(i + j) % n] += d[i] * d[j];
				REP(i, 0, n) if (e[i] != amount[i]) { ok = 0; break; }
				if (!ok) continue;
				if (!~ret[0] || lexicographical_compare(ALL(d), ALL(ret))) ret = d;
			}
			return ret;
		}
		

};



// Powered by FileEdit
// Powered by TZTester 1.01 [25-Feb-2003]
// Powered by CodeProcessor
