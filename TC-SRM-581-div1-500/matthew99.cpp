#line 5 "TreeUnion.cpp"
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

const int maxn = 300;

int n;

int cnt[maxn + 5];

int A[maxn + 5][maxn + 5], B[maxn + 5][maxn + 5];

class TreeUnion
{
	public:
		double expectedCycles(vector <string> tree1, vector <string> tree2, int K)
		{
			memset(A, oo, sizeof A), memset(B, oo, sizeof B);
			istringstream inA(accumulate(ALL(tree1), string("")));
			istringstream inB(accumulate(ALL(tree2), string("")));
			n = 0;
			int x;
			while (inA >> x) ++n, A[n][x] = A[x][n] = 1; ++n;
			REP(i, 1, n) inB >> x, B[i][x] = B[x][i] = 1;
			REP(k, 0, n) REP(i, 0, n) REP(j, 0, n) chkmin(A[i][j], A[i][k] + A[k][j]), chkmin(B[i][j], B[i][k] + B[k][j]);
			memset(cnt, 0, sizeof cnt);
			REP(i, 0, n) REP(j, 0, i) ++cnt[A[i][j]];
			double ret = 0;
			REP(i, 0, n) REP(j, 0, n) if (i != j && B[i][j] + 2 < K) ret += cnt[K - 2 - B[i][j]];
			return ret / (n * (n - 1));
		}
		

};



// Powered by FileEdit
// Powered by TZTester 1.01 [25-Feb-2003]
// Powered by CodeProcessor
