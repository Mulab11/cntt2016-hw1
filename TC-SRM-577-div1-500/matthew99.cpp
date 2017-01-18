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

const int maxn = 8;

int dp[maxn << 1][maxn << 1][maxn << 1][maxn << 1];

vector<pair<int, int> > all;

int n, m;

inline int get0(const pair<int, int> &x) { return x.x + x.y; }
inline int get1(const pair<int, int> &x) { return x.x + m - x.y - 1; }
inline int get2(const pair<int, int> &x) { return n - x.x - 1 + x.y; }
inline int get3(const pair<int, int> &x) { return n - x.x - 1 + m - x.y - 1; }

class EllysChessboard 
{
	public:
		int minCost(vector<string> _g) 
		{
			n = SZ(_g), m = SZ(_g[0]);
			all.clear();
			REP(i, 0, n) REP(j, 0, m) if (_g[i][j] == '#') all.pb(mp(i, j));
			memset(dp, oo, sizeof dp);
			dp[0][0][0][0] = 0;
			REP(i, 0, n + m) REP(j, 0, n + m) REP(k, 0, n + m) REP(l, 0, n + m) if (dp[i][j][k][l] < oo)
			{
				int tmp = 0;
				if (i + 1 < n + m)
				{
					tmp = 0;
					for (auto u : all) if (get0(u) == i && get1(u) < j && get2(u) < k && get3(u) < l) tmp += max({j - 1 - get1(u), k - 1 - get2(u), l - 1 - get3(u)});
					chkmin(dp[i + 1][j][k][l], dp[i][j][k][l] + tmp);
				}
				if (j + 1 < n + m)
				{
					tmp = 0;
					for (auto u : all) if (get0(u) < i && get1(u) == j && get2(u) < k && get3(u) < l) tmp += max({i - 1 - get0(u), k - 1 - get2(u), l - 1 - get3(u)});
					chkmin(dp[i][j + 1][k][l], dp[i][j][k][l] + tmp);
				}
				if (k + 1 < n + m)
				{
					tmp = 0;
					for (auto u : all) if (get0(u) < i && get1(u) < j && get2(u) == k && get3(u) < l) tmp += max({i - 1 - get0(u), j - 1 - get1(u), l - 1 - get3(u)});
					chkmin(dp[i][j][k + 1][l], dp[i][j][k][l] + tmp);
				}
				if (l + 1 < n + m)
				{
					tmp = 0;
					for (auto u : all) if (get0(u) < i && get1(u) < j && get2(u) < k && get3(u) == l) tmp += max({i - 1 - get0(u), j - 1 - get1(u), k - 1 - get2(u)});
					chkmin(dp[i][j][k][l + 1], dp[i][j][k][l] + tmp);
				}
			}
			return dp[n + m - 1][n + m - 1][n + m - 1][n + m - 1];
		}
};

// Powered by Greed 2.0-RC
