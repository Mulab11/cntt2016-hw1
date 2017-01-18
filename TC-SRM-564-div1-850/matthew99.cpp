#line 5 "DefectiveAddition.cpp"
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

const int maxn = 50;

int n;
int a[maxn + 5];

class DefectiveAddition
{
	public:
		int count(vector <int> cards, int goal)
		{
			n = SZ(cards);
			REP(i, 0, n) a[i] = cards[i];
			int ret = 0;
			while (1)
			{
				sort(a, a + n);
				if (!a[n - 1]) { (ret += goal == 0) %= Mod; break; }
				int t = a[n - 1] + 1;
				while (t & (t - 1)) t += t & -t;
				if (t <= goal) break;
				t >>= 1;
				static int dp[maxn + 5][2];
				memset(dp, 0, sizeof dp);
				dp[0][0] = 1;
				REP(i, 0, n - 1) REP(j, 0, 2)
					if (dp[i][j])
					{
						(dp[i + 1][j] += (LL)dp[i][j] * min(t, a[i] + 1) % Mod) %= Mod;
						(dp[i + 1][!j] += (LL)dp[i][j] * max(0, a[i] - t + 1) % Mod) %= Mod;
					}
				if (goal >= t) (ret += dp[n - 1][1]) %= Mod;
				else (ret += dp[n - 1][0]) %= Mod;
				a[n - 1] ^= t;
				goal ^= t;
			}
			(ret += Mod) %= Mod;
			return ret;
		}


};



// Powered by FileEdit
// Powered by TZTester 1.01 [25-Feb-2003]
// Powered by CodeProcessor
