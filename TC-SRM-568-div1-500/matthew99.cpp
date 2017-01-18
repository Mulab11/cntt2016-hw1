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

const int Mod = 1e9 + 7;

const int maxn = 60;

int n, m;
int g[maxn + 5][maxn + 5];

int r[maxn + 5], c[maxn + 5];

class EqualSums 
{
	public:
		int count(vector<string> _g) 
		{
			n = SZ(_g), m = SZ(_g[0]);
			REP(i, 0, n) REP(j, 0, m)
			{
				if (_g[i][j] == '-') g[i][j] = -1;
				else g[i][j] = _g[i][j] - '0';
			}
			memset(r, oo, sizeof r);
			memset(c, oo, sizeof c);
			vector<int> all;
			REP(_i, 0, n) if (r[_i] == oo)
			{
				queue<int> q;
				q.push(_i);
				int Minr = r[_i] = 0, Maxc = -oo;
				while (!q.empty())
				{
					int i = q.front(); q.pop();
					REP(j, 0, m)
					{
						if (~g[i][j])
						{
							if (c[j] < oo)
							{
								if (r[i] - c[j] != g[i][j]) return 0;
							}
							else
							{
								c[j] = r[i] - g[i][j];
								chkmax(Maxc, c[j]);
								REP(k, 0, n) if (~g[k][j])
								{
									r[k] = g[k][j] + c[j];
									chkmin(Minr, r[k]);
									q.push(k);
								}
							}
						}
					}
				}
				if (Minr < Maxc) return 0;
				all.pb(Minr - Maxc);
			}
			static int dp[maxn + 5][10];
			memset(dp, 0, sizeof dp);
			dp[1][all[0]] = 1;
			REP(i, 1, SZ(all)) REP(j, 0, 10) if (dp[i][j])
				for (int k = -all[i]; k <= j; ++k) (dp[i + 1][min(k + all[i], j) - max(0, k)] += dp[i][j]) %= Mod;
			int ret = 0;
			REP(i, 0, 10) (ret += dp[SZ(all)][i]) %= Mod;
			(ret += Mod) %= Mod;
			return ret;
		}
};

// Powered by Greed 2.0-RC
