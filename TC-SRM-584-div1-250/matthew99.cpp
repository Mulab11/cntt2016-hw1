#line 5 "Egalitarianism.cpp"
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

const int maxn = 50;

int n;
int f[maxn + 5][maxn + 5];

class Egalitarianism
{
	public:
		int maxDifference(vector <string> isFriend, int d)
		{
			n = SZ(isFriend);
			REP(i, 0, n) REP(j, 0, n) f[i][j] = isFriend[i][j] == 'Y' ? 1 : oo;
			REP(i, 0, n) f[i][i] = 0;
			REP(k, 0, n) REP(i, 0, n) REP(j, 0, n) chkmin(f[i][j], f[i][k] + f[k][j]);
			int ans = 0;
			REP(i, 0, n) REP(j, 0, n) chkmax(ans, f[i][j]);
			return ans == oo ? -1 : ans * d;
		}
		

};



// Powered by FileEdit
// Powered by TZTester 1.01 [25-Feb-2003]
// Powered by CodeProcessor
