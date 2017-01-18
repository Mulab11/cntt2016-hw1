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
pair<int, int> a[maxn + 5];

class GUMIAndSongsDiv1 
{
	public:
		int maxSongs(vector<int> duration, vector<int> tone, int T) 
		{
			n = SZ(duration);
			REP(i, 0, n) a[i] = mp(tone[i], duration[i]);
			sort(a, a + n);
			static int dp[maxn + 5][maxn + 5];
			memset(dp, oo, sizeof dp);
			int ret = 0;
			REP(i, 0, n)
			{
				dp[i][1] = a[i].y;
				REP(j, 0, i) REP(k, 1, n) if (dp[j][k] < T) chkmin(dp[i][k + 1], dp[j][k] + a[i].y + a[i].x - a[j].x);
				REP(j, 1, n + 1) if (dp[i][j] <= T) chkmax(ret, j);
			}
			return ret;
		}
};

// Powered by Greed 2.0-RC
