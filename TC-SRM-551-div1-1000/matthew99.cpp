#line 5 "SweetFruits.cpp"
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

const int maxn = 40;

int C[maxn + 5][maxn + 5];

vector<int> all0[maxn + 5];
vector<int> all1[maxn + 5];

int n, m, S;
int a[maxn + 5];

int tot[maxn + 5];

int ed[maxn + 5][maxn + 5];
int deg[maxn + 5];

inline int calc()
{
	static int a[maxn + 5][maxn + 5];
	REP(i, 0, n + m) { deg[i] = 0; REP(j, 0, n + m) deg[i] += ed[i][j]; }
	REP(i, 0, n + m) REP(j, 0, n + m) (a[i][j] = -ed[i][j]) %= Mod;
	REP(i, 0, n + m) (a[i][i] += deg[i]) %= Mod;
	int N = n + m - 1;
	static int pos[maxn + 5];
	REP(i, 0, N) pos[i] = i;
	int ret = 1;
	REP(i, 0, N)
	{
		REP(j, i, N) if (a[pos[j]][i]) 
		{
			if (j != i) swap(pos[i], pos[j]), ret = -ret;
			break;
		} 
		if (!a[pos[i]][i]) return 0;
		ret = (LL)ret * a[pos[i]][i] % Mod;
		int inv = fpm(a[pos[i]][i], Mod - 2, Mod);
		REP(j, i + 1, N) if (a[pos[j]][i])
		{
			int tmp = (LL)inv * a[pos[j]][i] % Mod;
			REP(k, i, N) (a[pos[j]][k] -= (LL)a[pos[i]][k] * tmp % Mod) %= Mod;
		}
	}
	return ret;
}

inline void prepare()
{
	REP(i, 0, maxn + 1)
	{
		C[i][0] = 1;
		REP(j, 1, i + 1) (C[i][j] = C[i - 1][j - 1] + C[i - 1][j]) %= Mod;
	}
}

class SweetFruits
{
	public:
		int countTrees(vector <int> sweetness, int maxSweetness)
		{
			prepare();
			n = m = 0, S = maxSweetness;
			for (auto x : sweetness) if (x != -1) a[n++] = x; else ++m;
			int mid = n >> 1;
			REP(i, 0, mid + 1) all0[i].clear();
			REP(i, 0, n - mid + 1) all1[i].clear();
			REP(i, 0, 1 << mid)
			{
				int sum = 0;
				REP(j, 0, mid) if (i >> j & 1) sum += a[j];
				all0[__builtin_popcount(i)].pb(sum);
			}
			REP(i, 0, mid + 1) sort(ALL(all0[i]));
			REP(i, 0, 1 << (n - mid))
			{
				int sum = 0;
				REP(j, 0, n - mid) if (i >> j & 1) sum += a[j + mid];
				all1[__builtin_popcount(i)].pb(sum);
			}
			REP(i, 0, n - mid + 1) sort(ALL(all1[i]));
			memset(tot, 0, sizeof tot);
			REP(i, 0, mid + 1) REP(j, 0, n - mid + 1)
			{
				int b = SZ(all1[j]) - 1;
				REP(a, 0, SZ(all0[i]))
				{
					while (b >= 0 && all0[i][a] + all1[j][b] > S) --b;
					if (b < 0) break;
					(tot[i + j] += b + 1) %= Mod;
				}
			}
			static int dp[maxn + 5];
			REP(num, 0, n + 1)
			{
				memset(ed, 0, sizeof ed);
				REP(i, 0, n + m) REP(j, max(i + 1, i < num ? n : 0), n + m) ed[i][j] = ed[j][i] = 1;
				dp[n - num] = calc();
			}
			REP(i, 0, n + 1) REP(j, 0, i) (dp[i] -= (LL)dp[j] * C[i][j] % Mod) %= Mod;
			int ret = 0;
			REP(i, 0, n + 1) (ret += (LL)dp[i] * tot[i] % Mod) %= Mod;
			(ret += Mod) %= Mod;
			return ret;
		}


};



// Powered by FileEdit
// Powered by TZTester 1.01 [25-Feb-2003]
// Powered by CodeProcessor
