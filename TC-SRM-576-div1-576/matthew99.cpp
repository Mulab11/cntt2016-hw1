#line 5 "TheExperiment.cpp"
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

const int maxn = 300;

int n;
int a[maxn + 5];
int dp[maxn + 5][maxn + 5][3];

class TheExperiment
{
	public:
		int countPlacements(vector <string> intensity, int M, int L, int A, int B)
		{
			n = 0;
			for (auto it : intensity) for (auto it0 : it) a[n++] = it0 - '0';
			memset(dp, 0, sizeof dp);
			dp[0][0][2] = 1;
			REP(i, 0, n) REP(j, 0, min(M, i) + 1) REP(k, 0, 3) if (dp[i][j][k])
			{
				if (k) (dp[i + 1][j][2] += dp[i][j][k]) %= Mod;
				if (j == M) continue;
				int sum = 0;
				REP(l, 1, min(L, n - i) + 1)
				{
					sum += a[i + l - 1];
					if (sum >= A && sum <= B) (dp[i + l][j + 1][(k & 1) | (l == L)] += dp[i][j][k]) %= Mod;
				}
			}
			return (dp[n][M][1] + dp[n][M][2]) % Mod;
		}
		

};



// Powered by FileEdit
// Powered by TZTester 1.01 [25-Feb-2003]
// Powered by CodeProcessor
