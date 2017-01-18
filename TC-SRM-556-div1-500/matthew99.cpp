#include <bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for (int i = (a), i##_end_ = (b); i < i##_end_; ++i)
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

const int maxn = 60;

int n;
int a[maxn + 5];
int b[maxn + 5];

class LeftRightDigitsGame2 
{
	public:
		string minNumber(string _a, string _b) 
		{
			n = SZ(_a);
			REP(i, 0, n) a[i] = _a[i] - '0';
			REP(i, 0, n) b[i] = _b[i] - '0';
			static string dp[maxn + 5][maxn + 5][3];
			REP(i, 0, n + 1) REP(j, 0, n + 1) REP(k, 0, 3) dp[i][j][k] = "a";
			REP(i, 0, n) dp[i][i][1] = "";
			for (int i = n; i >= 0; --i) REP(j, i, n + 1) REP(k, 0, 3) if (dp[i][j][k] != "a")
			{
				int p = j - i;
				if (i)
				{
					if (a[p] > b[i - 1]) chkmin(dp[i - 1][j][2], char('0' + a[p]) + dp[i][j][k]);
					else if (a[p] == b[i - 1]) chkmin(dp[i - 1][j][k], char('0' + a[p]) + dp[i][j][k]);
					else chkmin(dp[i - 1][j][0], char('0' + a[p]) + dp[i][j][k]);
				}
				if (j < n)
				{
					if (k == 1) chkmin(dp[i][j + 1][a[p] > b[j] ? 2 : a[p] == b[j]], dp[i][j][k] + char('0' + a[p]));
					else chkmin(dp[i][j + 1][k], dp[i][j][k] + char('0' + a[p]));
				}
			}
			string ret = min(dp[0][n][1], dp[0][n][2]);
			if (ret == "a") return "";
			return ret;
		}
};

// Powered by Greed 2.0-RC
