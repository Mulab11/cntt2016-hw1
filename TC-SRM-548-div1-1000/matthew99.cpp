#line 5 "KingdomAndCities.cpp"
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

const int maxn = 50, maxk = 50, max0 = 50, maxm = 2;

int f[maxm + 1][maxn + 5][maxk + 5];
int g[maxm + 1][maxn + 5][maxk + 5];

int C[(maxn * (maxn - 1) >> 1) + 5][max0 + 5];

inline void prepare()
{
	memset(f, 0, sizeof f), memset(g, 0, sizeof g);
	REP(i, 0, (maxn * (maxn - 1) >> 1) + 1)
	{
		C[i][0] = 1;
		REP(j, 1, min(i, max0) + 1)
			(C[i][j] = C[i - 1][j - 1] + C[i - 1][j]) %= Mod;
	}
	REP(i, 0, maxm + 1) REP(j, i, maxn + 1) REP(k, 0, min(maxk, (j * (j - 1)) >> 1) + 1)
	{
		if (!i) g[i][j][k] = C[j * (j - 1) >> 1][k];
		else if (i == 1) 
		{
			if (j > 2 && k >= 2) g[i][j][k] = ((LL)C[(j - 1) * (j - 2) >> 1][k - 2] * (j - 1) * (j - 2) >> 1) % Mod;
		}
		else if (i == 2)
		{
			if (j >= 3 && k >= 3) 
			{
				if (k >= 4) g[i][j][k] = ((LL)C[(j - 2) * (j - 3) >> 1][k - 4] * (j - 2) * (j - 3) * (j - 2) * (j - 3) >> 2) % Mod;
				(g[i][j][k] += ((LL)C[(j - 2) * (j - 3) >> 1][k - 3] * (j - 2) * (j - 2) % Mod)) %= Mod;
			}
		}
		f[i][j][k] = g[i][j][k];
		if (j > 1)
		{
			if (!i)
			{
				REP(u, 1, j) REP(v, 0, k + 1)
					(f[i][j][k] -= (LL)C[j - 1][u - 1] * f[i][u][v] % Mod * g[i][j - u][k - v] % Mod) %= Mod;
			}
			else
			{
				REP(w, 1, i + 1) REP(u, w, w + (j - i)) REP(v, 0, k + 1)
					(f[i][j][k] -= (LL)C[j - i][u - w] * f[w][u][v] % Mod * g[i - w][j - u][k - v] % Mod) %= Mod;
			}
		}
	}
}

class KingdomAndCities
{
	public:
		int howMany(int N, int M, int K)
		{
			prepare();
			int ret = f[M][N][K];
			(ret += Mod) %= Mod;
			return ret;
		}


};



// Powered by FileEdit
// Powered by TZTester 1.01 [25-Feb-2003]
// Powered by CodeProcessor
