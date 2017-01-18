#line 5 "BoundedOptimization.cpp"
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

const int maxn = 13;

int n;
bool g[maxn + 5][maxn + 5];

double val[maxn + 5];

inline double calc()
{
	double ret = 0;
	REP(i, 0, n) REP(j, 0, i) if (g[i][j]) ret += val[i] * val[j];
	return ret;
}

inline bool check(int x)
{
	REP(i, 0, n) if (x >> i & 1) REP(j, 0, i) if ((x >> j & 1) && !g[i][j]) return 0;
	return 1;
}

class BoundedOptimization
{
	public:
		double maxValue(vector <string> expr, vector <int> lowerBound, vector <int> upperBound, int maxSum)
		{
			memset(g, 0, sizeof g);
			n = SZ(lowerBound);
			char lst = '+';
			for (auto u : expr) for (auto v : u) { if (islower(v) && islower(lst)) g[v - 'a'][lst - 'a'] = g[lst - 'a'][v - 'a'] = 1; lst = v; }
			int S = (1 << n) - 1;
			if (accumulate(ALL(upperBound), 0) <= maxSum)
			{
				REP(i, 0, n) val[i] = upperBound[i];
				return calc();
			}
			double ret = 0;
			REP(i, 0, 1 << n)
			{
				if (!check(S ^ i)) continue;
				for (int j = i; ; j = (j - 1) & i)
				{
					REP(k, 0, n) if (i >> k & 1) val[k] = (j >> k & 1) ? lowerBound[k] : upperBound[k];
					double res = maxSum;
					REP(k, 0, n) if (i >> k & 1) res -= val[k];
					if (res >= 0) 
					{
						static double sum[maxn + 5];
						double tot = 0;
						int cnt = 0;
						REP(k, 0, n) if (!(i >> k & 1)) 
						{
							++cnt;
							sum[k] = 0;
							REP(l, 0, n) if ((i >> l & 1) && g[k][l]) sum[k] += val[l];
							tot += sum[k];
						}
						tot -= res;
						tot = -tot;
						tot /= cnt;
						bool ok = 1;
						REP(k, 0, n) if (!(i >> k & 1)) 
						{
							val[k] = tot + sum[k];
							if (val[k] < lowerBound[k] || val[k] > upperBound[k])
							{
								ok = 0;
								break;
							}
						}
						if (ok) chkmax(ret, calc());
					}
					if (!j) break;
				}
			}
			return ret;
		}
		

};



// Powered by FileEdit
// Powered by TZTester 1.01 [25-Feb-2003]
// Powered by CodeProcessor
