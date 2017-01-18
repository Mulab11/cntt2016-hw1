#line 5 "ConversionMachine.cpp"
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

const int maxn = 11, max0 = 80;

int n;
int a[maxn + 1], b[maxn + 1];

int N = 0;
int id[maxn + 1][maxn + 1];

int A[max0 + 5][max0 + 5];

inline void mul(int a[max0 + 5][max0 + 5], int b[max0 + 5][max0 + 5])
{
	static int ans[max0 + 5][max0 + 5];
	memset(ans, 0, sizeof ans);
	REP(i, 0, N) REP(j, 0, N) REP(k, 0, N)
		(ans[i][k] += (LL)a[i][j] * b[j][k] % Mod) %= Mod;
	REP(i, 0, N) REP(j, 0, N) a[i][j] = ans[i][j];
}

class ConversionMachine
{
	public:
		int countAll(string word1, string word2, vector <int> costs, int maxCost)
		{
			n = SZ(word1);
			REP(i, 0, n) a[i] = word1[i] - 'a', b[i] = word2[i] - 'a';
			N = 0;
			REP(i, 0, n + 1) REP(j, 0, n - i + 1) id[i][j] = N++;
			++N;
			LL cyc = costs[0] + costs[1] + costs[2];
			LL need = 0;
			int Max = 0;
			REP(i, 0, n)
			{
				int u = a[i];
				while (u != b[i]) need += costs[u], ++Max, (++u) %= 3;
			}
			if (need > maxCost) return 0;
			memset(A, 0, sizeof A);
			REP(i, 0, n + 1) REP(j, 0, n - i + 1)
			{
				A[id[i][j]][id[i + 1][j]] = n - i - j;
				A[id[i][j]][id[i - 1][j + 1]] = i;
				A[id[i][j]][id[i][j - 1]] = j;
			}
			A[id[n][0]][N - 1] = 1;
			A[N - 1][N - 1] = 1;
			Max += 3 * ((maxCost - need) / cyc) + 1;
			int u = 0, v = 0;
			REP(i, 0, n)
			{
				int tmp = (a[i] - b[i] + 3) % 3;
				if (tmp == 0) ++u; else if (tmp == 1) ++v;
			}
			static int t[max0 + 5][max0 + 5];
			memset(t, 0, sizeof t);
			REP(i, 0, N) t[i][i] = 1;
			for ( ; Max; Max >>= 1, mul(A, A)) if (Max & 1) mul(t, A);
			int ret = t[id[u][v]][N - 1];
			(ret += Mod) %= Mod;
			return ret;
		}
		

};



// Powered by FileEdit
// Powered by TZTester 1.01 [25-Feb-2003]
// Powered by CodeProcessor
