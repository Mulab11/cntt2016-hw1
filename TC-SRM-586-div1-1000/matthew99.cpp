#line 5 "StringWeight.cpp"
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

const int maxn = 50;

const int sigma = 26;

const int oo = 0x3f3f3f3f;

class StringWeight
{
	public:
		int getMinimum(vector <int> L)
		{
			int n = SZ(L);
			static int dp[maxn + 5][sigma + 1][sigma + 1];
			memset(dp, oo, sizeof dp);
			dp[0][0][0] = 0;
			int sum = 0;
			REP(i, 0, n)
			{
				int l = L[i];
				int tot = min(l, sigma);
				REP(j, 0, sigma + 1) REP(k, 0, sigma + 1)
					if (dp[i][j][k] < oo)
					{
						REP(pre, 0, tot + 1) if (j - pre >= 0) REP(suf, 0, tot - pre + 1) if (k + suf <= sigma) REP(mid, 0, tot - pre - suf + 1) if (mid + k + suf <= sigma)
						{
							int tmp = tot - pre - suf - mid;
							if (j - pre < tmp) continue;
							int val = dp[i][j][k] + (sum * pre + (pre * (pre - 1) >> 1)) - ((sum + l) * suf - (suf * (suf + 1) >> 1)) + (!tmp ? (l - tot) : 0);
							chkmin(dp[i + 1][j - pre + suf][mid + k + suf], val);
						}
					}
				sum += l;
			}
			int ret = oo;
			REP(i, 0, sigma + 1) chkmin(ret, dp[n][0][i]);
			return ret;
		}
		

};



// Powered by FileEdit
// Powered by TZTester 1.01 [25-Feb-2003]
// Powered by CodeProcessor
